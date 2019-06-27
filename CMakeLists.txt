cmake_minimum_required(VERSION 3.13)
project(leetcode)

file(GLOB Sources *.cpp Concepts/*.cpp DataStructure/*.cpp MetaProgram/*.cpp test/*.cpp)
file(GLOB Includes *.h Concepts/*.h DataStructure/*.h MetaProgram/*.h test/*.h)

find_package(OpenCV REQUIRED)
message("opencv include " ${OpenCV_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 14)

add_executable(leetcode ${Sources} ${Includes} Concepts/design_pattern.cpp Concepts/design_pattern.h test/test_design_pattern.cpp test/test_design_pattern.h)
include_directories( ${OpenCV_INCLUDE_DIRS} )
target_link_libraries( leetcode ${OpenCV_LIBS})
