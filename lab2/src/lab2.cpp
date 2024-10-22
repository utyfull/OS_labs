#include "lab2.h"

void* FindMinMax(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    const std::vector<int>& arr = *(data->arr);
    int localMin = std::numeric_limits<int>::max();
    int localMax = std::numeric_limits<int>::min();

    for (std::size_t i = data->start; i < data->end; i++) {
        if (arr[i] < localMin) {
            localMin = arr[i];
        }
        if (arr[i] > localMax) {
            localMax = arr[i];
        }
    }

    pthread_mutex_lock(&data->var->mutex);
    if (localMin < data->var->globalMin) {
        data->var->globalMin = localMin;
    }
    if (localMax > data->var->globalMax) {
        data->var->globalMax = localMax;
    }
    pthread_mutex_unlock(&data->var->mutex);

    return NULL;
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
    Var var;
    var.globalMin = std::numeric_limits<int>::max();  
    var.globalMax = std::numeric_limits<int>::min();

    pthread_mutex_init(&var.mutex, NULL);

    std::size_t segmentSize = array.size() / numThreads; 
    std::vector<pthread_t> threads(numThreads);  
    std::vector<ThreadData> threadData(numThreads); 

    for (int i = 0; i < numThreads; ++i) {
        threadData[i] = {
            &array,
            i * segmentSize,
            (i == numThreads - 1) ? array.size() : (i + 1) * segmentSize,
            &var
        };
        pthread_create(&threads[i], NULL, FindMinMax, (void*)&threadData[i]);
    }

    for (int i = 0; i < numThreads; ++i) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&var.mutex);

    return {var.globalMin, var.globalMax};
}

