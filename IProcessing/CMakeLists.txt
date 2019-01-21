cmake_minimum_required(VERSION 3.9)
project(ImageProcessing)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)
include_directories(../NAlgebra)
include_directories(../stb)

add_library(IProcessing STATIC IMatrix.cpp IMatrix.h PHaar.cpp PHaar.h WClassifier.cpp WClassifier.h)