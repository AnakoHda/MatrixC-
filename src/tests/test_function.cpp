#include <gtest/gtest.h>

#include "../s21_matrix_oop.h"
TEST(functions, Transpose) {
  S21Matrix m(2, 3);
  S21Matrix n(3, 2);
  full_Matrix(m);
  full_Matrix(n);
  m = m.Transpose();
  EXPECT_DOUBLE_EQ(m(0, 0), n(0, 0));
  EXPECT_DOUBLE_EQ(m(0, 1), n(0, 1));
  EXPECT_DOUBLE_EQ(m(1, 0), n(1, 0));
  EXPECT_DOUBLE_EQ(m(1, 1), n(1, 1));
  EXPECT_DOUBLE_EQ(m(2, 0), n(2, 0));
  EXPECT_DOUBLE_EQ(m(2, 1), n(2, 1));
}
TEST(functions, CalcComplements) {
  S21Matrix m(3, 3);
  S21Matrix n(3, 3);
  full_Matrix(m);
  m(2, 2) = 7.0;
  m = m.CalcComplements();
  n(0, 0) = 5.0;
  n(0, 1) = -2.0;
  n(0, 2) = -1.0;
  n(1, 0) = -2.0;
  n(1, 1) = -2.0;
  n(2, 0) = -1.0;
  n(1, 2) = 2.0;
  n(2, 1) = 2.0;
  n(2, 2) = -1.0;
  EXPECT_DOUBLE_EQ(m(0, 0), n(0, 0));
  EXPECT_DOUBLE_EQ(m(0, 1), n(0, 1));
  EXPECT_DOUBLE_EQ(m(1, 0), n(1, 0));
  EXPECT_DOUBLE_EQ(m(1, 1), n(1, 1));
  EXPECT_DOUBLE_EQ(m(2, 0), n(2, 0));
  EXPECT_DOUBLE_EQ(m(2, 1), n(2, 1));
}
TEST(operators, CalcComplements_error) {
  S21Matrix m(2, 3);
  EXPECT_THROW(m.CalcComplements(), std::invalid_argument);
}
TEST(functions, Determinant) {
  S21Matrix m(3, 3);
  full_Matrix(m);
  EXPECT_EQ(m.Determinant(), 0);
}
TEST(functions, InverseMatrix) {
  S21Matrix m(3, 3);
  S21Matrix n(3, 3);
  full_Matrix(m);
  m(2, 2) = 7.0;
  m = m.InverseMatrix();
  full_Matrix(n);
  n(0, 0) = -2.5;
  n(0, 1) = 1.0;
  n(0, 2) = 0.5;
  n(1, 0) = 1.0;
  n(1, 1) = 1.0;
  n(1, 2) = -1.0;
  n(2, 0) = 0.5;
  n(2, 1) = -1.0;
  n(2, 2) = 0.5;
  EXPECT_DOUBLE_EQ(m(0, 0), n(0, 0));
  EXPECT_DOUBLE_EQ(m(0, 1), n(0, 1));
  EXPECT_DOUBLE_EQ(m(1, 0), n(1, 0));
  EXPECT_DOUBLE_EQ(m(1, 1), n(1, 1));
  EXPECT_DOUBLE_EQ(m(2, 0), n(2, 0));
  EXPECT_DOUBLE_EQ(m(2, 1), n(2, 1));
}
TEST(operators, InverseMatrix_error) {
  S21Matrix m(3, 2);
  full_Matrix(m);
  EXPECT_THROW(m.InverseMatrix(), std::invalid_argument);
}
TEST(operators, InverseMatrix_error_zero) {
  S21Matrix m(3, 3);
  full_Matrix(m);
  EXPECT_THROW(m.InverseMatrix(), std::invalid_argument);
}