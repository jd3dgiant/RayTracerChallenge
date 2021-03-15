#include "Matrix.h"
#include "pch.h"

using namespace jdRay;

// Matrix3x3
template <typename valueT>
Matrix2x2<valueT> Matrix3x3<valueT>::submatrix(int rowRemove, int colRemove) const {
  std::array<valueT, 4> subMData;

  unsigned indexCounter = 0;
  for (unsigned i = 0; i < ROWSIZE; ++i) {
    if (i == rowRemove) {
      continue;
    }
    for (unsigned j = 0; j < ROWSIZE; ++j) {
      if (j == colRemove) {
        continue;
      }
      subMData[indexCounter] = (*this)(i, j);
      indexCounter++;
    }
  }

  return Matrix2x2<valueT>(subMData);
}
// end Matrix3x3

// Matrix4x4
template <typename valueT>
Matrix3x3<valueT> Matrix4x4<valueT>::submatrix(int rowRemove, int colRemove) const {
  std::array<valueT, 9> subMData;

  unsigned indexCounter = 0;
  for (unsigned i = 0; i < ROWSIZE; ++i) {
    if (i == rowRemove) {
      continue;
    }
    for (unsigned j = 0; j < ROWSIZE; ++j) {
      if (j == colRemove) {
        continue;
      }
      subMData[indexCounter] = (*this)(i, j);
      indexCounter++;
    }
  }
  return Matrix3x3<valueT>(subMData);
}

template <typename valueT>
Matrix4x4<valueT> Matrix4x4<valueT>::inverse() {
  return Matrix4x4<valueT>(inverseCache);
}

template <typename valueT>
Matrix4x4<valueT> Matrix4x4<valueT>::inverseSlow() const {
  assert(invertible());

  Matrix4x4<valueT> invertM;
  for (unsigned i = 0; i < ROWSIZE; ++i) {
    for (unsigned j = 0; j < ROWSIZE; ++j) {
      valueT cFactor = cofactor(i, j);
      // note that "col, row" here, instead of "row, col",
      // accomplishes the transpose operation!
      invertM(j, i) = cFactor / determinant();
    }
  }
  return invertM;
}

// end Matrix4x4

template <typename matrixValueT>
MatrixXxX<matrixValueT> MatrixXxX<matrixValueT>::identity(int matrixSquareSize) {
  // this will only work properly with matrices that are square in size
  MatrixXxX<matrixValueT> identityMatrix(matrixSquareSize, matrixSquareSize);

  for (unsigned i = 0; i < matrixSquareSize; ++i) {
    for (unsigned j = 0; j < matrixSquareSize; ++j) {
      if (i == j) {
        identityMatrix(i, j) = 1;
      } else {
        identityMatrix(i, j) = 0;
      }
    }
  }
  return identityMatrix; // TODO does this copy or return by reference
}

template <typename matrixValueT>
bool MatrixXxX<matrixValueT>::operator==(const MatrixXxX& rhs) const {
  if (mRows != rhs.mRows || mCols != rhs.mCols) {
    return false;
  }

  for (unsigned i = 0; i < mRows; ++i) {
    for (unsigned j = 0; j < mCols; ++j) {
      bool bEqual = utils::IsEqual(mData[i * mCols + j], rhs.mData[i * mCols + j]);
      if (!bEqual) {
        return false;
      }
    }
  }

  return true;
}
// TODO should add in check that matrix are same size
template <typename matrixValueT>
MatrixXxX<matrixValueT> MatrixXxX<matrixValueT>::operator*(const MatrixXxX& rhs) const {
  MatrixXxX<matrixValueT> multMatrix(mRows, mCols);
  for (unsigned i = 0; i < mRows; ++i) {
    for (unsigned j = 0; j < mCols; ++j) {
      multMatrix(i, j) = (*this)(i, 0) * rhs(0, j) + (*this)(i, 1) * rhs(1, j) +
          (*this)(i, 2) * rhs(2, j) + (*this)(i, 3) * rhs(3, j);
    }
  }
  return multMatrix;
}

template <typename matrixValueT>
Tuple MatrixXxX<matrixValueT>::operator*(const Tuple& rhs) const {
  Tuple newTuple;
  for (unsigned i = 0; i < mRows; ++i) {
    newTuple.components[i] = (*this)(i, 0) * rhs.components[0] + (*this)(i, 1) * rhs.components[1] +
        (*this)(i, 2) * rhs.components[2] + (*this)(i, 3) * rhs.components[3];
  }
  return newTuple;
}

template <typename matrixValueT>
MatrixXxX<matrixValueT> MatrixXxX<matrixValueT>::transpose() const {
  MatrixXxX<matrixValueT> tMatrix(mCols, mRows);

  for (unsigned i = 0; i < mRows; ++i) {
    for (unsigned j = 0; j < mCols; ++j) {
      tMatrix(j, i) = (*this)(i, j);
    }
  }
  return tMatrix;
}

template <typename matrixValueT>
matrixValueT MatrixXxX<matrixValueT>::determinant() const {
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
MatrixXxX<matrixValueT> MatrixXxX<matrixValueT>::submatrix(int rowRemove, int colRemove) const {
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

  return MatrixXxX<matrixValueT>(mRows - 1, mCols - 1, subMData);
}

template <typename matrixValueT>
matrixValueT MatrixXxX<matrixValueT>::minor(int row, int col) const {
  return submatrix(row, col).determinant();
}

template <typename matrixValueT>
matrixValueT MatrixXxX<matrixValueT>::cofactor(int row, int col) const {
  matrixValueT determinant = minor(row, col);

  return (row + col) % 2 == 0 ? determinant : -determinant;
}

template <typename matrixValueT>
MatrixXxX<matrixValueT> MatrixXxX<matrixValueT>::inverse() const {
  assert(invertible());

  MatrixXxX<matrixValueT> invertM(mRows, mCols);
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

template <typename matrixValueT>
template <typename valueT>
inline MatrixXxX<matrixValueT>
MatrixXxX<matrixValueT>::translationMatrix(valueT x, valueT y, valueT z) {
  MatrixXxX<matrixValueT> identity = identity();

  return MatrixXxX<matrixValueT>();
}
