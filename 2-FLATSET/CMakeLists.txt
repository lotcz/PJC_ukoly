cmake_minimum_required(VERSION 3.12)
project(2_FLATSET)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(2_FLATSET
        flatset.hpp
        tests-main.cpp
        tests-helpers.cpp
        test_flatset.cpp)
