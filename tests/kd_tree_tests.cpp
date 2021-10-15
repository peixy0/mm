#include "gtest/gtest.h"
#include "kd_tree.h"

TEST(KDTreeTests, whenFindingNearestNode_willProduceCorrectResult) {
  std::vector<linear_alg::V<2>> pts{{2, 3}, {5, 4}, {9, 6}, {4, 7}, {8, 1}, {7, 2}};
  kd_tree::Tree<linear_alg::V<2>> tree{pts};
  auto n = tree.FindNearest({9, 2});
  linear_alg::V<2> expected{8, 1};
  ASSERT_EQ(n, expected);
}
