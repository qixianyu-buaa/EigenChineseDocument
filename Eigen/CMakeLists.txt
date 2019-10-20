cmake_minimum_required(VERSION 2.8.3)
project(EigenTutorial)

add_compile_options(-std=c++11)
include_directories(
    /usr/include/eigen3/    # 若你的Eigen不是这个目录，请把此目录改为你的位置
    ./Chapter1_DenseMatrixAndArray/
    ./Chapter2_DenseLinearProblemsAndDecompositions/
    )

add_executable(chapter1_test chapter1_test.cpp)  #编译第一章

add_executable(chapter2_test chapter2_test.cpp)  #编译第二章
