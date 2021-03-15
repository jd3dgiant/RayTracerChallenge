#pragma once
#include <vector>
#include "Tuples.h"

namespace jdRay {

template <typename valueT>
class Matrix2x2 {
 public:
  Matrix2x2() {
    // making identity by default
    m2[0] = m2[3] = 1;
  }
  Matrix2x2(std::array<valueT, 4>& entries) : m2(entries) {}

  bool operator==(const Matrix2x2& rhs) const {
    return utils::IsEqual(m2[0], rhs.m2[0]) && utils::IsEqual(m2[1], rhs.m2[1]) &&
        utils::IsEqual(m2[2], rhs.m2[2]) && utils::IsEqual(m2[3], rhs.m2[3]);
  }

  bool operator!=(const Matrix2x2& rhs) const {
    return !operator==(rhs);
  }

  valueT& operator()(unsigned row, unsigned col) {
    return m2[row * ROWSIZE + col];
  }
  valueT operator()(unsigned row, unsigned col) const {
    return m2[row * ROWSIZE + col];
  }

  Matrix2x2 operator*(const Matrix2x2& rhs) const {
    std::array<valueT, 4> entries{
        m2[0] * rhs.m2[0] + m2[1] * rhs.m2[2],
        m2[0] * rhs.m2[1] + m2[1] * rhs.m2[3],
        m2[2] * rhs.m2[0] + m2[3] * rhs.m2[2],
        m2[2] * rhs.m2[1] + m2[3] * rhs.m2[3]};
    return Matrix2x2<valueT>(entries);
  }

  Matrix2x2 transpose() const {
    std::array<valueT, 4> entries{m2[0], m2[2], m2[1], m2[3]};
    return Matrix2x2<valueT>(entries);
  }

  float determinant() const {
    return m2[0] * m2[3] - m2[1] * m2[2];
  }

  bool invertible() const {
    return determinant() != 0;
  }

  std::array<valueT, 4> m2 = {};

 private:
  const int ROWSIZE = 2;
};

template <typename valueT>
class Matrix3x3 {
 public:
  Matrix3x3() {
    // making identity by default
    m3[0] = m3[4] = m3[8] = 1;
  }
  Matrix3x3(std::array<valueT, 9>& entries) : m3(entries) {}

  bool operator==(const Matrix3x3& rhs) const {
    return utils::IsEqual(m3[0], rhs.m3[0]) && utils::IsEqual(m3[1], rhs.m3[1]) &&
        utils::IsEqual(m3[2], rhs.m3[2]) && utils::IsEqual(m3[3], rhs.m3[3]) &&
        utils::IsEqual(m3[4], rhs.m3[4]) && utils::IsEqual(m3[5], rhs.m3[5]) &&
        utils::IsEqual(m3[6], rhs.m3[6]) && utils::IsEqual(m3[7], rhs.m3[7]) &&
        utils::IsEqual(m3[8], rhs.m3[8]);
  }

  bool operator!=(const Matrix3x3& rhs) const {
    return !operator==(rhs);
  }

  valueT& operator()(unsigned row, unsigned col) {
    return m3[row * ROWSIZE + col];
  }
  valueT operator()(unsigned row, unsigned col) const {
    return m3[row * ROWSIZE + col];
  }

  Matrix3x3 operator*(const Matrix3x3& rhs) const {
    std::array<valueT, 9> entries{
        m3[0] * rhs.m3[0] + m3[1] * rhs.m3[3] + m3[2] * rhs.m3[6],
        m3[0] * rhs.m3[1] + m3[1] * rhs.m3[4] + m3[2] * rhs.m3[7],
        m3[0] * rhs.m3[2] + m3[1] * rhs.m3[5] + m3[2] * rhs.m3[8],
        m3[3] * rhs.m3[0] + m3[4] * rhs.m3[3] + m3[5] * rhs.m3[6],
        m3[3] * rhs.m3[1] + m3[4] * rhs.m3[4] + m3[5] * rhs.m3[7],
        m3[3] * rhs.m3[2] + m3[4] * rhs.m3[5] + m3[5] * rhs.m3[8],
        m3[6] * rhs.m3[0] + m3[7] * rhs.m3[3] + m3[8] * rhs.m3[6],
        m3[6] * rhs.m3[1] + m3[7] * rhs.m3[4] + m3[8] * rhs.m3[7],
        m3[6] * rhs.m3[2] + m3[7] * rhs.m3[5] + m3[8] * rhs.m3[8]};
    return Matrix3x3<valueT>(entries);
  }

  Matrix3x3 transpose() const {
    std::array<valueT, 9> entries{m3[0], m3[3], m3[6], m3[1], m3[4], m3[7], m3[2], m3[5], m3[8]};
    return Matrix3x3<valueT>(entries);
  }

  Matrix2x2<valueT> submatrix(int rowRemove, int colRemove) const;

  valueT minor(int row, int col) const {
    return submatrix(row, col).determinant();
  }

  valueT cofactor(int row, int col) const {
    valueT determinant = minor(row, col);

    return (row + col) % 2 == 0 ? determinant : -determinant;
  }

  valueT determinant() const {
    return m3[0] * cofactor(0, 0) + m3[1] * cofactor(0, 1) + m3[2] * cofactor(0, 2);
  }

  bool invertible() const {
    return determinant() != 0;
  }

  std::array<valueT, 9> m3 = {};

 private:
  const int ROWSIZE = 3;
};

template <typename valueT>
class Matrix4x4 {
 public:
  Matrix4x4() {
    // making identity by default
    m4[0] = m4[5] = m4[10] = m4[15] = 1;
    updateInverseCache();
  }
  Matrix4x4(std::array<valueT, 16>& entries) : m4(entries) {
    updateInverseCache();
  }

  Matrix4x4(std::vector<Tuple>& matrixRows) {
    for (unsigned i = 0; i < ROWSIZE; ++i) {
      for (unsigned j = 0; j < ROWSIZE; ++j) {
        m4[i * ROWSIZE + j] = matrixRows[i].components[j];
      }
    }
    updateInverseCache();
  }

  bool operator==(const Matrix4x4& rhs) const {
    return utils::IsEqual(m4[0], rhs.m4[0]) && utils::IsEqual(m4[1], rhs.m4[1]) &&
        utils::IsEqual(m4[2], rhs.m4[2]) && utils::IsEqual(m4[3], rhs.m4[3]) &&
        utils::IsEqual(m4[4], rhs.m4[4]) && utils::IsEqual(m4[5], rhs.m4[5]) &&
        utils::IsEqual(m4[6], rhs.m4[6]) && utils::IsEqual(m4[7], rhs.m4[7]) &&
        utils::IsEqual(m4[8], rhs.m4[8]) && utils::IsEqual(m4[9], rhs.m4[9]) &&
        utils::IsEqual(m4[10], rhs.m4[10]) && utils::IsEqual(m4[11], rhs.m4[11]) &&
        utils::IsEqual(m4[12], rhs.m4[12]) && utils::IsEqual(m4[13], rhs.m4[13]) &&
        utils::IsEqual(m4[14], rhs.m4[14]) && utils::IsEqual(m4[15], rhs.m4[15]);
  }

  bool operator!=(const Matrix4x4& rhs) const {
    return !operator==(rhs);
  }

  valueT& operator()(unsigned i, unsigned j) {
    return m4[i * ROWSIZE + j];
  }
  valueT operator()(unsigned i, unsigned j) const {
    return m4[i * ROWSIZE + j];
  }

  Matrix4x4 operator*(const Matrix4x4& rhs) const {
    std::array<valueT, 16> entries{
        m4[0] * rhs.m4[0] + m4[1] * rhs.m4[4] + m4[2] * rhs.m4[8] + m4[3] * rhs.m4[12],
        m4[0] * rhs.m4[1] + m4[1] * rhs.m4[5] + m4[2] * rhs.m4[9] + m4[3] * rhs.m4[13],
        m4[0] * rhs.m4[2] + m4[1] * rhs.m4[6] + m4[2] * rhs.m4[10] + m4[3] * rhs.m4[14],
        m4[0] * rhs.m4[3] + m4[1] * rhs.m4[7] + m4[2] * rhs.m4[11] + m4[3] * rhs.m4[15],
        m4[4] * rhs.m4[0] + m4[5] * rhs.m4[4] + m4[6] * rhs.m4[8] + m4[7] * rhs.m4[12],
        m4[4] * rhs.m4[1] + m4[5] * rhs.m4[5] + m4[6] * rhs.m4[9] + m4[7] * rhs.m4[13],
        m4[4] * rhs.m4[2] + m4[5] * rhs.m4[6] + m4[6] * rhs.m4[10] + m4[7] * rhs.m4[14],
        m4[4] * rhs.m4[3] + m4[5] * rhs.m4[7] + m4[6] * rhs.m4[11] + m4[7] * rhs.m4[15],
        m4[8] * rhs.m4[0] + m4[9] * rhs.m4[4] + m4[10] * rhs.m4[8] + m4[11] * rhs.m4[12],
        m4[8] * rhs.m4[1] + m4[9] * rhs.m4[5] + m4[10] * rhs.m4[9] + m4[11] * rhs.m4[13],
        m4[8] * rhs.m4[2] + m4[9] * rhs.m4[6] + m4[10] * rhs.m4[10] + m4[11] * rhs.m4[14],
        m4[8] * rhs.m4[3] + m4[9] * rhs.m4[7] + m4[10] * rhs.m4[11] + m4[11] * rhs.m4[15],
        m4[12] * rhs.m4[0] + m4[13] * rhs.m4[4] + m4[14] * rhs.m4[8] + m4[15] * rhs.m4[12],
        m4[12] * rhs.m4[1] + m4[13] * rhs.m4[5] + m4[14] * rhs.m4[9] + m4[15] * rhs.m4[13],
        m4[12] * rhs.m4[2] + m4[13] * rhs.m4[6] + m4[14] * rhs.m4[10] + m4[15] * rhs.m4[14],
        m4[12] * rhs.m4[3] + m4[13] * rhs.m4[7] + m4[14] * rhs.m4[11] + m4[15] * rhs.m4[15]};
    return Matrix4x4<valueT>(entries);
  }

  Tuple operator*(const Tuple& rhs) const {
    return Tuple(
        m4[0] * rhs.components[0] + m4[1] * rhs.components[1] + m4[2] * rhs.components[2] +
            m4[3] * rhs.components[3],
        m4[4] * rhs.components[0] + m4[5] * rhs.components[1] + m4[6] * rhs.components[2] +
            m4[7] * rhs.components[3],
        m4[8] * rhs.components[0] + m4[9] * rhs.components[1] + m4[10] * rhs.components[2] +
            m4[11] * rhs.components[3],
        m4[12] * rhs.components[0] + m4[13] * rhs.components[1] + m4[14] * rhs.components[2] +
            m4[15] * rhs.components[3]);
  }

  Matrix4x4 transpose() const {
    std::array<valueT, 16> entries{
        m4[0],
        m4[4],
        m4[8],
        m4[12],
        m4[1],
        m4[5],
        m4[9],
        m4[13],
        m4[2],
        m4[6],
        m4[10],
        m4[14],
        m4[3],
        m4[7],
        m4[11],
        m4[15]};
    return Matrix4x4<valueT>(entries);
  }

  Matrix3x3<valueT> submatrix(int rowRemove, int colRemove) const;

  static Matrix4x4 identity() {
    return Matrix4x4();
  }

  valueT minor(int row, int col) const {
    return submatrix(row, col).determinant();
  }

  valueT cofactor(int row, int col) const {
    valueT determinant = minor(row, col);

    return (row + col) % 2 == 0 ? determinant : -determinant;
  }

  valueT determinant() const {
    return m4[0] * cofactor(0, 0) + m4[1] * cofactor(0, 1) + m4[2] * cofactor(0, 2) +
        m4[3] * cofactor(0, 3);
  }

  bool invertible() const {
    return determinant() != 0;
  }

  static Matrix4x4 translation(valueT x, valueT y, valueT z) {
    Matrix4x4 m4x4;
    m4x4.m4[3] = x;
    m4x4.m4[7] = y;
    m4x4.m4[11] = z;
    m4x4.updateInverseCache();
    return m4x4;
  }

  static Matrix4x4 scale(valueT x, valueT y, valueT z) {
    Matrix4x4 m4x4;
    m4x4.m4[0] = x;
    m4x4.m4[5] = y;
    m4x4.m4[10] = z;
    m4x4.updateInverseCache();
    return m4x4;
  }

  Matrix4x4 inverse();

  // book implementation
  Matrix4x4 inverseSlow() const;

  std::array<valueT, 16> to_array() const {
    return {
        m4[0],
        m4[1],
        m4[2],
        m4[3],
        m4[4],
        m4[5],
        m4[6],
        m4[7],
        m4[8],
        m4[9],
        m4[10],
        m4[11],
        m4[12],
        m4[13],
        m4[14],
        m4[15]};
  }

  std::array<valueT, 16> m4 = {};

 private:
  const int ROWSIZE = 4;

  std::array<valueT, 16> inverseCache;
  // cache of inverse of this matrix, needed because inverting is high frequency.
  // Much faster invert than the book version.
  // Copied from https://stackoverflow.com/questions/1148309/inverting-a-4x4-matrix
  // Which copied from https://glm.g-truc.net/0.9.9/index.html

  void updateInverseCache() {
    std::array<valueT, 16>& inv = inverseCache;
    valueT det;
    int i;

    inv[0] = m4[5] * m4[10] * m4[15] - m4[5] * m4[11] * m4[14] - m4[9] * m4[6] * m4[15] +
        m4[9] * m4[7] * m4[14] + m4[13] * m4[6] * m4[11] - m4[13] * m4[7] * m4[10];
    inv[4] = -m4[4] * m4[10] * m4[15] + m4[4] * m4[11] * m4[14] + m4[8] * m4[6] * m4[15] -
        m4[8] * m4[7] * m4[14] - m4[12] * m4[6] * m4[11] + m4[12] * m4[7] * m4[10];
    inv[8] = m4[4] * m4[9] * m4[15] - m4[4] * m4[11] * m4[13] - m4[8] * m4[5] * m4[15] +
        m4[8] * m4[7] * m4[13] + m4[12] * m4[5] * m4[11] - m4[12] * m4[7] * m4[9];
    inv[12] = -m4[4] * m4[9] * m4[14] + m4[4] * m4[10] * m4[13] + m4[8] * m4[5] * m4[14] -
        m4[8] * m4[6] * m4[13] - m4[12] * m4[5] * m4[10] + m4[12] * m4[6] * m4[9];
    inv[1] = -m4[1] * m4[10] * m4[15] + m4[1] * m4[11] * m4[14] + m4[9] * m4[2] * m4[15] -
        m4[9] * m4[3] * m4[14] - m4[13] * m4[2] * m4[11] + m4[13] * m4[3] * m4[10];
    inv[5] = m4[0] * m4[10] * m4[15] - m4[0] * m4[11] * m4[14] - m4[8] * m4[2] * m4[15] +
        m4[8] * m4[3] * m4[14] + m4[12] * m4[2] * m4[11] - m4[12] * m4[3] * m4[10];
    inv[9] = -m4[0] * m4[9] * m4[15] + m4[0] * m4[11] * m4[13] + m4[8] * m4[1] * m4[15] -
        m4[8] * m4[3] * m4[13] - m4[12] * m4[1] * m4[11] + m4[12] * m4[3] * m4[9];
    inv[13] = m4[0] * m4[9] * m4[14] - m4[0] * m4[10] * m4[13] - m4[8] * m4[1] * m4[14] +
        m4[8] * m4[2] * m4[13] + m4[12] * m4[1] * m4[10] - m4[12] * m4[2] * m4[9];
    inv[2] = m4[1] * m4[6] * m4[15] - m4[1] * m4[7] * m4[14] - m4[5] * m4[2] * m4[15] +
        m4[5] * m4[3] * m4[14] + m4[13] * m4[2] * m4[7] - m4[13] * m4[3] * m4[6];
    inv[6] = -m4[0] * m4[6] * m4[15] + m4[0] * m4[7] * m4[14] + m4[4] * m4[2] * m4[15] -
        m4[4] * m4[3] * m4[14] - m4[12] * m4[2] * m4[7] + m4[12] * m4[3] * m4[6];
    inv[10] = m4[0] * m4[5] * m4[15] - m4[0] * m4[7] * m4[13] - m4[4] * m4[1] * m4[15] +
        m4[4] * m4[3] * m4[13] + m4[12] * m4[1] * m4[7] - m4[12] * m4[3] * m4[5];
    inv[14] = -m4[0] * m4[5] * m4[14] + m4[0] * m4[6] * m4[13] + m4[4] * m4[1] * m4[14] -
        m4[4] * m4[2] * m4[13] - m4[12] * m4[1] * m4[6] + m4[12] * m4[2] * m4[5];
    inv[3] = -m4[1] * m4[6] * m4[11] + m4[1] * m4[7] * m4[10] + m4[5] * m4[2] * m4[11] -
        m4[5] * m4[3] * m4[10] - m4[9] * m4[2] * m4[7] + m4[9] * m4[3] * m4[6];
    inv[7] = m4[0] * m4[6] * m4[11] - m4[0] * m4[7] * m4[10] - m4[4] * m4[2] * m4[11] +
        m4[4] * m4[3] * m4[10] + m4[8] * m4[2] * m4[7] - m4[8] * m4[3] * m4[6];
    inv[11] = -m4[0] * m4[5] * m4[11] + m4[0] * m4[7] * m4[9] + m4[4] * m4[1] * m4[11] -
        m4[4] * m4[3] * m4[9] - m4[8] * m4[1] * m4[7] + m4[8] * m4[3] * m4[5];
    inv[15] = m4[0] * m4[5] * m4[10] - m4[0] * m4[6] * m4[9] - m4[4] * m4[1] * m4[10] +
        m4[4] * m4[2] * m4[9] + m4[8] * m4[1] * m4[6] - m4[8] * m4[2] * m4[5];

    det = m4[0] * inv[0] + m4[1] * inv[4] + m4[2] * inv[8] + m4[3] * inv[12];
    if (det != 0) {
      det = 1.0 / det;

      for (i = 0; i < 16; i++) {
        inv[i] = static_cast<valueT>(inv[i] * det);
      }
    } else {
      inv = Matrix4x4::identity().to_array();
    }
  }
};

// generic matrix of x row and y coloumn size
template <typename matrixValueT>
class MatrixXxX {
 public:
  MatrixXxX(unsigned rows, unsigned cols) : mRows(rows), mCols(cols), mData(rows * cols) {}

  MatrixXxX(unsigned rows, unsigned cols, std::vector<Tuple>& matrixElements)
      : mRows(rows), mCols(cols), mData(rows * cols) {
    for (unsigned i = 0; i < rows; ++i) {
      for (unsigned j = 0; j < cols; ++j) {
        mData[i * cols + j] = matrixElements[i].components[j];
      }
    }
  }

  MatrixXxX(unsigned rows, unsigned cols, std::vector<matrixValueT> matrixElements)
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

  static MatrixXxX identity(int matrixSquareSize);

  matrixValueT& operator()(unsigned row, unsigned col) {
    return mData[row * mCols + col];
  }
  matrixValueT operator()(unsigned row, unsigned col) const {
    return mData[row * mCols + col];
  }

  bool operator==(const MatrixXxX& rhs) const;

  bool operator!=(const MatrixXxX& rhs) const {
    return !operator==(rhs);
  }

  MatrixXxX operator*(const MatrixXxX& rhs) const;

  Tuple operator*(const Tuple& rhs) const;

  MatrixXxX transpose() const;

  matrixValueT determinant() const;

  MatrixXxX submatrix(int rowRemove, int colRemove) const;

  matrixValueT minor(int row, int col) const;

  matrixValueT cofactor(int row, int col) const;

  bool invertible() const {
    return determinant() != 0;
  }

  MatrixXxX<matrixValueT> inverse() const;

  template <typename valueT>
  static MatrixXxX<matrixValueT> translationMatrix(valueT x, valueT y, valueT z);

 private:
  size_t mRows;
  size_t mCols;
  std::vector<matrixValueT> mData;
};
}; // namespace jdRay
