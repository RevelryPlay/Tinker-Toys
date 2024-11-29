#include <chrono>
#include <format>
#include <iostream>
#include <thread>
#include <ArgoDraft/ArgoLogger.hpp>
#include <ArgoDraft/ConsoleMenu.hpp>

#include "src/ThreadPool.hpp"

int main() {
    try {
        ArgoDraft::MainMenu menu;
        menu.AddAction({"log", "Logs a message", []() {
                const std::string logFileName = "Threaded.log";
                auto logger = ArgoDraft::Logger(logFileName);
                const auto lang = "C++";

                logger.SetFileLogLevel(ArgoDraft::LogLevel::INFO);
                logger.SetConsoleLogLevel(ArgoDraft::LogLevel::INFO);

                logger.LogMessage(std::format("Hello and welcome to {}!", lang).c_str(), ArgoDraft::LogLevel::INFO);

                for (int i = 1; i <= 10; i++) {
                    logger.LogMessage(std::format("i {}!", i).c_str(), ArgoDraft::LogLevel::INFO);
                }
            }});

        menu.AddAction({"thread-sleep", "Test of ThreadPool using sleep", []() {
                const std::string logFileName = "Threaded.log";
                auto logger = ArgoDraft::Logger(logFileName);
                logger.SetFileLogLevel(ArgoDraft::LogLevel::INFO);
                logger.SetConsoleLogLevel(ArgoDraft::LogLevel::INFO);

                const auto numThreads = std::thread::hardware_concurrency();
                logger.LogMessage("Starting ThreadPool sleep test", ArgoDraft::LogLevel::INFO);
                logger.LogMessage(std::format("Number of threads: {}", numThreads).c_str(), ArgoDraft::LogLevel::INFO);

                const auto startTime = std::chrono::high_resolution_clock::now();
                logger.LogMessage(std::format("Starting time: {}", startTime).c_str(), ArgoDraft::LogLevel::INFO);

                logger.LogMessage("Creating ThreadPool", ArgoDraft::LogLevel::INFO);
                ThreadPool pool(numThreads);

                for (int i = 0; i < 100; i++) {
                    pool.Enqueue([i, &logger] {
                        logger.LogMessage(std::format("Task {} started", i).c_str(), ArgoDraft::LogLevel::INFO);
                        std::this_thread::sleep_for(std::chrono::seconds(1));
                        logger.LogMessage(std::format("Task {} finished", i).c_str(), ArgoDraft::LogLevel::INFO);
                    });
                }

                std::this_thread::sleep_for(std::chrono::seconds(11));

                const auto endTime = std::chrono::high_resolution_clock::now();
                logger.LogMessage(std::format("Ending time: {}", endTime).c_str(), ArgoDraft::LogLevel::INFO);
            }});
        menu.AddAction({"thread-prime", "Test of ThreadPool using prime numbers", []() {
                const std::string logFileName = "Threaded.log";
                auto logger = ArgoDraft::Logger(logFileName);
                logger.SetFileLogLevel(ArgoDraft::LogLevel::INFO);
                logger.SetConsoleLogLevel(ArgoDraft::LogLevel::INFO);

                const auto numThreads = std::thread::hardware_concurrency();
                logger.LogMessage("Starting ThreadPool prime number test", ArgoDraft::LogLevel::INFO);
                logger.LogMessage(std::format("Number of threads: {}", numThreads).c_str(), ArgoDraft::LogLevel::INFO);

                const auto startTime = std::chrono::high_resolution_clock::now();
                logger.LogMessage(std::format("Starting time: {}", startTime).c_str(), ArgoDraft::LogLevel::INFO);

                logger.LogMessage("Creating ThreadPool", ArgoDraft::LogLevel::INFO);
                ThreadPool pool(numThreads);

                for (int i = 0; i < 100; i++) {
                    pool.Enqueue([i, &logger] {
                        logger.LogMessage(std::format("Task {} started", i).c_str(), ArgoDraft::LogLevel::INFO);

                        constexpr auto n = 100000;
                        std::vector<bool> isPrime(n + 1, true);
                        isPrime[0] = isPrime[1] = false;

                        for (int i = 2; i * i <= n; i++) {
                            if (isPrime[i]) {
                                for (int j = i * i; j <= n; j += i) {
                                    isPrime[j] = false;
                                }
                            }
                        }

                        logger.LogMessage(std::format("Task {} finished", i).c_str(), ArgoDraft::LogLevel::INFO);
                    });
                }

                std::this_thread::sleep_for(std::chrono::seconds(11));

                const auto endTime = std::chrono::high_resolution_clock::now();
                logger.LogMessage(std::format("Ending time: {}", endTime).c_str(), ArgoDraft::LogLevel::INFO);

                const auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
                logger.LogMessage(std::format("Duration: {} milliseconds", duration.count()).c_str(),
                                  ArgoDraft::LogLevel::INFO);
            }});
        menu.AddAction({"thread-fibonacci", "Test of ThreadPool using fibonacci numbers", []() {
            const std::string logFileName = "Threaded.log";
            auto logger = ArgoDraft::Logger(logFileName);
            logger.SetFileLogLevel(ArgoDraft::LogLevel::INFO);
            logger.SetConsoleLogLevel(ArgoDraft::LogLevel::INFO);

            const auto numThreads = std::thread::hardware_concurrency();
            logger.LogMessage("Starting ThreadPool fibonacci number test", ArgoDraft::LogLevel::INFO);
            logger.LogMessage(std::format("Number of threads: {}", numThreads).c_str(), ArgoDraft::LogLevel::INFO);

            const auto startTime = std::chrono::high_resolution_clock::now();
            logger.LogMessage(std::format("Starting time: {}", startTime).c_str(), ArgoDraft::LogLevel::INFO);

            logger.LogMessage("Creating ThreadPool", ArgoDraft::LogLevel::INFO);
            ThreadPool pool(numThreads);

            for (int i = 0; i < 100; i++) {
                pool.Enqueue([i, &logger] {
                    logger.LogMessage(std::format("Task {} started", i).c_str(), ArgoDraft::LogLevel::INFO);

                    constexpr auto n = 100000;
                    std::vector<long long> fib(n + 1);
                    fib[0] = 0;
                    fib[1] = 1;

                    for (int i = 2; i <= n; i++) {
                        fib[i] = fib[i - 1] + fib[i - 2];
                    }

                    logger.LogMessage(std::format("Task {} finished", i).c_str(), ArgoDraft::LogLevel::INFO);
                });
            }

            std::this_thread::sleep_for(std::chrono::seconds(11));

            const auto endTime = std::chrono::high_resolution_clock::now();
            logger.LogMessage(std::format("Ending time: {}", endTime).c_str(), ArgoDraft::LogLevel::INFO);

            const auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
            logger.LogMessage(std::format("Duration: {} milliseconds", duration.count()).c_str(), ArgoDraft::LogLevel::INFO);
        }});
        
        menu.Init();
    } catch (const std::exception &e) {
        const std::string logFileName = "Threaded.log";
        const auto logger = ArgoDraft::Logger(logFileName);
        logger.LogMessage(("Error: " + std::string(e.what())).c_str(), ArgoDraft::LogLevel::CRITICAL);
    }

    return 0;
}
