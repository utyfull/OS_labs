set(CMAKE_CXX_STANDARD 20)

add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

add_executable(test_lab1 test_lab1.cpp ../lab1/src/lab1.cpp ../lab1/include/lab1.h)
target_link_libraries(test_lab1 PRIVATE GTest::GTest)
target_include_directories(test_lab1 PRIVATE ../lab1/include)

add_test(NAME test_lab1 COMMAND test_lab1)