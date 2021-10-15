cmake_minimum_required(VERSION 3.21)

PROJECT(mm)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(BENCHMARK_ENABLE_GTEST_TESTS OFF)
add_subdirectory(externals/google-benchmark)
add_subdirectory(externals/google-test)
add_subdirectory(externals/gsl)

add_compile_options(-Wall -Wextra -pedantic -Werror)

set(MODULE_NAME mm)

include_directories(include)

add_subdirectory(tests)
