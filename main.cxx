#ifndef MAXNUMBER
#define MAXNUMBER 10000
#endif

#include <iostream>
#include <string>
#include <thread>
#include <map>
#include <cstdint>
#include <chrono>
#include <cstdlib>

#include <ThreadPool.hpp>
#include <SieveOfEratosthenes.hpp>

void task(
    uint64_t number,
    std::map<std::thread::id, std::map<uint64_t, uint64_t>> &thread_results,
    std::vector<uint64_t> primes) {

  auto this_thread_id = std::this_thread::get_id();

  std::map<uint64_t, uint64_t> factorization_result;

  while (number != 1) {
    auto prime = primes.begin();
    while (prime != primes.end() && (*prime) <= number) {
      if (number % (*prime) == 0) {
        if (factorization_result.find((*prime)) != factorization_result.end()) {
          factorization_result[(*prime)] += 1;
        } else {
          factorization_result[(*prime)] = 1;
        }
        number /= (*prime);
        break;
      }
      prime = std::next(prime);
    }
  }

  auto this_thread_results = thread_results.find(this_thread_id);
  if (this_thread_results != thread_results.end()) {
    for (auto it : factorization_result) {
      auto number = it.first;
      auto power = it.second;
      auto merged = *this_thread_results->second.find(number);

      if (merged != *this_thread_results->second.end()) {
        auto merged_power = merged.second;

        thread_results[this_thread_id][number] =
            (power > merged_power) ? power : merged_power;

      } else {
        { thread_results[this_thread_id][number] = power; }
      }
    }
  } else {
    thread_results[this_thread_id] = factorization_result;
  }
}

int main(int argc, char **argv) {
  std::map<std::thread::id, std::map<uint64_t, uint64_t>> thread_results;
  std::map<uint64_t, uint64_t> res;

  int number_of_threads = std::thread::hardware_concurrency();
  if (number_of_threads < 4)
    number_of_threads = 8;
  std::cout << "Threads: " << number_of_threads << std::endl;

  std::cout << "Generating primes in 10000 range" << std::endl;
  std::vector<uint64_t> primes = sieve_of_eratosthenes((uint64_t)10000);
  std::cout << "Successfully generated " << primes.size() << " primes"
            << std::endl;

  std::queue<uint64_t> numbers_queue;

  ThreadPool thread_pool(number_of_threads);

  uint64_t input;

  while (std::cin >> input) {

    numbers_queue.push(input);

    if (!numbers_queue.empty()) {
      uint64_t temp;

      temp = numbers_queue.front();
      numbers_queue.pop();
      thread_pool.schedule_task([temp, &thread_results, primes]() {
        task(temp, std::ref(thread_results), primes);
      });
    }
  }

  while (!numbers_queue.empty()) {

    uint64_t temp;

    temp = numbers_queue.front();
    numbers_queue.pop();
    thread_pool.schedule_task([temp, &thread_results, primes]() {
      task(temp, std::ref(thread_results), primes);
    });
  }

  thread_pool.shut_down();

  for (auto thread_result : thread_results) {
    for (auto it : thread_result.second) {
      auto prime = it.first;
      auto power = it.second;

      auto pair = res.find(prime);

      if (pair != res.end()) {
        res[prime] = (power > (*pair).second) ? power : (*pair).second;
      } else {
        res[prime] = power;
      }
    }
  }

  uint64_t lcm = 1;

  std::cout << "\tPrime number\tPower" << std::endl;

  for (auto it : res) {
    auto prime = it.first;
    auto power = it.second;

    std::cout << "\t" << prime << "\t\t" << power << std::endl;

    lcm *= (uint64_t)pow(prime, power);
  }

  std::cout << "LCM: " << lcm << std::endl;

  return 0;
}
