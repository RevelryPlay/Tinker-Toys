#pragma once

#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
using namespace std;

class ThreadPool {
public:
    explicit ThreadPool(size_t numThreads = thread::hardware_concurrency());
    ~ThreadPool();

    void Enqueue(const std::function<void()>& task);

private:
    // Vector to store worker threads
    vector<thread> threads_;

    // Queue of tasks
    queue<function<void()> > tasks_;

    // Mutex to synchronize access to shared data
    mutex queue_mutex_;

    // Condition variable to signal changes in the state of
    // the tasks queue
    condition_variable cv_;

    // Flag to indicate whether the thread pool should stop or not
    bool stop_ = false;
};