cmake_minimum_required(VERSION 3.10)
project(PSO_algorithm)

set(CMAKE_CXX_STANDARD 17)

add_executable(PSO_algorithm
    main.cpp
    src/utils.cpp
    src/particle.cpp
)
