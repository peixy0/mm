set(TESTS_SOURCES
  kd_tree_tests.cpp
  linear_alg_tests.cpp
  ut_main.cpp)

add_executable(${MODULE_NAME}_tests
  ${TESTS_SOURCES})

target_link_libraries(${MODULE_NAME}_tests
  PRIVATE
  GSL
  GTest::gtest)

set(BENCHMARK_SOURCES
  kd_tree_benchmark.cpp)

add_executable(${MODULE_NAME}_benchmark
  ${BENCHMARK_SOURCES})

target_link_libraries(${MODULE_NAME}_benchmark
  PRIVATE
  GSL
  benchmark::benchmark)
