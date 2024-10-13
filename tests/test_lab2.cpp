#include <gtest/gtest.h>
#include "lab2.h"

TEST(ThreadTest, standartRandonCombination) {
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