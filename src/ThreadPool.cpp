#include "ThreadPool.hpp"

ThreadPool::ThreadPool(int number_of_threads)
    : terminate(false), stopped(false) {
  for (int i = 0; i < number_of_threads; ++i) {
    this->thread_pool.emplace_back(std::thread(&ThreadPool::invoke, this));
  }
}

ThreadPool::~ThreadPool() {
  if (!this->stopped.load()) {
    this->shut_down();
  }
}

void ThreadPool::schedule_task(std::function<void()> f) {
  {
    std::unique_lock<std::mutex> lock(this->tasks_mutex);
    this->tasks.push(f);
  }
  this->cv.notify_one();
}

void ThreadPool::invoke() {
  std::function<void()> task;

  while (true) {
    {
      std::unique_lock<std::mutex> lock(this->tasks_mutex);
      this->cv.wait(lock, [this] {
        return !this->tasks.empty() || this->terminate.load();
      });

      if (this->terminate.load() && this->tasks.empty()) {
        return;
      }

      task = this->tasks.front();
      this->tasks.pop();
    }
    task();
  }
}

void ThreadPool::shut_down() {
  {
    std::unique_lock<std::mutex> lock(this->tasks_mutex);
    this->terminate.store(true);
  }

  this->cv.notify_all();

  for (auto &thread : this->thread_pool) {
    if (thread.joinable())
      thread.join();
  }

  this->thread_pool.empty();
  this->stopped.store(true);
}
