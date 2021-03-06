﻿#include "Tuples.cpp"
#include "pch.h"
using namespace jdRay;

// Scenario: A tuple with w = 1.0 is a point
//	Given a ← tuple(4.3, -4.2, 3.1, 1.0)
//	Then a.x = 4.3
//	And a.y = -4.2
//	And a.z = 3.1
//	And a.w = 1.0
//	And a is a point
//	And a is not a vector
TEST(TupleTests, PointIsPoint) {
  Point3 point(4.3, -4.2, 3.1);

  EXPECT_FLOAT_EQ(point.x(), 4.3);
  EXPECT_FLOAT_EQ(point.y(), -4.2);
  EXPECT_FLOAT_EQ(point.z(), 3.1);
  EXPECT_FLOAT_EQ(point.w(), 1.0);
  EXPECT_TRUE(point.IsPoint3());
  EXPECT_FALSE(point.IsVector3());
}

//	Scenario : A tuple with w = 0 is a vector
//	Given a ← tuple(4.3, -4.2, 3.1, 0.0)
//	Then a.x = 4.3
//	And a.y = -4.2
//	And a.z = 3.1
//	And a.w = 0.0
//	And a is not a point
//	And a is a vector
TEST(TupleTests, VectorIsVector) {
  Vector3 vector(4.3, -4.2, 3.1);

  EXPECT_FLOAT_EQ(vector.x(), 4.3);
  EXPECT_FLOAT_EQ(vector.y(), -4.2);
  EXPECT_FLOAT_EQ(vector.z(), 3.1);
  EXPECT_FLOAT_EQ(vector.w(), 0.0);
  EXPECT_FALSE(vector.IsPoint3());
  EXPECT_TRUE(vector.IsVector3());
}

// Scenario: point() creates Tuples with w = 1
//	Given p ← point(4, -4, 3)
//	Then p = tuple(4, -4, 3, 1)
TEST(TupleTests, CreatePoint) {
  Point3 point(4.3, -4.2, 3.1);

  EXPECT_FLOAT_EQ(point.x(), 4.3);
  EXPECT_FLOAT_EQ(point.y(), -4.2);
  EXPECT_FLOAT_EQ(point.z(), 3.1);
  EXPECT_FLOAT_EQ(point.w(), 1.0);
}

// Scenario : vector() creates Tuples with w = 0
//	Given v ← vector(4, -4, 3)
//	Then v = tuple(4, -4, 3, 0)

TEST(TupleTests, CreateVector) {
  Vector3 vector(4.3, -4.2, 3.1);

  EXPECT_FLOAT_EQ(vector.x(), 4.3);
  EXPECT_FLOAT_EQ(vector.y(), -4.2);
  EXPECT_FLOAT_EQ(vector.z(), 3.1);
  EXPECT_FLOAT_EQ(vector.w(), 0.0);
}

// Scenario: Adding two Tuples
//	Given a1 ← tuple(3, -2, 5, 1)
//	And a2 ← tuple(-2, 3, 1, 0)
//	Then a1 + a2 = tuple(1, 1, 6, 1)
TEST(TupleTests, AddingVectorToPoint) {
  Point3 point(3, -2, 5);
  Vector3 vector(-2, 3, 1);

  Point3 pointCompare = point + vector;

  EXPECT_TRUE(pointCompare == Point3(1, 1, 6));
}

// Scenario: Subtracting two points
//	Given p1 ← point(3, 2, 1)
//	And p2 ← point(5, 6, 7)
//	Then p1 - p2 = vector(-2, -4, -6)
TEST(TupleTests, SubtractingPoints) {
  Point3 point1(3, 2, 1);
  Point3 point2(5, 6, 7);

  Vector3 vectorCompare = point1 - point2;
  EXPECT_TRUE(vectorCompare == Vector3(-2, -4, -6));
}

// Scenario: Subtracting a vector from a point
//	Given p ← point(3, 2, 1)
//	And v ← vector(5, 6, 7)
//	Then p - v = point(-2, -4, -6)
TEST(TupleTests, SubtractingVectorFromPoint) {
  Point3 point(3, 2, 1);
  Vector3 vector(5, 6, 7);

  Point3 pointCompare = point - vector;
  EXPECT_TRUE(pointCompare == Point3(-2, -4, -6));
}

// Scenario: Subtracting two vectors
//	Given v1 ← vector(3, 2, 1)
//	And v2 ← vector(5, 6, 7)
//	Then v1 - v2 = vector(-2, -4, -6)
TEST(TupleTests, SubtractingTwoVectors) {
  Vector3 v1(3, 2, 1);
  Vector3 v2(5, 6, 7);

  Vector3 vectorCompare = v1 - v2;
  EXPECT_TRUE(vectorCompare == Vector3(-2, -4, -6));
}

// Scenario: Subtracting a vector from the zero vector
//	Given zero ← vector(0, 0, 0)
//	And v ← vector(1, -2, 3)
//	Then zero - v = vector(-1, 2, -3)
TEST(TupleTests, SubtractVectorFromZeroVector) {
  Vector3 vector(1, -2, 3);

  Vector3 vectorCompare = Vector3::zero() - vector;
  EXPECT_TRUE(vectorCompare == Vector3(-1, 2, -3));
}

// Scenario: Negating a tuple
//	Given a ← tuple(1, -2, 3, -4)
//	Then - a = tuple(-1, 2, -3, 4)
TEST(TupleTests, NegateTuple) {
  Tuple tuple(1, -2, 3, -4);

  EXPECT_TRUE(-tuple == Tuple(-1, 2, -3, 4));
}

// Scenario: Multiplying a tuple by a scalar
//	Given a ← tuple(1, -2, 3, -4)
//	Then a * 3.5 = tuple(3.5, -7, 10.5, -14)
TEST(TupleTests, MultiplyTuple) {
  Tuple tuple(1, -2, 3, -4);
  Tuple multipliedTuple = tuple * 3.5;
  EXPECT_TRUE(multipliedTuple == Tuple(3.5, -7, 10.5, -14));
}

// Scenario : Multiplying a tuple by a fraction
//	Given a ← tuple(1, -2, 3, -4)
//	Then a * 0.5 = tuple(0.5, -1, 1.5, -2)
TEST(TupleTests, MultiplyTupleByFraction) {
  Tuple tuple(1, -2, 3, -4);
  Tuple multipliedTuple = tuple * 0.5;
  EXPECT_TRUE(multipliedTuple == Tuple(0.5, -1, 1.5, -2));
}

// Scenario: Dividing a tuple by a scalar
//	Given a ← tuple(1, -2, 3, -4)
//	Then a / 2 = tuple(0.5, -1, 1.5, -2)
TEST(TupleTests, DivideTupleByFraction) {
  Tuple tuple(1, -2, 3, -4);
  Tuple dividedTuple = tuple / 2;
  EXPECT_TRUE(dividedTuple == Tuple(0.5, -1, 1.5, -2));
}

// Scenario: Computing the magnitude of vector(1, 0, 0)
//	Given v ← vector(1, 0, 0)
//  Then magnitude(v) = 1
// Scenario: Computing the magnitude of vector(0, 1, 0)
//	Given v ← vector(0, 1, 0)
//	Then magnitude(v) = 1
// Scenario: Computing the magnitude of vector(0, 0, 1)
//	Given v ← vector(0, 0, 1)
//	Then magnitude(v) = 1
// Scenario : Computing the magnitude of vector(1, 2, 3)
//	Given v ← vector(1, 2, 3)
//	Then magnitude(v) = √14
// Scenario : Computing the magnitude of vector(-1, -2, -3)
//	Given v ← vector(-1, -2, -3)
//	Then magnitude(v) = √14
TEST(TupleTests, VectorMagnitudes) {
  Vector3 v1(1, 0, 0);
  Vector3 v2(0, 1, 0);
  Vector3 v3(0, 0, 1);
  Vector3 v4(1, 2, 3);
  Vector3 v5(-1, -2, -3);

  EXPECT_FLOAT_EQ(v1.magnitude(), 1);
  EXPECT_FLOAT_EQ(v2.magnitude(), 1);
  EXPECT_FLOAT_EQ(v3.magnitude(), 1);
  EXPECT_FLOAT_EQ(v4.magnitude(), 3.741657);
  EXPECT_FLOAT_EQ(v5.magnitude(), 3.741657);
}

// Scenario: Normalizing vector(4, 0, 0) gives(1, 0, 0)
//	Given v ← vector(4, 0, 0)
//	Then normalize(v) = vector(1, 0, 0)
// Scenario : Normalizing vector(1, 2, 3)
//	Given v ← vector(1, 2, 3)
//	# vector(1 / √14, 2 / √14, 3 / √14)
//	Then normalize(v) = approximately vector(0.26726, 0.53452, 0.80178)
// Scenario: The magnitude of a normalized vector
//	Given v ← vector(1, 2, 3)
//	When norm ← normalize(v)
//	Then magnitude(norm) = 1
TEST(TupleTests, NormalizeVectors) {
  Vector3 v1(4, 0, 0);
  Vector3 v2(1, 2, 3);
  Vector3 v3(1, 2, 3);

  EXPECT_TRUE(v1.normalize() == Vector3(1, 0, 0));
  EXPECT_TRUE(v2.normalize() == Vector3(0.26726, 0.53452, 0.80178));
  EXPECT_FLOAT_EQ(v3.normalize().magnitude(), 1);
}

// Scenario: The dot product of two Tuples
//	Given a ← vector(1, 2, 3)
//	And b ← vector(2, 3, 4)
//	Then dot(a, b) = 20
TEST(TupleTests, DotProduct) {
  Vector3 v1(1, 2, 3);
  Vector3 v2(2, 3, 4);

  EXPECT_FLOAT_EQ(Vector3::dotProduct(v1, v2), 20);
}

// Scenario: The cross product of two vectors
//	Given a ← vector(1, 2, 3)
//	And b ← vector(2, 3, 4)
//	Then cross(a, b) = vector(-1, 2, -1)
//	And cross(b, a) = vector(1, -2, 1)
TEST(TupleTests, CrossProduct) {
  Vector3 v1(1, 2, 3);
  Vector3 v2(2, 3, 4);

  EXPECT_TRUE(Vector3::crossProduct(v1, v2) == Vector3(-1, 2, -1));
  EXPECT_TRUE(Vector3::crossProduct(v2, v1) == Vector3(1, -2, 1));
}

// Scenario: Colors are(red, green, blue) Tuples
//	Given c ← color(-0.5, 0.4, 1.7)
//	Then c.red = -0.5
//	And c.green = 0.4
//	And c.blue = 1.7
TEST(TupleTests, ColorTuple) {
  Color c(-0.5, 0.4, 1.7);
  EXPECT_FLOAT_EQ(c.r(), -.5);
  EXPECT_FLOAT_EQ(c.g(), .4);
  EXPECT_FLOAT_EQ(c.b(), 1.7);
}

// Scenario: Adding colors
//	Given c1 ← color(0.9, 0.6, 0.75)
//	And c2 ← color(0.7, 0.1, 0.25)
//	Then c1 + c2 = color(1.6, 0.7, 1.0)
TEST(TupleTests, AddingColor) {
  Color c1(0.9, 0.6, 0.75);
  Color c2(0.7, 0.1, 0.25);

  Color addedColor = c1 + c2;

  EXPECT_TRUE(addedColor == Color(1.6, 0.7, 1.0));
}
// Scenario : Subtracting colors
//	Given c1 ← color(0.9, 0.6, 0.75)
//	And c2 ← color(0.7, 0.1, 0.25)
//	Then c1 - c2 = color(0.2, 0.5, 0.5)
TEST(TupleTests, SubtractingColor) {
  Color c1(0.9, 0.6, 0.75);
  Color c2(0.7, 0.1, 0.25);

  Color addedColor = c1 - c2;

  EXPECT_TRUE(addedColor == Color(0.2, 0.5, 0.5));
}
// Scenario : Multiplying a color by a scalar
//	Given c ← color(0.2, 0.3, 0.4)
//	Then c * 2 = color(0.4, 0.6, 0.8)
TEST(TupleTests, MultiplyingScalarColor) {
  Color c(0.2, 0.3, 0.4);

  Color multipliedColor = c * 2;

  EXPECT_TRUE(multipliedColor == Color(0.4, 0.6, 0.8));
}
// Scenario: Multiplying colors
//	Given c1 ← color(1, 0.2, 0.4)
//	And c2 ← color(0.9, 1, 0.1)
//	Then c1 * c2 = color(0.9, 0.2, 0.04)
TEST(TupleTests, MultiplyingColors) {
  Color c1(1, 0.2, 0.4);
  Color c2(0.9, 1, 0.1);

  Color multipliedColor = c1 * c2;

  EXPECT_TRUE(multipliedColor == Color(0.9, 0.2, 0.04));
}
