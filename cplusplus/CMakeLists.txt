cmake_minimum_required (VERSION 2.6)
project (Djson)

add_library(djson src/Json.cpp src/Json.h)

add_executable(main test.cpp)


