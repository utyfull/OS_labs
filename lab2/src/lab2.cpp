#include "lab2.h"

std::mutex mtx;                
int globalMin = std::numeric_limits<int>::max();  
int globalMax = std::numeric_limits<int>::min();

void FindMinMax(const std::vector<int>& arr, int start, int end) {
    int localMin = std::numeric_limits<int>::max();
    int localMax = std::numeric_limits<int>::min();

    for (int i = start; i < end; i++) {
        if (arr[i] < localMin) {
            localMin = arr[i];
        } 
        if (arr[i] > localMax) {
            localMax = arr[i];
        }
    }

    std::lock_guard<std::mutex> lock(mtx);
    if (localMin < globalMin) {
        globalMin = localMin;
    }
    if (localMax > globalMax) {
        globalMax = localMax;
    }
}

void FillVectorWithRandomValues(std::vector<int>& arr, int knownMin, int knownMax) {
    int size = arr.size();

    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % 1000;  
    }

    arr[0] = knownMin;
    arr[size - 1] = knownMax;
}

std::pair<int, int> FindMinMaxInArray(const std::vector<int>& array, int numThreads) {
    // if (numThreads > std::thread::hardware_concurrency()) {
    // numThreads = std::thread::hardware_concurrency();  
    // } защита от слишком большого колличества потоков, здесь не нужно 

    std::vector<std::thread> threads;
    int segmentSize = array.size() / numThreads;

    for (int i = 0; i < numThreads; ++i) {
        int start = i * segmentSize;
        int end = (i == numThreads - 1) ? array.size() : (i + 1) * segmentSize; 
        threads.emplace_back(FindMinMax, std::cref(array), start, end);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    return {globalMin, globalMax};
}