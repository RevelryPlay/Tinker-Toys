#include <chrono>
#include <thread>

#include <ArgoDraft/ArgoLogger.hpp>
#include <ArgoDraft/ConsoleMenu.hpp>

#include "src/ThreadPool.hpp"

using namespace ArgoDraft;

void LogDuration( const std::chrono::high_resolution_clock::time_point &startTime,
                  const std::chrono::high_resolution_clock::time_point &endTime, const Logger &logger ) {
    const auto duration = std::chrono::duration_cast< std::chrono::milliseconds >( endTime - startTime );

    // Log the duration formating into minutes, seconds, and milliseconds
    const auto minutes      = std::chrono::duration_cast< std::chrono::minutes >( duration );
    const auto seconds      = std::chrono::duration_cast< std::chrono::seconds >( duration ) % 60;
    const auto milliseconds = duration % 1000;

    logger.LogMessage( std::format( "Duration: {} minutes, {} seconds, {} milliseconds", minutes.count( ),
                                    seconds.count( ), milliseconds.count( ) )
                               .c_str( ),
                       LogLevel::INFO );
}

const int numThreads = std::thread::hardware_concurrency( );
// constexpr int numThreads = 1;

int main( ) {
    try {
        MainMenu menu;

        // Fibonacci thread pool test
        menu.AddAction( { "fib", "Fibonacci thread pool test", []( ) {
                             constexpr auto iterations   = 50000;
                             constexpr auto maxFibonacci = 90; // Overflows at 93

                             // Starting timer
                             const auto startTime = std::chrono::high_resolution_clock::now( );

                             const std::string logFileName = "Threaded.log";
                             auto              logger      = Logger( logFileName );
                             logger.SetFileLogLevel( LogLevel::INFO );
                             logger.SetConsoleLogLevel( LogLevel::INFO );

                             logger.LogMessage( "Starting Fibonacci ThreadPool test", LogLevel::INFO );

                             logger.LogMessage( std::format( "Number of threads: {}", numThreads ).c_str( ),
                                                LogLevel::INFO );

                             logger.LogMessage( "Creating ThreadPool", LogLevel::INFO );
                             ThreadPool pool( numThreads );

                             for ( int i = 0; i < iterations; i++ ) {
                                 pool.Enqueue( [i, &logger] {
                                     logger.LogMessage( std::format( "Task {} started on thread {}", i,
                                                                     std::this_thread::get_id( ) )
                                                                .c_str( ),
                                                        LogLevel::INFO );

                                     std::vector< long long > fib( maxFibonacci + 1 );
                                     fib[0] = 0;
                                     fib[1] = 1;

                                     for ( int i = 2; i <= maxFibonacci; i++ ) {
                                         fib[i] = fib[i - 1] + fib[i - 2];
                                         logger.LogMessage( std::format( "Fibonacci({}) = {}, thread {}", i, fib[i],
                                                                         std::this_thread::get_id( ) )
                                                                    .c_str( ),
                                                            LogLevel::INFO );
                                     }

                                     logger.LogMessage( std::format( "Task {} finished on thread {}", i,
                                                                     std::this_thread::get_id( ) )
                                                                .c_str( ),
                                                        LogLevel::INFO );
                                 } );
                             }

                             // check if any threads are still running
                             while ( pool.HasTasks( ) ) {
                                 std::this_thread::sleep_for( std::chrono::milliseconds( 100 ) );
                             }

                             // Ending timer
                             const auto endTime = std::chrono::high_resolution_clock::now( );
                             LogDuration( startTime, endTime, logger );
                         } } );

        // Prime numbers thread pool test
        menu.AddAction(
                { "prime", "Prime numbers thread pool test", []( ) {
                     // Starting timer
                     const auto startTime = std::chrono::high_resolution_clock::now( );

                     const std::string logFileName = "Threaded.log";
                     auto              logger      = Logger( logFileName );
                     logger.SetFileLogLevel( LogLevel::INFO );
                     logger.SetConsoleLogLevel( LogLevel::INFO );

                     logger.LogMessage( "Starting prime numbers ThreadPool test", LogLevel::INFO );

                     logger.LogMessage( std::format( "Number of threads: {}", numThreads ).c_str( ), LogLevel::INFO );

                     logger.LogMessage( "Creating ThreadPool", LogLevel::INFO );
                     ThreadPool pool( numThreads );

                     for ( int i = 0; i < 1000000; i++ ) {
                         pool.Enqueue( [i, &logger] {
                             logger.LogMessage(
                                     std::format( "Task {} started on thread {}", i, std::this_thread::get_id( ) )
                                             .c_str( ),
                                     LogLevel::INFO );

                             bool isPrime = true;
                             for ( int j = 2; j <= i / 2; j++ ) {
                                 if ( i % j == 0 ) {
                                     isPrime = false;
                                     break;
                                 }
                             }

                             if ( isPrime ) {
                                 logger.LogMessage( std::format( "Task {} is prime", i ).c_str( ), LogLevel::INFO );
                             }

                             logger.LogMessage(
                                     std::format( "Task {} finished on thread {}", i, std::this_thread::get_id( ) )
                                             .c_str( ),
                                     LogLevel::INFO );
                         } );
                     }

                     // check if any threads are still running
                     while ( pool.HasTasks( ) ) {
                         std::this_thread::sleep_for( std::chrono::milliseconds( 100 ) );
                     }

                     // Ending timer
                     const auto endTime = std::chrono::high_resolution_clock::now( );
                     LogDuration( startTime, endTime, logger );
                 } } );

        // Minimal thread pool test
        menu.AddAction( { "minimal", "A minimal thread pool test", []( ) {
                             // Starting timer
                             const auto startTime = std::chrono::high_resolution_clock::now( );

                             const std::string logFileName = "Threaded.log";
                             auto              logger      = Logger( logFileName );
                             logger.SetFileLogLevel( LogLevel::INFO );
                             logger.SetConsoleLogLevel( LogLevel::INFO );

                             logger.LogMessage( "Starting minimal ThreadPool test", LogLevel::INFO );

                             logger.LogMessage( std::format( "Number of threads: {}", numThreads ).c_str( ),
                                                LogLevel::INFO );

                             logger.LogMessage( "Creating ThreadPool", LogLevel::INFO );
                             ThreadPool pool( numThreads );

                             for ( int i = 0; i < 100; i++ ) {
                                 pool.Enqueue( [i, &logger] {
                                     logger.LogMessage( std::format( "Task {} started on thread {}", i,
                                                                     std::this_thread::get_id( ) )
                                                                .c_str( ),
                                                        LogLevel::INFO );
                                     std::this_thread::sleep_for( std::chrono::seconds( 1 ) );
                                     logger.LogMessage( std::format( "Task {} finished on thread {}", i,
                                                                     std::this_thread::get_id( ) )
                                                                .c_str( ),
                                                        LogLevel::INFO );
                                 } );
                             }

                             // check if any threads are still running
                             while ( pool.HasTasks( ) ) {
                                 std::this_thread::sleep_for( std::chrono::milliseconds( 100 ) );
                             }

                             // Ending timer
                             const auto endTime = std::chrono::high_resolution_clock::now( );
                             LogDuration( startTime, endTime, logger );
                         } } );

        menu.Init( );
    } catch ( const std::exception &e ) {
        const std::string logFileName = "Threaded.log";
        const auto        logger      = Logger( logFileName );
        logger.LogMessage( ( "Error: " + std::string( e.what( ) ) ).c_str( ), LogLevel::CRITICAL );
    }

    return 0;
}
