cmake_minimum_required(VERSION 3.10)
project(genetic_algorithm)

set(CMAKE_CXX_STANDARD 17)

add_executable(genetic_algorithm
    main.cpp
    src/utils.cpp
    src/genetic.cpp
)
