#include <benchmark/benchmark.h>

#include <random>

#include "kd_tree.h"

static void KDTreeFindNearest_Benchmark(benchmark::State& state) {
  constexpr std::size_t N_PTS = 100'000;
  constexpr std::size_t N = 2;
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(0.0, 1.0);

  std::vector<linear_alg::V<N>> pts;
  pts.resize(N_PTS);
  for (std::size_t i = 0; i < N_PTS; i++) {
    linear_alg::V<N> v;
    for (std::size_t j = 0; j < N; j++) {
      v(j) = dis(gen);
    }
    pts.emplace_back(v);
  }
  linear_alg::V<N> pt;
  for (std::size_t i = 0; i < N; i++) {
    pt(i) = dis(gen);
  }
  for (auto _ : state) {
    kd_tree::Tree<linear_alg::V<N>> tree{pts};
    tree.FindNearest(pt);
  }
}

BENCHMARK(KDTreeFindNearest_Benchmark);

BENCHMARK_MAIN();
