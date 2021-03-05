#include "Matrix.h"
#include "pch.h"

template <typename matrixValueT>
Matrix<matrixValueT> Matrix<matrixValueT>::identity(int matrixSquareSize) {
  // this will only work properly with matrices that are square in size
  Matrix<matrixValueT> identityMatrix(matrixSquareSize, matrixSquareSize);

  for (unsigned i = 0; i < matrixSquareSize; ++i) {
    for (unsigned j = 0; j < matrixSquareSize; ++j) {
      if (i == j) {
        identityMatrix(i, j) = 1;
      } else {
        identityMatrix(i, j) = 0;
      }
    }
  }
  return identityMatrix; // TODO can this be a reference
}

template <typename matrixValueT>
matrixValueT& Matrix<matrixValueT>::operator()(size_t i, size_t j) {
  return mData[i * mCols + j];
}

template <typename matrixValueT>
matrixValueT Matrix<matrixValueT>::operator()(size_t i, size_t j) const {
  return mData[i * mCols + j];
}

template <typename matrixValueT>
bool Matrix<matrixValueT>::operator==(const Matrix& rhs) const {
  if (mRows != rhs.mRows || mCols != rhs.mCols) {
    return false;
  }

  for (unsigned i = 0; i < mRows; ++i) {
    for (unsigned j = 0; j < mCols; ++j) {
      bool bEqual = IsEqual(mData[i * mCols + j], rhs.mData[i * mCols + j]);
      if (!bEqual) {
        return false;
      }
    }
  }

  return true;
}
// TODO should add in check that matrix are same size
template <typename matrixValueT>
Matrix<matrixValueT> Matrix<matrixValueT>::operator*(const Matrix& rhs) const {
  Matrix<matrixValueT> multMatrix(mRows, mCols);
  for (unsigned i = 0; i < mRows; ++i) {
    for (unsigned j = 0; j < mCols; ++j) {
      multMatrix(i, j) = (*this)(i, 0) * rhs(0, j) + (*this)(i, 1) * rhs(1, j) +
          (*this)(i, 2) * rhs(2, j) + (*this)(i, 3) * rhs(3, j);
    }
  }
  return multMatrix;
}

template <typename matrixValueT>
Tuple Matrix<matrixValueT>::operator*(const Tuple& rhs) const {
  Tuple newTuple;
  for (unsigned i = 0; i < mRows; ++i) {
    newTuple.components[i] = (*this)(i, 0) * rhs.components[0] + (*this)(i, 1) * rhs.components[1] +
        (*this)(i, 2) * rhs.components[2] + (*this)(i, 3) * rhs.components[3];
  }
  return newTuple;
}

template <typename matrixValueT> // TODO can this return by reference
Matrix<matrixValueT> Matrix<matrixValueT>::transpose() const {
  Matrix<matrixValueT> tMatrix(mCols, mRows);

  for (unsigned i = 0; i < mRows; ++i) {
    for (unsigned j = 0; j < mCols; ++j) {
      tMatrix(j, i) = (*this)(i, j);
    }
  }
  return tMatrix;
}

template <typename matrixValueT> // TODO can this return by reference
matrixValueT Matrix<matrixValueT>::determinant() const {
  if (mRows == 2 && mCols == 2) {
    return (*this)(0, 0) * (*this)(1, 1) - (*this)(0, 1) * (*this)(1, 0);
  } else {
    matrixValueT det = 0;
    for (unsigned i = 0; i < mCols; i++) {
      det += (*this)(0, i) * cofactor(0, i);
    }
    return det;
  }
}

template <typename matrixValueT>
Matrix<matrixValueT> Matrix<matrixValueT>::submatrix(int rowRemove, int colRemove) const {
  std::vector<matrixValueT> subMData;

  for (unsigned i = 0; i < mRows; ++i) {
    if (i == rowRemove) {
      continue;
    }
    for (unsigned j = 0; j < mCols; ++j) {
      if (j == colRemove) {
        continue;
      }
      subMData.emplace_back(mData[i * mCols + j]);
    }
  }

  return Matrix<matrixValueT>(mRows - 1, mCols - 1, subMData);
}

template <typename matrixValueT>
matrixValueT Matrix<matrixValueT>::minor(int row, int col) const {
  return submatrix(row, col).determinant();
}

template <typename matrixValueT>
matrixValueT Matrix<matrixValueT>::cofactor(int row, int col) const {
  matrixValueT determinant = minor(row, col);

  return (row + col) % 2 == 0 ? determinant : -determinant;
}

template <typename matrixValueT>
Matrix<matrixValueT> Matrix<matrixValueT>::inverse() const {
  assert(invertible());

  Matrix<matrixValueT> invertM(mRows, mCols);
  for (unsigned i = 0; i < mRows; ++i) {
    for (unsigned j = 0; j < mCols; ++j) {
      auto cFactor = cofactor(i, j);
      // note that "col, row" here, instead of "row, col",
      // accomplishes the transpose operation!
      invertM(j, i) = cFactor / determinant();
    }
  }
  return invertM;
}
