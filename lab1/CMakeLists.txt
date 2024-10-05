set(CMAKE_CXX_STANDARD 20)

add_executable(lab1 main.cpp include/lab1.h src/lab1.cpp)
add_executable(divergent src/divergent.cpp include/lab1.h)
target_include_directories(lab1 PRIVATE include)
target_include_directories(divergent PRIVATE include)