cmake_minimum_required(VERSION 3.10)
project(1C)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS -pthread)

include(cmake/FetchLib.cmake)

file(MAKE_DIRECTORY ${PROJECT_SOURCE_DIR}/library)
include_directories(${PROJECT_SOURCE_DIR}/project)

add_executable(1C project/lodepng.cpp project/main.cpp)
