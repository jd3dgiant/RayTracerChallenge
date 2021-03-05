#pragma once
#include <vector>
#include "Tuples.h"

template <typename matrixValueT>
class Matrix {
 public:
  Matrix(size_t rows, size_t cols) : mRows(rows), mCols(cols), mData(rows * cols) {}

  Matrix(size_t rows, size_t cols, std::vector<Tuple>& matrixElements)
      : mRows(rows), mCols(cols), mData(rows * cols) {
    for (unsigned i = 0; i < rows; ++i) {
      for (unsigned j = 0; j < cols; ++j) {
        mData[i * cols + j] = matrixElements[i].components[j];
      }
    }
  }

  Matrix(size_t rows, size_t cols, std::vector<matrixValueT> matrixElements)
      : mRows(rows), mCols(cols), mData(rows * cols) {
    int mECount = matrixElements.size();
    for (unsigned i = 0; i < rows; ++i) {
      for (unsigned j = 0; j < cols; ++j) {
        int index = i * cols + j;
        if (index < mECount) {
          mData[index] = matrixElements[index];
        } else {
          break;
        }
      }
    }
  }

  static Matrix identity(int matrixSquareSize);

  matrixValueT& operator()(size_t i, size_t j);
  matrixValueT operator()(size_t i, size_t j) const;

  bool operator==(const Matrix& rhs) const;

  bool operator!=(const Matrix& rhs) const {
    return !operator==(rhs);
  }

  Matrix operator*(const Matrix& rhs) const;

  Tuple operator*(const Tuple& rhs) const;

  // TODO: this is duplicate of TUPLE make into global function
  bool IsEqual(float lhs, float rhs) const {
    return std::abs(lhs - rhs) < EPSILON;
  }

  Matrix transpose() const;

  matrixValueT determinant() const;

  Matrix submatrix(int rowRemove, int colRemove) const;

  matrixValueT minor(int row, int col) const;

  matrixValueT cofactor(int row, int col) const;

  bool invertible() const {
    return determinant() != 0;
  }

  Matrix<matrixValueT> inverse() const;

 protected:
  float const EPSILON = 0.0001;

 private:
  size_t mRows;
  size_t mCols;
  std::vector<matrixValueT> mData;
};
