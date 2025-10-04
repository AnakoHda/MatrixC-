#include <gtest/gtest.h>

#include "../s21_matrix_oop.h"
TEST(operators, equal) {
  S21Matrix m(2, 2);
  S21Matrix n(2, 2);
  full_Matrix(m);
  full_Matrix(n);
  EXPECT_TRUE(m == n);
  EXPECT_EQ(m(0, 0), n(0, 0));
  EXPECT_EQ(m(0, 1), n(0, 1));
  EXPECT_EQ(m(1, 0), n(1, 0));
  EXPECT_EQ(m(1, 1), n(1, 1));
}
TEST(operators, EqMatrix) {
  S21Matrix m(2, 2);
  S21Matrix n(2, 2);
  full_Matrix(m);
  full_Matrix(n);
  EXPECT_TRUE(m.EqMatrix(n));
  EXPECT_TRUE(n.EqMatrix(m));
  EXPECT_EQ(m(0, 0), n(0, 0));
  EXPECT_EQ(m(0, 1), n(0, 1));
  EXPECT_EQ(m(1, 0), n(1, 0));
  EXPECT_EQ(m(1, 1), n(1, 1));
}
TEST(operators, equal_one) {
  S21Matrix m(2, 2);
  S21Matrix n(2, 2);
  full_Matrix(m);
  n = m;
  EXPECT_TRUE(m == n);
  EXPECT_DOUBLE_EQ(m(0, 0), n(0, 0));
  EXPECT_DOUBLE_EQ(m(0, 1), n(0, 1));
  EXPECT_DOUBLE_EQ(m(1, 0), n(1, 0));
  EXPECT_DOUBLE_EQ(m(1, 1), n(1, 1));
}
TEST(operators, SumMatrix) {
  S21Matrix m(2, 2);
  S21Matrix n(2, 2);
  full_Matrix(m);
  full_Matrix(n);
  m.SumMatrix(n);
  EXPECT_EQ(m.get_rows(), 2);
  EXPECT_EQ(m.get_cols(), 2);
  EXPECT_EQ(2 * n(0, 0), m(0, 0));
  EXPECT_EQ(2 * n(0, 1), m(0, 1));
  EXPECT_EQ(2 * n(1, 0), m(1, 0));
  EXPECT_EQ(2 * n(1, 1), m(1, 1));
}
TEST(operators, SumMatrix_error) {
  S21Matrix m(2, 2);
  S21Matrix n(2, 3);
  EXPECT_THROW(m.SumMatrix(n), std::invalid_argument);
}
TEST(operators, plus) {
  S21Matrix m(2, 2);
  S21Matrix n(2, 2);
  full_Matrix(m);
  full_Matrix(n);
  S21Matrix r = m + n;
  EXPECT_EQ(r.get_rows(), 2);
  EXPECT_EQ(r.get_cols(), 2);
  EXPECT_EQ(2 * n(0, 0), r(0, 0));
  EXPECT_EQ(2 * n(0, 1), r(0, 1));
  EXPECT_EQ(2 * n(1, 0), r(1, 0));
  EXPECT_EQ(2 * n(1, 1), r(1, 1));
}
TEST(operators, plus_error) {
  S21Matrix m(2, 2);
  S21Matrix n(2, 3);
  EXPECT_THROW(m + n, std::invalid_argument);
}
TEST(operators, SubMatrix) {
  S21Matrix m(2, 2);
  S21Matrix n(2, 2);
  full_Matrix(m);
  full_Matrix(n);
  m.SubMatrix(n);
  EXPECT_EQ(m.get_rows(), 2);
  EXPECT_EQ(m.get_cols(), 2);
  EXPECT_EQ(m(0, 0), n(0, 0) - n(0, 0));
  EXPECT_EQ(m(0, 1), n(0, 1) - n(0, 1));
  EXPECT_EQ(m(1, 0), n(1, 0) - n(1, 0));
  EXPECT_EQ(m(1, 1), n(1, 1) - n(1, 1));
}
TEST(operators, SubMatrix_error) {
  S21Matrix m(2, 2);
  S21Matrix n(2, 3);
  EXPECT_THROW(m.SubMatrix(n), std::invalid_argument);
}
TEST(operators, minus) {
  S21Matrix m(2, 2);
  S21Matrix n(2, 2);
  full_Matrix(m);
  full_Matrix(n);
  S21Matrix r = m - n;
  EXPECT_EQ(r.get_rows(), 2);
  EXPECT_EQ(r.get_cols(), 2);
  EXPECT_EQ(r(0, 0), n(0, 0) - n(0, 0));
  EXPECT_EQ(r(0, 1), n(0, 1) - n(0, 1));
  EXPECT_EQ(r(1, 0), n(1, 0) - n(1, 0));
  EXPECT_EQ(r(1, 1), n(1, 1) - n(1, 1));
}
TEST(operators, minus_error) {
  S21Matrix m(2, 2);
  S21Matrix n(2, 3);
  EXPECT_THROW(m - n, std::invalid_argument);
}

TEST(operators, MulNumber) {
  S21Matrix m(2, 2);
  S21Matrix n(2, 2);
  full_Matrix(m);
  full_Matrix(n);
  m.MulNumber(2.0);
  EXPECT_EQ(m.get_rows(), 2);
  EXPECT_EQ(m.get_cols(), 2);
  EXPECT_EQ(m(0, 0), n(0, 0) * 2.0);
  EXPECT_EQ(m(0, 1), n(0, 1) * 2.0);
  EXPECT_EQ(m(1, 0), n(1, 0) * 2.0);
  EXPECT_EQ(m(1, 1), n(1, 1) * 2.0);
}
TEST(operators, MulMatrix) {
  S21Matrix m(1, 2);
  S21Matrix n(2, 3);
  S21Matrix r(1, 3);
  full_Matrix(m);
  full_Matrix(n);
  r(0, 0) = 5.0;
  r(0, 1) = 8.0;
  r(0, 2) = 11.0;
  m.MulMatrix(n);
  EXPECT_EQ(m.get_rows(), 1);
  EXPECT_EQ(m.get_cols(), 3);
  EXPECT_EQ(m(0, 0), r(0, 0));
  EXPECT_EQ(m(0, 1), r(0, 1));
  EXPECT_EQ(m(0, 2), r(0, 2));
}
TEST(operators, MulMatrix_error) {
  S21Matrix m(2, 2);
  S21Matrix n(3, 2);
  EXPECT_THROW(m.MulMatrix(n), std::invalid_argument);
}
TEST(operators, multiplication) {
  S21Matrix m(1, 2);
  S21Matrix n(2, 3);
  S21Matrix r(1, 3);
  full_Matrix(m);
  full_Matrix(n);
  r(0, 0) = 5.0;
  r(0, 1) = 8.0;
  r(0, 2) = 11.0;
  m = m * n;
  EXPECT_EQ(m.get_rows(), 1);
  EXPECT_EQ(m.get_cols(), 3);
  EXPECT_EQ(m(0, 0), r(0, 0));
  EXPECT_EQ(m(0, 1), r(0, 1));
  EXPECT_EQ(m(0, 2), r(0, 2));
}
TEST(operators, multiplication_error) {
  S21Matrix m(2, 2);
  S21Matrix n(3, 2);
  EXPECT_THROW(m * n, std::invalid_argument);
}