#ifndef __S21MATRIX_H__
#define __S21MATRIX_H__

#include <iostream>

class S21Matrix {
 private:
  int rows_, cols_;
  double** matrix_;

 public:
  int get_rows() { return this->rows_; }
  int get_cols() { return this->cols_; }
  void set_rows(int rows);
  void set_cols(int cols);

  S21Matrix() {
    this->rows_ = 0;
    this->cols_ = 0;
    this->matrix_ = nullptr;
  }
  S21Matrix(int rows, int cols);

  S21Matrix(const S21Matrix& other) : S21Matrix(other.rows_, other.cols_) {
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->cols_; j++) {
        this->matrix_[i][j] = other.matrix_[i][j];
      }
    }
  }

  S21Matrix(S21Matrix&& other) {
    this->rows_ = other.rows_;
    this->cols_ = other.cols_;
    this->matrix_ = other.matrix_;
    other.rows_ = 0;
    other.cols_ = 0;
    other.matrix_ = nullptr;
  }
  ~S21Matrix() {
    if (this->matrix_) {
      for (int i = 0; i < this->rows_; i++) {
        delete[] this->matrix_[i];
      }
      delete[] this->matrix_;
    }
  }

  // some operators overloads
  S21Matrix operator+(const S21Matrix& other) {
    S21Matrix result(*this);
    result.SumMatrix(other);
    return result;
  }
  S21Matrix operator-(const S21Matrix& other) {
    S21Matrix result(*this);
    result.SubMatrix(other);
    return result;
  }
  S21Matrix operator*(const S21Matrix& other) {
    S21Matrix result(*this);
    result.MulMatrix(other);
    return result;
  }
  S21Matrix operator*(const double num) {
    S21Matrix result(*this);
    result.MulNumber(num);
    return result;
  }
  bool operator==(const S21Matrix& other) const {
    return this->EqMatrix(other);
  }

  S21Matrix& operator=(const S21Matrix& other);

  S21Matrix& operator+=(const S21Matrix& other) {
    this->SumMatrix(other);
    return *this;
  }
  S21Matrix& operator-=(const S21Matrix& other) {
    this->SubMatrix(other);
    return *this;
  }
  S21Matrix& operator*=(const S21Matrix& other) {
    this->MulMatrix(other);
    return *this;
  }
  double& operator()(int i, int j) {
    if (i < 0 || i >= this->rows_ || j < 0 || j >= this->cols_)
      throw std::invalid_argument("выход за пределы матрицы");

    return this->matrix_[i][j];
  }

  bool EqMatrix(const S21Matrix& other) const;

  void SumMatrix(const S21Matrix& other);

  void SubMatrix(const S21Matrix& other);

  void MulNumber(const double num) {
    for (int i = 0; i < this->rows_; i++)
      for (int j = 0; j < this->cols_; j++) this->matrix_[i][j] *= num;
  }

  void MulMatrix(const S21Matrix& other);

  S21Matrix Transpose();

  S21Matrix CalcComplements();
  void s21_Minoring(S21Matrix from, int local_rows, int local_columns);
  double Determinant();

  S21Matrix InverseMatrix();
};

// Test helper
void full_Matrix(S21Matrix& m);
#endif
