#include "gtest/gtest.h"
#include "linear_alg.h"

TEST(LinearAlgMatrixTests, identityMatrixCreation_willProduceCorrectResult) {
  auto m = linear_alg::M<3, 3>::Identity();
  linear_alg::M<3, 3> expected{1, 0, 0, 0, 1, 0, 0, 0, 1};
  ASSERT_EQ(m, expected);
}

TEST(LinearAlgMatrixTests, whenMatrixIsTransposed_willProduceCorrectResult) {
  linear_alg::M<3, 3> m{1, 2, 3, 4, 5, 6, 7, 8, 9};
  linear_alg::M<3, 3> expected{1, 4, 7, 2, 5, 8, 3, 6, 9};
  ASSERT_EQ(m.T(), expected);
}

TEST(LinearAlgMatrixTests, matrixMultiplication_willProduceCorrectResult) {
  linear_alg::M<3, 4> m{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
  linear_alg::M<3, 3> expected{30, 70, 110, 70, 174, 278, 110, 278, 446};
  ASSERT_EQ(m * m.T(), expected);
}

TEST(LinearAlgMatrixTests, matrixScalarMultiplication_willProduceCorrectResult) {
  linear_alg::M<3, 4> m{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
  linear_alg::M<3, 4> expected{10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120};
  ASSERT_EQ(m * 10.f, expected);
  ASSERT_EQ(10.f * m, expected);
}

TEST(LinearAlgMatrixTests, matrixAddition_willProduceCorrectResult) {
  linear_alg::M<3, 4> m{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
  linear_alg::M<3, 4> expected{2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24};
  ASSERT_EQ(m + m, expected);
}

TEST(LinearAlgMatrixTests, matrixScalarAddition_willProduceCorrectResult) {
  linear_alg::M<3, 4> m{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
  linear_alg::M<3, 4> expected{3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
  ASSERT_EQ(m + 2.f, expected);
  ASSERT_EQ(2.f + m, expected);
}

TEST(LinearAlgMatrixTests, nagateMatrix_willProduceCorrectResult) {
  linear_alg::M<3, 4> m{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
  linear_alg::M<3, 4> expected{-1, -2, -3, -4, -5, -6, -7, -8, -9, -10, -11, -12};
  ASSERT_EQ(-m, expected);
}

TEST(LinearAlgMatrixTests, matrixSubtraction_willProduceCorrectResult) {
  linear_alg::M<3, 4> m{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
  linear_alg::M<3, 4> expected{};
  ASSERT_EQ(m - m, expected);
}

TEST(LinearAlgMatrixTests, matrixScalarSubtraction_willProduceCorrectResult) {
  linear_alg::M<3, 4> m{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
  linear_alg::M<3, 4> expected{-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  ASSERT_EQ(m - 2.f, expected);
}

TEST(LinearAlgMatrixTests, scalarMatrixSubtraction_willProduceCorrectResult) {
  linear_alg::M<3, 4> m{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
  linear_alg::M<3, 4> expected{0, -1, -2, -3, -4, -5, -6, -7, -8, -9, -10, -11};
  ASSERT_EQ(1.f - m, expected);
}
