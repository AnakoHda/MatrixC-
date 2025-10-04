#include "s21_matrix_oop.h"

void S21Matrix::set_rows(int rows) {
  if (rows <= 0) throw std::invalid_argument("число меньше 0");
  if (rows == this->rows_) return;

  S21Matrix tmp = S21Matrix(rows, this->cols_);
  int min_rows = (rows < this->rows_) ? rows : this->rows_;
  for (int i = 0; i < min_rows; i++)
    for (int j = 0; j < this->cols_; j++)
      tmp.matrix_[i][j] = this->matrix_[i][j];

  *this = tmp;
}

void S21Matrix::set_cols(int cols) {
  if (cols <= 0) throw std::invalid_argument("число меньше 0");
  if (cols == this->cols_) return;

  S21Matrix tmp = S21Matrix(this->rows_, cols);
  int min_cols = (cols < this->cols_) ? cols : this->cols_;
  for (int i = 0; i < this->rows_; i++)
    for (int j = 0; j < min_cols; j++) tmp.matrix_[i][j] = this->matrix_[i][j];

  *this = tmp;
}

S21Matrix::S21Matrix(int rows, int cols) {
  if (rows <= 0 || cols <= 0) throw std::invalid_argument("числа меньше 0");
  this->rows_ = rows;
  this->cols_ = cols;
  try {
    this->matrix_ = new double*[rows_]();
    for (int i = 0; i < rows_; i++) {
      this->matrix_[i] = new double[cols_]();
    }
  } catch (const std::exception& e) {
    if (this->matrix_) {
      for (int i = 0; i < this->rows_; i++) {
        delete[] this->matrix_[i];
      }
      delete[] this->matrix_;
    }

    std::cerr << "Allocation failed: " << e.what() << std::endl;
    throw;
  }
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  S21Matrix tmp = S21Matrix(other.rows_, other.cols_);
  this->~S21Matrix();
  this->rows_ = tmp.rows_;
  this->cols_ = tmp.cols_;
  this->matrix_ = tmp.matrix_;
  tmp.matrix_ = nullptr;

  for (int i = 0; i < this->rows_; i++)
    for (int j = 0; j < this->cols_; j++)
      this->matrix_[i][j] = other.matrix_[i][j];
  return *this;
}

bool S21Matrix::EqMatrix(const S21Matrix& other) const {
  if (other.rows_ != this->rows_ || other.cols_ != this->cols_) return false;

  const double EPSILON = 1e-7;
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      if (fabs(this->matrix_[i][j] - other.matrix_[i][j]) > EPSILON)
        return false;
    }
  }
  return true;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (other.rows_ != this->rows_ || other.cols_ != this->cols_)
    throw std::invalid_argument("Различная размерность матриц");

  for (int i = 0; i < this->rows_; i++)
    for (int j = 0; j < this->cols_; j++)
      this->matrix_[i][j] += other.matrix_[i][j];
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (other.rows_ != this->rows_ || other.cols_ != this->cols_)
    throw std::invalid_argument("Различная размерность матриц");

  for (int i = 0; i < this->rows_; i++)
    for (int j = 0; j < this->cols_; j++)
      this->matrix_[i][j] -= other.matrix_[i][j];
}
void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (this->cols_ != other.rows_)
    throw std::invalid_argument(
        "число столбцов первой матрицы не равно числу строк второй матрицы");

  S21Matrix tmp = S21Matrix(this->rows_, other.cols_);

  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      tmp.matrix_[i][j] = 0;
      for (int k = 0; k < this->cols_; k++)
        tmp.matrix_[i][j] += this->matrix_[i][k] * other.matrix_[k][j];
    }
  }
  *this = tmp;
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix tmp = S21Matrix(this->cols_, this->rows_);
  for (int i = 0; i < this->rows_; i++)
    for (int j = 0; j < this->cols_; j++)
      tmp.matrix_[j][i] = this->matrix_[i][j];
  return tmp;
}

S21Matrix S21Matrix::CalcComplements() {
  if (this->cols_ != this->rows_)
    throw std::invalid_argument("матрица не является квадратной");
  S21Matrix result(this->rows_, this->cols_);
  if (this->cols_ == 1) {
    result(0, 0) = 1;
    return result;
  }

  S21Matrix little_matrix(this->rows_ - 1, this->cols_ - 1);
  double cofactor = 0;
  for (int i = 0; i < this->rows_; i++)
    for (int j = 0; j < this->cols_; j++) {
      little_matrix.s21_Minoring(*this, i, j);
      cofactor = little_matrix.Determinant();
      result(i, j) = cofactor * pow(-1, (i + j));
    }
  return result;
}
void S21Matrix::s21_Minoring(S21Matrix from, int local_rows,
                             int local_columns) {
  for (int i = 0, m = 0; i < from.rows_; i++) {
    for (int j = 0, n = 0; j < from.cols_; j++) {
      if (i != local_rows && j != local_columns) {
        this->matrix_[m][n] = from(i, j);
        n++;
      }
    }
    if (i != local_rows) m++;
  }
}
double S21Matrix::Determinant() {
  if (this->cols_ != this->rows_)
    throw std::invalid_argument("матрица не является квадратной");
  double result;
  S21Matrix sub_matr(*this);

  int swaps = 0;
  for (int j = 0; j < this->cols_; j++) {
    if (sub_matr(j, j) == 0) {
      int tmp_index = -1;
      for (int l = j; l < this->rows_ && tmp_index == -1; l++)
        if (sub_matr(l, j) != 0) tmp_index = l;

      if (tmp_index >= 0) {
        double* temp = sub_matr.matrix_[j];
        sub_matr.matrix_[j] = sub_matr.matrix_[tmp_index];
        sub_matr.matrix_[tmp_index] = temp;
        swaps++;
      } else
        result = 0.0;
    }
    for (int k = j + 1; k < this->rows_; k++) {
      double temp = (sub_matr(k, j) / sub_matr(j, j));
      for (int i = j; i < this->cols_; i++) {
        sub_matr(k, i) = sub_matr(k, i) - temp * sub_matr(j, i);
      }
    }
  }
  result = sub_matr(0, 0);
  for (int i = 1; i < this->cols_; i++) result *= sub_matr(i, i);
  if (swaps % 2 == 1) result = -result;

  return result;
}

S21Matrix S21Matrix::InverseMatrix() {
  double determinant = this->Determinant();

  if (determinant == 0.0) {
    throw std::invalid_argument("determinant = 0");
  }
  S21Matrix result = this->CalcComplements();
  result = result.Transpose();

  for (int i = 0; i < result.rows_; i++)
    for (int j = 0; j < result.cols_; j++) result.matrix_[i][j] /= determinant;

  return result;
}
void full_Matrix(S21Matrix& m) {
  for (int i = 0; i < m.get_rows(); i++)
    for (int j = 0; j < m.get_cols(); j++) m(i, j) = i + j + 1.0;
}