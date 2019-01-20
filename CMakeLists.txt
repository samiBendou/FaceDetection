cmake_minimum_required(VERSION 3.9.2)
project(FaceDetection)
include(gtest.cmake)

if (APPLE)
    add_definitions(-DGTEST_USE_OWN_TR1_TUPLE)
    add_definitions(-D__GLIBCXX__)
endif (APPLE)

set(CMAKE_CXX_STANDARD 11)

cmake_policy(SET CMP0023 OLD) # Allow mixed target_link_library

option(CODE_COVERAGE "Enable coverage reporting" OFF)

include_directories(NAlgebra/header/)
include_directories(stb/)
include_directories(IProcessing/)

add_subdirectory(NAlgebra)
add_subdirectory(IProcessing)



add_library(coverage_config INTERFACE)

set(CMAKE_CXX_FLAGS "-std=c++11 -g -O0 -Wall -Wextra -Wpedantic -Wswitch-enum -Wunreachable-code -Wwrite-strings -Wcast-align -Wshadow -Wundef --coverage ${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)

add_executable(IProcessingTest IMatrixTest.cpp PHaarTest.cpp)

# GTest needs threading support
find_package (Threads)
target_link_libraries(IProcessingTest NAlgebra IProcessing gtest ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(IProcessingTest INTERFACE --coverage)
