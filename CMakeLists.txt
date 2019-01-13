cmake_minimum_required(VERSION 3.9.2)
project(FaceDetection)
include(gtest.cmake)

if (APPLE)
    add_definitions(-DGTEST_USE_OWN_TR1_TUPLE)
    add_definitions(-D__GLIBCXX__)
endif (APPLE)

set(CMAKE_CXX_STANDARD 11)

include_directories(NAlgebra/header)
include_directories(stb/)
include_directories(./)

add_subdirectory(NAlgebra)




cmake_policy(SET CMP0023 OLD) # Allow mixed target_link_library

set(CMAKE_CXX_FLAGS "-g -O0 -Wall -Werror -Wextra -Wpedantic -Wconversion -Wswitch-default -Wswitch-enum -Wunreachable-code -Wwrite-strings -Wcast-align -Wshadow -Wundef --coverage ${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)


SET(COVERAGE OFF CACHE BOOL "Coverage")

add_executable(ImageMatrixTest ImageMatrixTest.cpp)

SET(COVERAGE OFF CACHE BOOL "Coverage")

# GTest needs threading support
find_package (Threads)
target_link_libraries(ImageMatrixTest NAlgebra gtest ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(ImageMatrixTest PRIVATE --coverage)