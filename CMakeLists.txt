cmake_minimum_required(VERSION 3.13)
project(leetcode)

set(CMAKE_CXX_STANDARD 14)

add_executable(leetcode main.cpp utils.cpp utils.h Concepts/concepts.cpp Concepts/concepts.h DataStructure/linearlist.cpp DataStructure/linearlist.h)