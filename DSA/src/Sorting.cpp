#include "Sorting.hpp"

void Sorting::bubbleSort( ) const {
    logger.LogMessage( "Sorting with bubble sort", ArgoDraft::LogLevel::INFO );
    logger.LogMessage( "Unsorted array: ", ArgoDraft::LogLevel::INFO );

    std::string unsortedLog;
    for ( const auto &element : unsortedArray ) {
        unsortedLog += std::to_string( element ) + " ";
    }
    logger.LogMessage( unsortedLog.c_str( ), ArgoDraft::LogLevel::INFO );

    // Use bubble sort to sort the array
    std::vector< std::int16_t > sortedArray = unsortedArray;
    for ( std::size_t i = 0; i < sortedArray.size( ); ++i ) {
        logger.LogMessage( std::format( "Iteration {}", i ).c_str( ), ArgoDraft::LogLevel::DEBUG );
        for ( std::size_t j = 0; j < sortedArray.size( ) - i - 1; ++j ) {
            logger.LogMessage(
                    std::format( "Comparing elements {} and {}", sortedArray[j], sortedArray[j + 1] ).c_str( ),
                    ArgoDraft::LogLevel::DEBUG );

            if ( sortedArray[j] > sortedArray[j + 1] ) {
                logger.LogMessage(
                        std::format( "Swapping elements {} and {}", sortedArray[j], sortedArray[j + 1] ).c_str( ),
                        ArgoDraft::LogLevel::INFO );
                std::swap( sortedArray[j], sortedArray[j + 1] );
            }
        }
    }

    logger.LogMessage( "Sorted array: ", ArgoDraft::LogLevel::INFO );
    std::string sortedLog;
    for ( const auto &element : sortedArray ) {
        sortedLog += std::to_string( element ) + " ";
    }
    logger.LogMessage( sortedLog.c_str( ), ArgoDraft::LogLevel::INFO );
}

void Sorting::selectionSort( ) const {
    std::string unsortedLog;
    for ( const auto &element : unsortedArray ) {
        unsortedLog += std::to_string( element ) + " ";
    }
    logger.LogMessage( unsortedLog.c_str( ), ArgoDraft::LogLevel::INFO );

    // Use selection sort to sort the array
    std::vector< std::int16_t > sortedArray = unsortedArray;
    for ( std::size_t i = 0; i < sortedArray.size( ); ++i ) {
        std::size_t minIndex = i;

        logger.LogMessage( std::format( "Iteration {}", i ).c_str( ), ArgoDraft::LogLevel::DEBUG );
        logger.LogMessage( std::format( "Minimum index: {}", minIndex ).c_str( ), ArgoDraft::LogLevel::DEBUG );

        for ( std::size_t j = i + 1; j < sortedArray.size( ); ++j ) {
            logger.LogMessage(
                    std::format( "Comparing elements {} and {}", sortedArray[j], sortedArray[minIndex] ).c_str( ),
                    ArgoDraft::LogLevel::DEBUG );

            if ( sortedArray[j] < sortedArray[minIndex] ) {
                minIndex = j;

                logger.LogMessage( std::format( "New minimum index: {}", minIndex ).c_str( ),
                                   ArgoDraft::LogLevel::DEBUG );
            }
        }

        std::swap( sortedArray[i], sortedArray[minIndex] );
        logger.LogMessage( std::format( "Swapping elements {} and {}", sortedArray[i], sortedArray[minIndex] ).c_str( ),
                           ArgoDraft::LogLevel::INFO );
    }

    logger.LogMessage( "Sorted array: ", ArgoDraft::LogLevel::INFO );
    std::string sortedLog;
    for ( const auto &element : sortedArray ) {
        sortedLog += std::to_string( element ) + " ";
    }
    logger.LogMessage( sortedLog.c_str( ), ArgoDraft::LogLevel::INFO );
}

void Sorting::insertionSort( ) const {
    logger.LogMessage( "Sorting with insertion sort", ArgoDraft::LogLevel::INFO );
    logger.LogMessage( "Unsorted array: ", ArgoDraft::LogLevel::INFO );

    std::string unsortedLog;
    for ( const auto &element : unsortedArray ) {
        unsortedLog += std::to_string( element ) + " ";
    }
    logger.LogMessage( unsortedLog.c_str( ), ArgoDraft::LogLevel::INFO );

    // Use insertion sort to sort the array
    std::vector< std::int16_t > sortedArray = unsortedArray;
    for ( std::size_t i = 1; i < sortedArray.size( ); ++i ) {
        std::int16_t key = sortedArray[i];
        std::size_t  j   = i - 1;

        logger.LogMessage( std::format( "Iteration {}", i ).c_str( ), ArgoDraft::LogLevel::DEBUG );
        logger.LogMessage( std::format( "Key: {}", key ).c_str( ), ArgoDraft::LogLevel::DEBUG );

        while ( j >= 0 && sortedArray[j] > key ) {
            logger.LogMessage( std::format( "Comparing elements {} and {}", sortedArray[j], key ).c_str( ),
                               ArgoDraft::LogLevel::DEBUG );

            sortedArray[j + 1] = sortedArray[j];
            logger.LogMessage( std::format( "Moving element {} to position {}", sortedArray[j], j + 1 ).c_str( ),
                               ArgoDraft::LogLevel::INFO );

            --j;
        }

        sortedArray[j + 1] = key;
        logger.LogMessage( std::format( "Inserting key {} at position {}", key, j + 1 ).c_str( ),
                           ArgoDraft::LogLevel::INFO );
    }
}

void Sorting::mergeSort( ) {}

void Sorting::quickSort( ) {}

void Sorting::heapSort( ) {}

void Sorting::countingSort( ) {}

void Sorting::radixSort( ) {}

void Sorting::bucketSort( ) {}

void Sorting::shellSort( ) {}

void Sorting::cocktailSort( ) {}

void Sorting::combSort( ) {}

void Sorting::gnomeSort( ) {}

void Sorting::oddEvenSort( ) {}

void Sorting::stoogeSort( ) {}

void Sorting::pigeonholeSort( ) {}

void Sorting::cycleSort( ) {}

void Sorting::bitonicSort( ) {}

void Sorting::pancakeSort( ) {}

void Sorting::bogoSort( ) {}

void Sorting::sleepSort( ) {}

void Sorting::timSort( ) {}

void Sorting::introSort( ) {}

void Sorting::smoothSort( ) {}

void Sorting::flashSort( ) {}

void Sorting::blockSort( ) {}

void Sorting::librarySort( ) {}

void Sorting::strandSort( ) {}

void Sorting::patienceSort( ) {}

void Sorting::spreadSort( ) {}

void Sorting::cubeSort( ) {}
