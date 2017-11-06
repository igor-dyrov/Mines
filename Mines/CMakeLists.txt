cmake_minimum_required(VERSION 3.8)
project(Mines)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp settings.cpp)
add_executable(Mines ${SOURCE_FILES})