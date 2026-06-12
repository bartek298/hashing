cmake_minimum_required(VERSION 3.29)
project(struktury_3)

set(CMAKE_CXX_STANDARD 11)

add_executable(struktury_3 main.cpp
        IHashTable.hpp
        SeparateChainingTable.hpp
        LinearProbingTable.hpp
        QuadraticProbingTable.hpp)
