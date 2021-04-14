cmake_minimum_required(VERSION 3.19)
project(1C)

set(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_FLAGS -pthread)

include(cmake/FetchLib.cmake)

file(MAKE_DIRECTORY ${PROJECT_SOURCE_DIR}/library)
FetchLib("https://github.com/google/googletest.git" gtest)

include_directories(${PROJECT_SOURCE_DIR}/project)
add_subdirectory(${PROJECT_SOURCE_DIR}/library/gtest)

add_executable(1C project/lodepng.cpp project/main.cpp)

add_executable(Test test/test.cpp)
target_link_libraries(Test gtest)