project("Tests")

add_executable(test_lab1 test_lab1.cpp)
target_link_libraries(test_lab1 gtest gtest_main pthread)
add_test(NAME test_lab1 COMMAND test_lab1)