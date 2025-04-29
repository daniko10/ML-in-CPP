cmake_minimum_required(VERSION 3.10)
project(genetic_algorithm_tests)

set(CMAKE_CXX_STANDARD 17)

set(GTEST_INCLUDE_DIR "/mnt/d/MinGW/googletest/googletest/include")
set(GTEST_LIB_DIR "/mnt/d/MinGW/googletest/build/lib")

include_directories(
    ${GTEST_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

file(GLOB TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB UTILS_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/../src/*.cpp")

add_executable(genetic_algorithm_tests ${TEST_SOURCES} ${UTILS_SOURCES})

target_link_directories(genetic_algorithm_tests PRIVATE ${GTEST_LIB_DIR})
target_link_libraries(genetic_algorithm_tests
    gtest
    gtest_main
    pthread
)
