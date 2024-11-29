#include "ThreadPool.hpp"

ThreadPool::ThreadPool(const size_t numThreads = thread::hardware_concurrency()) {
    // Create worker threads
    for (size_t i = 0; i < numThreads; i++) {
        threads_.emplace_back([this] {
            while (true) {
                function<void()> task; {
                    // Lock the mutex before checking for tasks
                    unique_lock<mutex> lock(queue_mutex_);

                    // Wait until there is a task in the queue
                    cv_.wait(lock, [this] { return stop_ || !tasks_.empty(); });

                    // If the thread pool is stopping and the queue is empty, break
                    if (stop_ && tasks_.empty()) {
                        return;
                    }

                    // Get the next task from the queue
                    task = move(tasks_.front());
                    tasks_.pop();
                }

                // Execute the task
                task();
            }
        });
    }
}

// Destructor to stop all threads
ThreadPool::~ThreadPool() { {
        // Lock the mutex before stopping the threads
        unique_lock<mutex> lock(queue_mutex_);
        stop_ = true;
    }

    // Notify all threads
    cv_.notify_all();

    // Join all threads to make sure they have completed their work
    for (auto &thread: threads_) {
        thread.join();
    }
}

// Enqueue a task to the thread pool
void ThreadPool::Enqueue(std::function<void()> task) { {
        unique_lock<mutex> lock(queue_mutex_);
        tasks_.push(task);
    }
    cv_.notify_one();
}
