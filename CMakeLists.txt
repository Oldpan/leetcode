cmake_minimum_required(VERSION 3.13)
project(leetcode)

file(GLOB Sources *.cpp Concepts/*.cpp DataStructure/*.cpp MetaProgram/*.cpp test/*.cpp)
file(GLOB Includes *.h Concepts/*.h DataStructure/*.h MetaProgram/*.h test/*.h)

find_package(OpenCV REQUIRED)
message("opencv include " ${OpenCV_INCLUDE_DIRS})

FIND_PACKAGE( OpenMP REQUIRED)
if(OPENMP_FOUND)
    message("OPENMP FOUND")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

set(CMAKE_CXX_STANDARD 14)

add_executable(leetcode ${Sources} ${Includes})
include_directories( ${OpenCV_INCLUDE_DIRS} )
target_link_libraries( leetcode ${OpenCV_LIBS} pthread)
