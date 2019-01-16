cmake_minimum_required(VERSION 3.13)
project(person-database)

set(CMAKE_CXX_STANDARD 14)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/out)

add_executable(person-database main.cpp)