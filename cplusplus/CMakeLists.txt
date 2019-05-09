cmake_minimum_required (VERSION 2.6)
project (Djson)

add_library(
    djson 
    src/Common.h
    src/Json.cpp 
    src/Json.h
    src/Value.cpp 
    src/Value.h
)

add_executable(
    main 
    test.cpp
)

target_link_libraries(main djson)
