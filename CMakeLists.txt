cmake_minimum_required(VERSION 3.16)
project(IO-Benchmarker)

set(CMAKE_CXX_STANDARD 20)

include_directories("include")
include_directories("src")

set(HEADERS include/Reader.hpp include/Writer.hpp include/helpers.hpp)
set(SOURCES src/Reader.cpp src/Writer.cpp)

add_executable(IO-Benchmarker ${HEADERS} ${SOURCES} main.cpp)