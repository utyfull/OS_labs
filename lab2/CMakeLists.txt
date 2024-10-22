set(CMAKE_CXX_STANDARD 20)

add_executable(lab2 main.cpp include/lab2.h src/lab2.cpp)
target_include_directories(lab2 PRIVATE include)
include(FindThreads)