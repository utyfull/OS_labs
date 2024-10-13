#include "lab2.h"

int main() {
    int arraySize = 1000000000;  
    int numThreads = 64;       
    std::vector<int> array(arraySize);
    int knownMin = -500;
    int knownMax = 1500;

    FillVectorWithRandomValues(array, knownMin, knownMax);

    auto startTime = std::chrono::high_resolution_clock::now();
    std::pair<int, int> result = FindMinMaxInArray(array, numThreads);
    auto endTime = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsedTime = endTime - startTime;

    std::cout << "Found Min: " << result.first << std::endl;
    std::cout << "Found Max: " << result.second << std::endl;
    std::cout << "Time taken: " << elapsedTime.count() << " seconds" << std::endl;

    return 0;
}