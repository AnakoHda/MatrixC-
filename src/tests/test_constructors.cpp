#include <gtest/gtest.h>

#include "../s21_matrix_oop.h"

TEST(constructors, base) {
  S21Matrix m;
  EXPECT_EQ(m.get_rows(), 0);
  EXPECT_EQ(m.get_cols(), 0);
}

TEST(constructors, param) {
  S21Matrix m(2, 3);
  EXPECT_EQ(m.get_rows(), 2);
  EXPECT_EQ(m.get_cols(), 3);
}
TEST(constructors, uncorrect_param) {
  EXPECT_THROW(S21Matrix m(0, 0), std::invalid_argument);
}
TEST(constructors, exection) {
  S21Matrix m(4, 2);
  EXPECT_EQ(m.get_rows(), 4);
  EXPECT_EQ(m.get_cols(), 2);
  m(0, 0) = 1.0;
  m(0, 1) = 2.0;
  S21Matrix n(m);
  EXPECT_EQ(n.get_rows(), m.get_rows());
  EXPECT_EQ(n.get_cols(), m.get_cols());
  EXPECT_EQ(n(0, 0), m(0, 0));
  EXPECT_EQ(n(0, 1), m(0, 1));
}
TEST(constructors, exection_move) {
  S21Matrix m(4, 2);
  EXPECT_EQ(m.get_rows(), 4);
  EXPECT_EQ(m.get_cols(), 2);
  m(0, 0) = 1.0;
  m(0, 1) = 2.0;
  S21Matrix n(S21Matrix(4, 2));
  EXPECT_EQ(n.get_rows(), m.get_rows());
  EXPECT_EQ(n.get_cols(), m.get_cols());
}
