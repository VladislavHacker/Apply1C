cmake_minimum_required(VERSION 3.19)
project(1C)

set(CMAKE_CXX_STANDARD 20)

include(cmake/FetchLib.cmake)

file(MAKE_DIRECTORY ${PROJECT_SOURCE_DIR}/library)
FetchLib("https://github.com/google/googletest.git" gtest)
FetchLib("https://github.com/dtschump/CImg.git" CImg)

include_directories(${PROJECT_SOURCE_DIR}/project)
add_subdirectory(${PROJECT_SOURCE_DIR}/library/gtest)
# add_subdirectory(${PROJECT_SOURCE_DIR}/library/CImg)
add_executable(1C project/main.cpp)
# target_link_libraries(1C CImg)


add_executable(Test test/test.cpp)
target_link_libraries(Test gtest)