cmake_minimum_required(VERSION 3.12)
project(FaceDetection)

set(CMAKE_CXX_STANDARD 11)


include_directories(NAlgebra/header)
include_directories(stb/)

add_subdirectory(NAlgebra)

add_executable(FaceDetection main.cpp ImageMatrix.cpp ImageMatrix.h)

target_link_libraries(FaceDetection NAlgebra)