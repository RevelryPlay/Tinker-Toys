#pragma once

#include <vector>
#include <format>

#include <ArgoDraft/ArgoLogger.hpp>

class Sorting {
public:
    Sorting() {
        logger = ArgoDraft::Logger(logFileName);
        logger.SetFileLogLevel(ArgoDraft::LogLevel::INFO);
        logger.SetConsoleLogLevel(ArgoDraft::LogLevel::INFO);
    }

    ~Sorting() = default;
    
    void bubbleSort() const;
    void selectionSort() const;
    void insertionSort() const;
    void mergeSort();
    void quickSort();
    void heapSort();
    void countingSort();
    void radixSort();
    void bucketSort();
    void shellSort();
    void cocktailSort();
    void combSort();
    void gnomeSort();
    void oddEvenSort();
    void stoogeSort();
    void pigeonholeSort();
    void cycleSort();
    void bitonicSort();
    void pancakeSort();
    void bogoSort();
    void sleepSort();
    void timSort();
    void introSort();
    void smoothSort();
    void flashSort();
    void blockSort();
    void librarySort();
    void strandSort();
    void patienceSort();
    void spreadSort();
    void cubeSort();

private:
    const std::vector<std::int16_t> unsortedArray = {
        64, 34, 25, 12, 22, 11, 90, 1, 0, 100, 99, 98, 97, 96, 95, 94, 93, 92, 91, 89, 88, 87, 86, 85, 84,
        83, 82, 81, 80, 79, 78, 77, 76, 75, 74, 73, 72, 71, 70, 69, 68, 67, 66, 65, 63, 62, 61, 60, 59, 58,
        57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 33, 32,
        31, 30, 29, 28, 27, 26, 24, 23, 21, 20, 19, 18, 17, 16, 15, 14, 13, 10, 9, 8, 7, 6, 5, 4, 3, 2
    };
    
    std::string logFileName = "Sorting.log";
    ArgoDraft::Logger logger;
};
