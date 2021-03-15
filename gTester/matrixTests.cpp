#include <array>
#include "Matrix.cpp"
#include "pch.h"
// CHAPTER 3

// Scenario: A 2x2 matrix ought to be representable
//    Given the following 2x2 matrix M :
//    | -3 | 5 |
//    | 1 | -2 |
//    Then M[0, 0] = -3
//    And M[0, 1] = 5
//    And M[1, 0] = 1
//    And M[1, 1] = -2
TEST(MatrixTests, Construct2X2Matrix) {
  Matrix2x2<float> test(std::array<float, 4>{-3, 5, 1, -2});

  EXPECT_FLOAT_EQ(test.m2[0], -3);
  EXPECT_FLOAT_EQ(test.m2[1], 5);
  EXPECT_FLOAT_EQ(test.m2[2], 1);
  EXPECT_FLOAT_EQ(test.m2[3], -2);
}

// Scenario: A 3x3 matrix ought to be representable
//  Given the following 3x3 matrix M :
//  | -3 | 5 | 0 |
//  | 1 | -2 | -7 |
//  | 0 | 1 | 1 |
//  Then M[0, 0] = -3
//  And M[1, 1] = -2
//  And M[2, 2] = 1
TEST(MatrixTests, Construct3X3Matrix) {
  Matrix3x3<float> test(std::array<float, 9>{-3, 5, 0, 1, -2, -7, 0, 1, 1});

  EXPECT_FLOAT_EQ(test(0, 0), -3);
  EXPECT_FLOAT_EQ(test(1, 1), -2);
  EXPECT_FLOAT_EQ(test(2, 2), 1);
}

// Scenario: Constructing and inspecting a 4x4 matrix
//    Given the following 4x4 matrix M :
//    | 1 | 2 | 3 | 4 |
//    | 5.5 | 6.5 | 7.5 | 8.5 |
//    | 9 | 10 | 11 | 12 |
//    | 13.5 | 14.5 | 15.5 | 16.5 |
//    Then M[0, 0] = 1
//    And M[0, 3] = 4
//    And M[1, 0] = 5.5
//    And M[1, 2] = 7.5
//    And M[2, 2] = 11
//    And M[3, 0] = 13.5
//    And M[3, 2] = 15.5
TEST(MatrixTests, Construct4x4Matrix) {
  Matrix4x4<float> test(
      std::array<float, 16>{1, 2, 3, 4, 5.5, 6.5, 7.5, 8.5, 9, 10, 11, 12, 13.5, 14.5, 15.5, 16.5});

  EXPECT_FLOAT_EQ(test(0, 0), 1);
  EXPECT_FLOAT_EQ(test(0, 3), 4);
  EXPECT_FLOAT_EQ(test(1, 0), 5.5);
  EXPECT_FLOAT_EQ(test(1, 2), 7.5);
  EXPECT_FLOAT_EQ(test(2, 2), 11);
  EXPECT_FLOAT_EQ(test(3, 0), 13.5);
  EXPECT_FLOAT_EQ(test(3, 2), 15.5);
}

// Scenario: Matrix equality with identical matrices
//    Given the following matrix A :
//        | 1 | 2 | 3 | 4 |
//        | 5 | 6 | 7 | 8 |
//        | 9 | 8 | 7 | 6 |
//        | 5 | 4 | 3 | 2 |
//    And the following matrix B :
//        | 1 | 2 | 3 | 4 |
//        | 5 | 6 | 7 | 8 |
//        | 9 | 8 | 7 | 6 |
//        | 5 | 4 | 3 | 2 |
//    Then A = B
TEST(MatrixTests, CompareIdenticalMatrices) {
  Tuple r1(1, 2, 3, 4);
  Tuple r2(5, 6, 7, 8);
  Tuple r3(9, 8, 7, 6);
  Tuple r4(5, 4, 3, 2);
  std::vector<Tuple> rows = {r1, r2, r3, r4};
  Matrix4x4<float> test1(rows);
  Matrix4x4<float> test2(rows);
  EXPECT_TRUE(test1 == test2);
}

// Scenario: Matrix equality with different matrices
//    Given the following matrix A :
//        | 1 | 2 | 3 | 4 |
//        | 5 | 6 | 7 | 8 |
//        | 9 | 8 | 7 | 6 |
//        | 5 | 4 | 3 | 2 |
//    And the following matrix B :
//        | 2 | 3 | 4 | 5 |
//        | 6 | 7 | 8 | 9 |
//        | 8 | 7 | 6 | 5 |
//        | 4 | 3 | 2 | 1 |
//    Then A != B
TEST(MatrixTests, CompareNotIdenticalMatrices) {
  Tuple r1a(1, 2, 3, 4);
  Tuple r2a(5, 6, 7, 8);
  Tuple r3a(9, 8, 7, 6);
  Tuple r4a(5, 4, 3, 2);
  std::vector<Tuple> mRows1 = {r1a, r2a, r3a, r4a};

  Tuple r1b(2, 3, 4, 5);
  Tuple r2b(6, 7, 8, 9);
  Tuple r3b(8, 7, 6, 5);
  Tuple r4b(4, 3, 2, 1);
  std::vector<Tuple> mRows2 = {r1b, r2b, r3b, r4b};

  Matrix4x4<float> test1(mRows1);
  Matrix4x4<float> test2(mRows2);
  EXPECT_TRUE(test1 != test2);
}

// Scenario: Multiplying two matrices
//    Given the following matrix A :
//        | 1 | 2 | 3 | 4 |
//        | 5 | 6 | 7 | 8 |
//        | 9 | 8 | 7 | 6 |
//        | 5 | 4 | 3 | 2 |
//    And the following matrix B :
//        | -2 | 1 | 2 | 3 |
//        | 3 | 2 | 1 | -1 |
//        | 4 | 3 | 6 | 5 |
//        | 1 | 2 | 7 | 8 |
//    Then A * B is the following 4x4 matrix :
//        | 20 | 22 | 50 | 48 |
//        | 44 | 54 | 114 | 108 |
//        | 40 | 58 | 110 | 102 |
//        | 16 | 26 | 46 | 42 |
TEST(MatrixTests, MatrixMultiplication) {
  Tuple r1a(1, 2, 3, 4);
  Tuple r2a(5, 6, 7, 8);
  Tuple r3a(9, 8, 7, 6);
  Tuple r4a(5, 4, 3, 2);
  std::vector<Tuple> mRows1 = {r1a, r2a, r3a, r4a};
  Matrix4x4<float> matrixA(mRows1);

  Tuple r1b(-2, 1, 2, 3);
  Tuple r2b(3, 2, 1, -1);
  Tuple r3b(4, 3, 6, 5);
  Tuple r4b(1, 2, 7, 8);
  std::vector<Tuple> mRows2 = {r1b, r2b, r3b, r4b};
  Matrix4x4<float> matrixB(mRows2);

  Tuple r1c(20, 22, 50, 48);
  Tuple r2c(44, 54, 114, 108);
  Tuple r3c(40, 58, 110, 102);
  Tuple r4c(16, 26, 46, 42);
  std::vector<Tuple> mRows3 = {r1c, r2c, r3c, r4c};
  Matrix4x4<float> matrixC(mRows3);

  EXPECT_TRUE(matrixA * matrixB == matrixC);
}

// Scenario: A matrix multiplied by a tuple
//    Given the following matrix A :
//          | 1 | 2 | 3 | 4 |
//          | 2 | 4 | 4 | 2 |
//          | 8 | 6 | 4 | 1 |
//          | 0 | 0 | 0 | 1 |
//    And b ← tuple(1, 2, 3, 1)
//    Then A * b = tuple(18, 24, 33, 1)
TEST(MatrixTests, MatrixTupleMultiplication) {
  Tuple r1(1, 2, 3, 4);
  Tuple r2(2, 4, 4, 2);
  Tuple r3(8, 6, 4, 1);
  Tuple r4(0, 0, 0, 1);
  std::vector<Tuple> mARows = {r1, r2, r3, r4};
  Matrix4x4<float> matrixA(mARows);

  Tuple b(1, 2, 3, 1);
  EXPECT_TRUE(matrixA * b == Tuple(18, 24, 33, 1));
}

// Scenario: Multiplying a matrix by the identity matrix
//    Given the following matrix A :
//          | 0 | 1 | 2 | 4 |
//          | 1 | 2 | 4 | 8 |
//          | 2 | 4 | 8 | 16 |
//          | 4 | 8 | 16 | 32 |
//    Then A * identity_matrix = A
TEST(MatrixTests, MatrixIdentity) {
  Tuple r1(0, 1, 2, 4);
  Tuple r2(1, 2, 4, 8);
  Tuple r3(2, 4, 8, 16);
  Tuple r4(4, 8, 16, 32);
  std::vector<Tuple> mARows = {r1, r2, r3, r4};
  Matrix4x4<float> matrixA(mARows);

  EXPECT_TRUE(matrixA * Matrix4x4<float>::identity() == matrixA);
}

// Scenario: Multiplying the identity matrix by a tuple
//    Given a ← tuple(1, 2, 3, 4)
//    Then identity_matrix * a = a
TEST(MatrixTests, MatrixIdentityTuple) {
  Tuple a(1, 2, 3, 4);

  EXPECT_TRUE(Matrix4x4<float>::identity() * a == a);
}

// Scenario: Transposing a matrix
// Given the following matrix A:
//    | 0 | 9 | 3 | 0 |
//    | 9 | 8 | 0 | 8 |
//    | 1 | 8 | 5 | 3 |
//    | 0 | 0 | 5 | 8 |
// Then transpose(A) is the following matrix:
//    | 0 | 9 | 1 | 0 |
//    | 9 | 8 | 8 | 0 |
//    | 3 | 0 | 5 | 5 |
//    | 0 | 8 | 3 | 8 |
TEST(MatrixTests, MatrixTranspose) {
  Tuple r1a(0, 9, 3, 0);
  Tuple r2a(9, 8, 0, 8);
  Tuple r3a(1, 8, 5, 3);
  Tuple r4a(0, 0, 5, 8);
  std::vector<Tuple> mARows = {r1a, r2a, r3a, r4a};
  Matrix4x4<float> matrixA(mARows);

  Tuple r1b(0, 9, 1, 0);
  Tuple r2b(9, 8, 8, 0);
  Tuple r3b(3, 0, 5, 5);
  Tuple r4b(0, 8, 3, 8);
  std::vector<Tuple> mBRows = {r1b, r2b, r3b, r4b};
  Matrix4x4<float> matrixB(mBRows);

  // Testing to see if non square matrices can be transposed
  MatrixXxX<float> matrixA1(1, 2);
  MatrixXxX<float> matrixB1(2, 1);

  matrixA1(0, 0) = 0;
  matrixA1(0, 1) = 1;

  matrixB1(0, 0) = 0;
  matrixB1(1, 0) = 1;

  EXPECT_TRUE(matrixA.transpose() == matrixB);
  EXPECT_TRUE(matrixA1.transpose() == matrixB1);
}

// Scenario: Transposing the identity matrix
//  Given A ← transpose(identity_matrix)
//  Then A = identity_matrix
TEST(MatrixTests, MatrixIdentityTranspose) {
  auto iMatrix = Matrix4x4<float>::identity();

  EXPECT_TRUE(iMatrix.transpose() == iMatrix);
}

// Scenario: Calculating the determinant of a 2x2 matrix
// Given the following 2x2 matrix A:
//  | 1 | 5 |
//  | -3 | 2 |
// Then determinant(A) = 17
TEST(MatrixTests, Matrix2x2Determinant) {
  std::array<float, 4> inputVals = {1, 5, -3, 2};
  Matrix2x2<float> m2x2(inputVals);

  EXPECT_TRUE(m2x2.determinant() == 17);
}

// Scenario: A submatrix of a 3x3 matrix is a 2x2 matrix
// Given the following 3x3 matrix A:
//| 1 | 5 | 0 |
//| -3 | 2 | 7 |
//| 0 | 6 | -3 |
// Then submatrix(A, 0, 2) is the following 2x2 matrix:
//| -3 | 2 |
//| 0 | 6 |
TEST(MatrixTests, MatrixSubMatrixATest) {
  std::array<float, 9> inputVals3x3 = {1, 5, 0, -3, 2, 7, 0, 6, -3};
  Matrix3x3<float> m3x3(inputVals3x3);

  std::array<float, 4> inputVals2x2 = {-3, 2, 0, 6};
  Matrix2x2<float> m2x2(inputVals2x2);

  EXPECT_TRUE(m3x3.submatrix(0, 2) == m2x2);
}
// Scenario: A submatrix of a 4x4 matrix is a 3x3 matrix
// Given the following 4x4 matrix A:
//| -6 | 1 | 1 | 6 |
//| -8 | 5 | 8 | 6 |
//| -1 | 0 | 8 | 2 |
//| -7 | 1 | -1 | 1 |
// Then submatrix(A, 2, 1) is the following 3x3 matrix:
//| -6 | 1 | 6 |
//| -8 | 8 | 6 |
//| -7 | -1 | 1 |
TEST(MatrixTests, MatrixSubMatrixBTest) {
  Tuple r1(-6, 1, 1, 6);
  Tuple r2(-8, 5, 8, 6);
  Tuple r3(-1, 0, 8, 2);
  Tuple r4(-7, 1, -1, 1);
  std::vector<Tuple> mRows = {r1, r2, r3, r4};
  Matrix4x4<float> m4x4(mRows);

  std::array<float, 9> inputVals3x3 = {-6, 1, 6, -8, 8, 6, -7, -1, 1};
  Matrix3x3<float> m3x3(inputVals3x3);

  EXPECT_TRUE(m4x4.submatrix(2, 1) == m3x3);
}

// Scenario: Calculating a minor of a 3x3 matrix
// Given the following 3x3 matrix A:
//| 3 | 5 | 0 |
//| 2 | -1 | -7 |
//| 6 | -1 | 5 |
// And B ← submatrix(A, 1, 0)
// Then determinant(B) = 25
// And minor(A, 1, 0) = 25
TEST(MatrixTests, MatrixMinor) {
  std::array<float, 9> inputVals3x3 = {3, 5, 0, 2, -1, -7, 6, -1, 5};
  Matrix3x3<float> m3x3(inputVals3x3);

  Matrix2x2<float> mSubmatrix = m3x3.submatrix(1, 0);
  EXPECT_TRUE(mSubmatrix.determinant() == m3x3.minor(1, 0));
}

// Scenario: Calculating a cofactor of a 3x3 matrix
// Given the following 3x3 matrix A:
//| 3 | 5 | 0 |
//| 2 | -1 | -7 |
//| 6 | -1 | 5 |
// Then minor(A, 0, 0) = -12
// And cofactor(A, 0, 0) = -12
// And minor(A, 1, 0) = 25
// And cofactor(A, 1, 0) = -25
TEST(MatrixTests, MatrixCofactor) {
  std::array<float, 9> inputVals3x3 = {3, 5, 0, 2, -1, -7, 6, -1, 5};
  Matrix3x3<float> m3x3(inputVals3x3);

  EXPECT_TRUE(m3x3.minor(0, 0) == -12);
  EXPECT_TRUE(m3x3.cofactor(0, 0) == -12);
  EXPECT_TRUE(m3x3.minor(1, 0) == 25);
  EXPECT_TRUE(m3x3.cofactor(1, 0) == -25);
}

// Scenario: Calculating the determinant of a 3x3 matrix
// Given the following 3x3 matrix A:
//| 1 | 2 | 6 |
//| -5 | 8 | -4 |
//| 2 | 6 | 4 |
// Then cofactor(A, 0, 0) = 56
// And cofactor(A, 0, 1) = 12
// And cofactor(A, 0, 2) = -46
// And determinant(A) = -196
TEST(MatrixTests, Matrix3x3Determinant) {
  std::array<float, 9> inputVals3x3 = {1, 2, 6, -5, 8, -4, 2, 6, 4};
  Matrix3x3<float> m3x3(inputVals3x3);

  EXPECT_TRUE(m3x3.cofactor(0, 0) == 56);
  EXPECT_TRUE(m3x3.cofactor(0, 1) == 12);
  EXPECT_TRUE(m3x3.cofactor(0, 2) == -46);
  EXPECT_TRUE(m3x3.determinant() == -196);
}

// Scenario: Calculating the determinant of a 4x4 matrix
// Given the following 4x4 matrix A:
//| -2 | -8 | 3 | 5 |
//| -3 | 1 | 7 | 3 |
//| 1 | 2 | -9 | 6 |
//| -6 | 7 | 7 | -9 |
// Then cofactor(A, 0, 0) = 690
// And cofactor(A, 0, 1) = 447
// And cofactor(A, 0, 2) = 210
// And cofactor(A, 0, 3) = 51
// And determinant(A) = -4071
TEST(MatrixTests, Matrix4x4Determinant) {
  Tuple r1(-2, -8, 3, 5);
  Tuple r2(-3, 1, 7, 3);
  Tuple r3(1, 2, -9, 6);
  Tuple r4(-6, 7, 7, -9);
  std::vector<Tuple> mRows = {r1, r2, r3, r4};
  Matrix4x4<float> m4x4(mRows);

  EXPECT_TRUE(m4x4.cofactor(0, 0) == 690);
  EXPECT_TRUE(m4x4.cofactor(0, 1) == 447);
  EXPECT_TRUE(m4x4.cofactor(0, 2) == 210);
  EXPECT_TRUE(m4x4.cofactor(0, 3) == 51);
  EXPECT_TRUE(m4x4.determinant() == -4071);
}

// Scenario: Testing an invertible matrix for invertibility
// Given the following 4x4 matrix A:
//| 6 | 4 | 4 | 4 |
//| 5 | 5 | 7 | 6 |
//| 4 | -9 | 3 | -7 |
//| 9 | 1 | 7 | -6 |
// Then determinant(A) = -2120
// And A is invertible
TEST(MatrixTests, Matrix4x4Invertibility) {
  Tuple r1(6, 4, 4, 4);
  Tuple r2(5, 5, 7, 6);
  Tuple r3(4, -9, 3, -7);
  Tuple r4(9, 1, 7, -6);
  std::vector<Tuple> mRows = {r1, r2, r3, r4};
  Matrix4x4<float> m4x4(mRows);

  EXPECT_TRUE(m4x4.determinant() == -2120);
  EXPECT_TRUE(m4x4.invertible());
}

// Scenario: Testing a noninvertible matrix for invertibility
// Given the following 4x4 matrix A:
//| -4 | 2 | -2 | -3 |
//| 9 | 6 | 2 | 6 |
//| 0 | -5 | 1 | -5 |
//| 0 | 0 | 0 | 0 |
// Then determinant(A) = 0
// And A is not invertible
TEST(MatrixTests, Matrix4x4NonInvertibility) {
  Tuple r1(-4, 2, -2, -3);
  Tuple r2(9, 6, 2, 6);
  Tuple r3(0, -5, 1, -5);
  Tuple r4(0, 0, 0, 0);
  std::vector<Tuple> mRows = {r1, r2, r3, r4};
  Matrix4x4<float> m4x4(mRows);

  EXPECT_TRUE(m4x4.determinant() == 0);
  EXPECT_FALSE(m4x4.invertible());
}

// Scenario: Calculating the inverse of a matrix
// Given the following 4x4 matrix A:
//| -5 | 2 | 6 | -8 |
//| 1 | -5 | 1 | 8 |
//| 7 | 7 | -6 | -7 |
//| 1 | -3 | 7 | 4 |
// And B ← inverse(A)
// Then determinant(A) = 532
// And cofactor(A, 2, 3) = -160
// And B[3,2] = -160/532
// And cofactor(A, 3, 2) = 105
// And B[2,3] = 105/532
// And B is the following 4x4 matrix:
//| 0.21805 | 0.45113 | 0.24060 | -0.04511 |
//| -0.80827 | -1.45677 | -0.44361 | 0.52068 |
//| -0.07895 | -0.22368 | -0.05263 | 0.19737 |
//| -0.52256 | -0.81391 | -0.30075 | 0.30639 |
TEST(MatrixTests, Matrix4x4InvertA) {
  Tuple r1(-5, 2, 6, -8);
  Tuple r2(1, -5, 1, 8);
  Tuple r3(7, 7, -6, -7);
  Tuple r4(1, -3, 7, 4);
  std::vector<Tuple> mRowsA = {r1, r2, r3, r4};
  Matrix4x4<double> m4x4A(mRowsA);

  auto m4x4Inv = m4x4A.inverse();

  Tuple r1b(0.21805, 0.45113, 0.24060, -0.04511);
  Tuple r2b(-0.80827, -1.45677, -0.44361, 0.52068);
  Tuple r3b(-0.07895, -0.22368, -0.05263, 0.19737);
  Tuple r4b(-0.52256, -0.81391, -0.30075, 0.30639);
  std::vector<Tuple> mRowCompare = {r1b, r2b, r3b, r4b};
  Matrix4x4<double> m4x4C(mRowCompare);

  EXPECT_TRUE(m4x4A.determinant() == 532);
  EXPECT_TRUE(m4x4A.cofactor(2, 3) == -160);
  EXPECT_NEAR(m4x4Inv(3, 2), -160.0 / 532.0, .001);
  EXPECT_TRUE(m4x4A.cofactor(3, 2) == 105);
  EXPECT_NEAR(m4x4Inv(2, 3), 105.0 / 532.0, .001);
  EXPECT_TRUE(m4x4Inv == m4x4C);
}

// CHAPTER 4
// Scenario: Multiplying by a translation matrix
// Given transform ← translation(5, -3, 2)
// And p ← point(-3, 4, 5)
// Then transform * p = point(2, 1, 7)
TEST(MatrixTransformationTests, TranslationMatrix4x4) {
  auto translationM = Matrix4x4<double>::translation(5, -3, 2);
  Point3 p(-3, 4, 5);
  EXPECT_TRUE(translationM * p == Point3(2, 1, 7));
}

// Scenario: Multiplying by the inverse of a translation matrix
// Given transform ← translation(5, -3, 2)
// And inv ← inverse(transform)
// And p ← point(-3, 4, 5)
// Then inv * p = point(-8, 7, 3)
TEST(MatrixTransformationTests, InverseTranslationMatrix4x4) {
  auto translationM = Matrix4x4<double>::translation(5, -3, 2);
  auto inv = translationM.inverse();
  Point3 p(-3, 4, 5);
  EXPECT_TRUE(inv * p == Point3(-8, 7, 3));
}

// Scenario: Translation does not affect vectors
// Given transform ← translation(5, -3, 2)
// And v ← vector(-3, 4, 5)
// Then transform * v = v
TEST(MatrixTransformationTests, TranslationMatrix4x4IgnoresVectors) {
  auto translationM = Matrix4x4<double>::translation(5, -3, 2);
  Vector3 v(-3, 4, 5);
  EXPECT_TRUE(translationM * v == v);
}

// Scenario: A scaling matrix applied to a point
// Given transform ← scaling(2, 3, 4)
// And p ← point(-4, 6, 8)
// Then transform * p = point(-8, 18, 32)
TEST(MatrixTransformationTests, ScaleMatrix4x4) {
  auto scaleM = Matrix4x4<double>::scale(2, 3, 4);
  Point3 p(-4, 6, 8);
  EXPECT_TRUE(scaleM * p == Point3(-8, 18, 32));
}

// Scenario: A scaling matrix applied to a vector
// Given transform ← scaling(2, 3, 4)
// And v ← vector(-4, 6, 8)
// Then transform * v = vector(-8, 18, 32)
TEST(MatrixTransformationTests, VectorMultScaleMatrix4x4) {
  auto scaleM = Matrix4x4<double>::scale(2, 3, 4);
  Vector3 v(-4, 6, 8);
  EXPECT_TRUE(scaleM * v == Vector3(-8, 18, 32));
}

// Scenario: Multiplying by the inverse of a scaling matrix
// Given transform ← scaling(2, 3, 4)
// And inv ← inverse(transform)
// And v ← vector(-4, 6, 8)
// Then inv * v = vector(-2, 2, 2)
TEST(MatrixTransformationTests, VectorMultInverseScaleMatrix4x4) {
  auto scaleM = Matrix4x4<double>::scale(2, 3, 4);
  auto inv = scaleM.inverse();
  Vector3 v(-4, 6, 8);
  EXPECT_TRUE(inv * v == Vector3(-2, 2, 2));
}

// Scenario: Reflection is scaling by a negative value
// Given transform ← scaling(-1, 1, 1)
// And p ← point(2, 3, 4)
// Then transform * p = point(-2, 3, 4)
TEST(MatrixTransformationTests, PointNegativeScaleMatrix4x4) {
  auto scaleM = Matrix4x4<double>::scale(-1, 1, 1);
  Point3 p(2, 3, 4);
  EXPECT_TRUE(scaleM * p == Point3(-2, 3, 4));
}
