#ifndef LAB_2_H
#define LAB_2_H

#include <iostream>
#include <vector>
#include <thread>
#include <limits>
#include <cstdlib>
#include <mutex>
#include <algorithm>
#include <utility>
#include <chrono>

extern std::mutex mtx;
extern int globalMin;
extern int globalMax;

void FindMinMax(const std::vector<int>& arr, int start, int end);
void FillVectorWithRandomValues(std::vector<int>& arr, int knownMin, int knownMax);
std::pair<int, int> FindMinMaxInArray(const std::vector<int>& array, int numThreads);


#endif