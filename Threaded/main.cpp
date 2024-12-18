#include <chrono>
#include <thread>

#include <ArgoDraft/ArgoLogger.hpp>
#include <ArgoDraft/ConsoleMenu.hpp>

#include "src/ThreadPool.hpp"

using namespace ArgoDraft;

int main() {
    try {
        MainMenu menu;

        menu.AddAction({
            "thread-sleep", "Test of ThreadPool using sleep", []() {
                // const std::string logFileName = "Threaded.log";
                // auto logger = Logger(logFileName);
                // logger.SetFileLogLevel(LogLevel::INFO);
                // logger.SetConsoleLogLevel(LogLevel::INFO);
                //
                // const auto numThreads = std::thread::hardware_concurrency();
                // logger.LogMessage("Starting ThreadPool sleep test", LogLevel::INFO);
                // logger.LogMessage(std::format("Number of threads: {}", numThreads).c_str(), LogLevel::INFO);
                //
                // const auto startTime = std::chrono::high_resolution_clock::now();
                // logger.LogMessage(std::format("Starting time: {}", startTime).c_str(), LogLevel::INFO);
                //
                // logger.LogMessage("Creating ThreadPool", LogLevel::INFO);
                // ThreadPool pool(numThreads);
                //
                // for (int i = 0; i < 100; i++) {
                //     pool.Enqueue([i, &logger] {
                //         logger.LogMessage(std::format("Task {} started", i).c_str(), LogLevel::INFO);
                //         std::this_thread::sleep_for(std::chrono::seconds(1));
                //         logger.LogMessage(std::format("Task {} finished", i).c_str(), LogLevel::INFO);
                //     });
                // }
                //
                // std::this_thread::sleep_for(std::chrono::seconds(11));
                //
                // const auto endTime = std::chrono::high_resolution_clock::now();
                // logger.LogMessage(std::format("Ending time: {}", endTime).c_str(), LogLevel::INFO);
            }
        });
        menu.AddAction({
            "thread-prime", "Test of ThreadPool using prime numbers", []() {
                // const std::string logFileName = "Threaded.log";
                // auto logger = Logger(logFileName);
                // logger.SetFileLogLevel(LogLevel::INFO);
                // logger.SetConsoleLogLevel(LogLevel::INFO);
                //
                // const auto numThreads = std::thread::hardware_concurrency();
                // logger.LogMessage("Starting ThreadPool prime number test", LogLevel::INFO);
                // logger.LogMessage(std::format("Number of threads: {}", numThreads).c_str(), LogLevel::INFO);
                //
                // const auto startTime = std::chrono::high_resolution_clock::now();
                // logger.LogMessage(std::format("Starting time: {}", startTime).c_str(), LogLevel::INFO);
                //
                // logger.LogMessage("Creating ThreadPool", LogLevel::INFO);
                // ThreadPool pool(numThreads);
                //
                // for (int i = 0; i < 100; i++) {
                //     pool.Enqueue([i, &logger] {
                //         logger.LogMessage(std::format("Task {} started", i).c_str(), LogLevel::INFO);
                //
                //         constexpr auto n = 100000;
                //         std::vector<bool> isPrime(n + 1, true);
                //         isPrime[0] = isPrime[1] = false;
                //
                //         for (int i = 2; i * i <= n; i++) {
                //             if (isPrime[i]) {
                //                 for (int j = i * i; j <= n; j += i) {
                //                     isPrime[j] = false;
                //                 }
                //             }
                //         }
                //
                //         logger.LogMessage(std::format("Task {} finished", i).c_str(), LogLevel::INFO);
                //     });
                // }
                //
                // std::this_thread::sleep_for(std::chrono::seconds(11));
                //
                // const auto endTime = std::chrono::high_resolution_clock::now();
                // logger.LogMessage(std::format("Ending time: {}", endTime).c_str(), LogLevel::INFO);
                //
                // const auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
                // logger.LogMessage(std::format("Duration: {} milliseconds", duration.count()).c_str(),
                //                   LogLevel::INFO);
            }
        });

        menu.AddAction({
            "thread-fibonacci", "Test of ThreadPool using fibonacci numbers", []() {
                // const std::string logFileName = "Threaded.log";
                // auto logger = Logger(logFileName);
                // logger.SetFileLogLevel(LogLevel::INFO);
                // logger.SetConsoleLogLevel(LogLevel::INFO);
                //
                // const auto numThreads = std::thread::hardware_concurrency();
                // logger.LogMessage("Starting ThreadPool fibonacci number test", LogLevel::INFO);
                // logger.LogMessage(std::format("Number of threads: {}", numThreads).c_str(), LogLevel::INFO);
                //
                // const auto startTime = std::chrono::high_resolution_clock::now();
                // logger.LogMessage(std::format("Starting time: {}", startTime).c_str(), LogLevel::INFO);
                //
                // logger.LogMessage("Creating ThreadPool", LogLevel::INFO);
                // ThreadPool pool(numThreads);
                //
                // for (int i = 0; i < 100; i++) {
                //     pool.Enqueue([i, &logger] {
                //         logger.LogMessage(std::format("Task {} started", i).c_str(), LogLevel::INFO);
                //
                //         constexpr auto n = 100000;
                //         std::vector<long long> fib(n + 1);
                //         fib[0] = 0;
                //         fib[1] = 1;
                //
                //         for (int i = 2; i <= n; i++) {
                //             fib[i] = fib[i - 1] + fib[i - 2];
                //         }
                //
                //         logger.LogMessage(std::format("Task {} finished", i).c_str(), LogLevel::INFO);
                //     });
                // }
                //
                // std::this_thread::sleep_for(std::chrono::seconds(11));
                //
                // const auto endTime = std::chrono::high_resolution_clock::now();
                // logger.LogMessage(std::format("Ending time: {}", endTime).c_str(), LogLevel::INFO);
                //
                // const auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
                // logger.LogMessage(std::format("Duration: {} milliseconds", duration.count()).c_str(), LogLevel::INFO);
            }
        });

        // Minimal thread pool test
        menu.AddAction({
            "minimal", "A minimal thread pool test", []() {
                const std::string logFileName = "Threaded.log";
                auto logger = Logger(logFileName);
                logger.SetFileLogLevel(LogLevel::INFO);
                logger.SetConsoleLogLevel(LogLevel::INFO);

                logger.LogMessage("Starting minimal ThreadPool test", LogLevel::INFO);

                const auto numThreads = std::thread::hardware_concurrency();
                logger.LogMessage(std::format("Number of threads: {}", numThreads).c_str(), LogLevel::INFO);

                logger.LogMessage("Creating ThreadPool", LogLevel::INFO);
                ThreadPool pool(numThreads);

                for (int i = 0; i < 100; i++) {
                    pool.Enqueue([i, &logger] {
                        logger.LogMessage(
                            std::format("Task {} started on thread {}", i, std::this_thread::get_id()).c_str(),
                            LogLevel::INFO);
                        std::this_thread::sleep_for(std::chrono::seconds(1));
                        logger.LogMessage(
                            std::format("Task {} finished on thread {}", i, std::this_thread::get_id()).c_str(),
                            LogLevel::INFO);
                    });
                }

                std::this_thread::sleep_for(std::chrono::seconds(11));
            }
        });

        menu.Init();
    } catch (const std::exception &e) {
        const std::string logFileName = "Threaded.log";
        const auto logger = Logger(logFileName);
        logger.LogMessage(("Error: " + std::string(e.what())).c_str(), LogLevel::CRITICAL);
    }

    return 0;
}
