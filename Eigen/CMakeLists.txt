cmake_minimum_required(VERSION 2.8.3)
project(test_eigen)
add_compile_options(-std=c++11)

include_directories(
    /usr/include/eigen3/ 
    ./Chapter1_DenseMatrixAndArray/
    )

add_executable(chapter1_test chapter1_test.cpp)