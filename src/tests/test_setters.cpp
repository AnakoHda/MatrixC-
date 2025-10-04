#include <gtest/gtest.h>

#include "../s21_matrix_oop.h"
TEST(setters, big) {
  S21Matrix m(2, 2);
  m.set_cols(4);
  m.set_rows(4);
  EXPECT_EQ(m(3, 0), 0);
  EXPECT_EQ(m(0, 3), 0);
  EXPECT_EQ(m(3, 3), 0);
}
TEST(setters, small) {
  S21Matrix m(4, 4);
  m(1, 1) = 5.0;
  m.set_cols(2);
  EXPECT_EQ(m.get_cols(), 2);
  EXPECT_EQ(m.get_rows(), 4);
  EXPECT_EQ(m(1, 1), 5.0);
  EXPECT_THROW(m(3, 3), std::invalid_argument);
  m.set_rows(2);
  EXPECT_EQ(m.get_cols(), 2);
  EXPECT_EQ(m.get_rows(), 2);
  EXPECT_EQ(m(1, 1), 5.0);
  EXPECT_THROW(m(3, 1), std::invalid_argument);
}
TEST(setters, uncorrect_param) {
  S21Matrix m(2, 2);
  EXPECT_THROW(m.set_rows(-1), std::invalid_argument);
  EXPECT_THROW(m.set_cols(-1), std::invalid_argument);
}