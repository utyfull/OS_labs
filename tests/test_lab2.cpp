#include <gtest/gtest.h>
#include "lab2.h"

TEST(ThreadTest, Randon16Threads) {
    int arraySize = 1000000000;  
    int numThreads = 16;       
    std::vector<int> array(arraySize);
    int knownMin = -500;
    int knownMax = 1500;
    std::pair<int, int> expect = {knownMin, knownMax};

    FillVectorWithRandomValues(array, knownMin, knownMax);
    std::pair<int, int> result = FindMinMaxInArray(array, numThreads);

    EXPECT_EQ(result, expect);
}

TEST(ThreadTest, Randon1Thread) {
    int arraySize = 1000000000;  
    int numThreads = 1;       
    std::vector<int> array(arraySize);
    int knownMin = -500;
    int knownMax = 1500;
    std::pair<int, int> expect = {knownMin, knownMax};

    FillVectorWithRandomValues(array, knownMin, knownMax);
    std::pair<int, int> result = FindMinMaxInArray(array, numThreads);

    EXPECT_EQ(result, expect);
}

TEST(ThreadTest, Eq1ThreadAnd16ThreadsResult) {
    int arraySize = 1000000000;  
    int numThreads1 = 1;   
    int numThreads2 = 16;    
    std::vector<int> array(arraySize);
    int knownMin = -500;
    int knownMax = 1500;

    FillVectorWithRandomValues(array, knownMin, knownMax);
    std::pair<int, int> result1 = FindMinMaxInArray(array, numThreads1);
    std::pair<int, int> result2 = FindMinMaxInArray(array, numThreads2);

    EXPECT_EQ(result1, result2);
}

TEST(ThreadTest, OneThreadvs16Threads) {
    int arraySize = 1000000000;  
    int numThreads1 = 1;    
    int numThreads2 = 16;   
    std::vector<int> array(arraySize);
    int knownMin = -500;
    int knownMax = 1500;

    FillVectorWithRandomValues(array, knownMin, knownMax);

    auto startTime1 = std::chrono::high_resolution_clock::now();
    std::pair<int, int> result1 = FindMinMaxInArray(array, numThreads1);
    auto endTime1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsedTime1 = endTime1 - startTime1;

    auto startTime2 = std::chrono::high_resolution_clock::now();
    std::pair<int, int> result2 = FindMinMaxInArray(array, numThreads2);
    auto endTime2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsedTime2 = endTime2 - startTime2;

    EXPECT_TRUE(elapsedTime1 > elapsedTime2 && result1 == result2);
}