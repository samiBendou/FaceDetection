cmake_minimum_required(VERSION 3.12)
project(FaceDetection)
include(gtest.cmake)

set(CMAKE_CXX_STANDARD 11)

include_directories(NAlgebra/header)
include_directories(stb/)

add_subdirectory(NAlgebra)

add_executable(FaceDetection main.cpp ImageMatrix.cpp ImageMatrix.h)

add_executable(ImageMatrixTest ImageMatrixTest.cpp)


# GTest needs threading support
find_package (Threads)
target_link_libraries(ImageMatrixTest NAlgebra gtest ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(FaceDetection NAlgebra)
