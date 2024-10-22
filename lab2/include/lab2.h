#ifndef LAB_2_H
#define LAB_2_H

#include <iostream>
#include <vector>
#include <thread>
#include <limits>
#include <cstdlib>
#include <algorithm>
#include <utility>
#include <chrono>
#include <pthread.h>

struct Var {
    int globalMin;
    int globalMax;
    pthread_mutex_t mutex;
};

struct ThreadData {
    const std::vector<int>* arr;
    std::size_t start;
    std::size_t end;
    Var* var;
};

void FindMinMax(const std::vector<int>& arr, int start, int end, struct Var var);
void FillVectorWithRandomValues(std::vector<int>& arr, int knownMin, int knownMax);
std::pair<int, int> FindMinMaxInArray(const std::vector<int>& array, int numThreads);


#endif