#ifndef THREADPOOL
#define THREADPOOL

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <memory>
#include <atomic>
#include <functional>
#include <iostream>
#include <map>

class ThreadPool {
public:
  ThreadPool(int number_of_threads);
  ~ThreadPool();

  void schedule_task(std::function<void()> f);

  void shut_down();

private:
  std::vector<std::thread> thread_pool;

  std::queue<std::function<void()>> tasks;

  std::mutex tasks_mutex;

  std::condition_variable cv;

  std::atomic<bool> terminate;

  std::atomic<bool> stopped;

  void invoke();
};

#endif /* end of include guard:  */
