#include "Intersect.cpp"
#include "Matrix.cpp"
#include "Ray.cpp"
#include "pch.h"
using namespace jdRay;
// Chapter 5

// Scenario: Creating and querying a ray
//  Given origin ← point(1, 2, 3)
//  And direction ← vector(4, 5, 6)
//  When r ← ray(origin, direction)
//  Then r.origin = origin
//  And r.direction = direction
TEST(RayTests, Creation) {
  Point3 origin(1, 2, 3);
  Vector3 direction(4, 5, 6);
  Ray r(origin, direction);
  EXPECT_TRUE(r.origin == origin);
  EXPECT_TRUE(r.direction == direction);
}

// Scenario: Computing a point from a distance
//  Given r ← ray(point(2, 3, 4), vector(1, 0, 0))
//  Then position(r, 0) = point(2, 3, 4)
//  And position(r, 1) = point(3, 3, 4)
//  And position(r, -1) = point(1, 3, 4)
//  And position(r, 2.5) = point(4.5, 3, 4)
TEST(RayTests, PositionDistance) {
  Point3 p1(2, 3, 4);
  Vector3 v1(1, 0, 0);
  Ray r(p1, v1);
  EXPECT_TRUE(r.position(0) == p1);
  EXPECT_TRUE(r.position(1) == Point3(3, 3, 4));
  EXPECT_TRUE(r.position(-1) == Point3(1, 3, 4));
  EXPECT_TRUE(r.position(2.5) == Point3(4.5, 3, 4));
}

// Scenario: A ray intersects a sphere at two points
//  Given r ← ray(point(0, 0, -5), vector(0, 0, 1))
//  And s ← sphere()
//  When xs ← intersect(s, r)
//  Then xs.count = 2
//  And xs[0] = 4.0
//  And xs[1] = 6.0
TEST(RayTests, SphereIntersection) {
  Ray r(Point3(0, 0, -5), Vector3(0, 0, 1));
  Sphere s(0, Point3());
  auto xs = Intersection::intersect(r, s);

  EXPECT_TRUE(xs[0].t == 4.0);
  EXPECT_TRUE(xs[1].t == 6.0);
}

// Scenario: A ray intersects a sphere at a tangent
//  Given r ← ray(point(0, 1, -5), vector(0, 0, 1))
//  And s ← sphere()
//  When xs ← intersect(s, r)
//  Then xs.count = 2
//  And xs[0] = 5.0
//  And xs[1] = 5.0
TEST(RayTests, SphereIntersectionTangent) {
  Ray r(Point3(0, 1, -5), Vector3(0, 0, 1));
  Sphere s(0, Point3());
  auto xs = Intersection::intersect(r, s);

  EXPECT_TRUE(xs[0].t == 5.0);
  EXPECT_TRUE(xs[1].t == 5.0);
}

// Scenario: A ray misses a sphere
//  Given r ← ray(point(0, 2, -5), vector(0, 0, 1))
//  And s ← sphere()
//  When xs ← intersect(s, r)
//  Then xs.count = 0
TEST(RayTests, SphereMiss) {
  Ray r(Point3(0, 2, -5), Vector3(0, 0, 1));
  Sphere s(0, Point3());
  auto xs = Intersection::intersect(r, s);

  EXPECT_TRUE(xs.size() == 0);
}

// Scenario: A ray originates inside a sphere
//  Given r ← ray(point(0, 0, 0), vector(0, 0, 1))
//  And s ← sphere()
//  When xs ← intersect(s, r)
//  Then xs.count = 2
//  And xs[0] = -1.0
//  And xs[1] = 1.0
TEST(RayTests, InsideSphere) {
  Ray r(Point3(0, 0, 0), Vector3(0, 0, 1));
  Sphere s(0, Point3());
  auto xs = Intersection::intersect(r, s);

  EXPECT_TRUE(xs[0].t == -1.0);
  EXPECT_TRUE(xs[1].t == 1.0);
}

// Scenario: A sphere is behind a ray
//  Given r ← ray(point(0, 0, 5), vector(0, 0, 1))
//  And s ← sphere()
//  When xs ← intersect(s, r)
//  Then xs.count = 2
//  And xs[0] = -6.0
//  And xs[1] = -4.0
TEST(RayTests, InFrontOfSphere) {
  Ray r(Point3(0, 0, 5), Vector3(0, 0, 1));
  Sphere s(0, Point3());
  auto xs = Intersection::intersect(r, s);

  EXPECT_TRUE(xs[0].t == -6.0);
  EXPECT_TRUE(xs[1].t == -4.0);
}

//
// Scenario: An intersection encapsulates t and object
//  Given s ← sphere()
//  When i ← intersection(3.5, s)
//  Then i.t = 3.5
//  And i.object = s
TEST(RayTests, HitTarget) {
  Sphere s(0, Point3());
  auto i = Intersection(3.5, s);

  EXPECT_TRUE(i.shape == s);
  EXPECT_TRUE(i.t == 3.5);
}

// Scenario: Aggregating intersections
//  Given s ← sphere()
//  And i1 ← intersection(1, s)
//  And i2 ← intersection(2, s)
//  When xs ← intersections(i1, i2)
//  Then xs.count = 2
//  And xs[0].t = 1
//  And xs[1].t = 2
TEST(RayTests, AggregatingIntersections) {
  Sphere s(0, Point3());
  auto i1 = Intersection(1, s);
  auto i2 = Intersection(2, s);

  std::vector<Intersection> xs = Intersection::intersections({i1, i2});

  EXPECT_TRUE(xs.size() == 2);
  EXPECT_TRUE(xs[0].t == 1);
  EXPECT_TRUE(xs[1].t == 2);
}

// Scenario: Intersect sets the object on the intersection
//  Given r ← ray(point(0, 0, -5), vector(0, 0, 1))
//  And s ← sphere()
//  When xs ← intersect(r)
//  Then xs.count = 2
//  And xs[0].object = s
//  And xs[1].object = s
TEST(RayTests, IntersectSets) {
  Ray r(Point3(0, 0, 5), Vector3(0, 0, 1));
  Sphere s(0, Point3());
  auto xs = Intersection::intersect(r, s);

  EXPECT_TRUE(xs.size() == 2);
  EXPECT_TRUE(xs[0].shape == s);
  EXPECT_TRUE(xs[1].shape == s);
}

// Scenario: The hit, when all intersections have positive t
//  Given s ← sphere()
//  And i1 ← intersection(1, s)
//  And i2 ← intersection(2, s)
//  And xs ← intersections(i2, i1)
//  When i ← hit(xs)
//  Then i = i1
TEST(RayTests, PositiveTValueIntersections) {
  Sphere s(0);
  auto i1 = Intersection(1, s);
  auto i2 = Intersection(2, s);

  std::vector<Intersection> xs = Intersection::intersections({i1, i2});

  Intersection* iHit = Intersection::hit(xs);

  EXPECT_TRUE(*iHit == i1);
}
// Scenario : The hit, when some intersections have negative t
//  Given s ← sphere()
//  And i1 ← intersection(-1, s)
//  And i2 ← intersection(1, s)
//  And xs ← intersections(i2, i1)
//  When i ← hit(xs)
//  Then i = i2
TEST(RayTests, MixedTValueIntersections) {
  Sphere s(0);
  auto i1 = Intersection(-1, s);
  auto i2 = Intersection(1, s);

  std::vector<Intersection> xs = Intersection::intersections({i2, i1});

  Intersection* iHit = Intersection::hit(xs);

  EXPECT_TRUE(*iHit == i2);
}
// Scenario : The hit, when all intersections have negative t
//  Given s ← sphere()
//  And i1 ← intersection(-2, s)
//  And i2 ← intersection(-1, s)
//  And xs ← intersections(i2, i1)
//  When i ← hit(xs)
//  Then i is nothing
TEST(RayTests, NegativeTValueIntersections) {
  Sphere s(0);
  auto i1 = Intersection(-2, s);
  auto i2 = Intersection(-1, s);

  std::vector<Intersection> xs = Intersection::intersections({i2, i1});

  Intersection* iHit = Intersection::hit(xs);

  EXPECT_TRUE(iHit == nullptr);
}
// Scenario: The hit is always the lowest nonnegative intersection
//  Given s ← sphere()
//  And i1 ← intersection(5, s)
//  And i2 ← intersection(7, s)
//  And i3 ← intersection(-3, s)
//  And i4 ← intersection(2, s)
//  And xs ← intersections(i1, i2, i3, i4)
//  When i ← hit(xs)
//  Then i = i4
TEST(RayTests, LowestPositiveTValueIntersections) {
  Sphere s(0);
  auto i1 = Intersection(5, s);
  auto i2 = Intersection(7, s);
  auto i3 = Intersection(-3, s);
  auto i4 = Intersection(2, s);

  std::vector<Intersection> xs = Intersection::intersections({i1, i2, i3, i4});

  IntersectionPtr iHit = Intersection::hit(xs);

  EXPECT_TRUE(*iHit == i4);
}

// Scenario: Translating a ray
//  Given r ← ray(point(1, 2, 3), vector(0, 1, 0))
//  And m ← translation(3, 4, 5)
//  When r2 ← transform(r, m)
//  Then r2.origin = point(4, 6, 8)
//  And r2.direction = vector(0, 1, 0)
TEST(RayTests, TranslateRay) {
  Ray r(Point3(1, 2, 3), Vector3(0, 1, 0));
  // TODO how do I simplify this to not declare template
  Matrix4x4<double> m = Matrix4x4<double>::translation(3, 4, 5);

  Ray r2 = m * r;
  EXPECT_TRUE(r2.origin == Point3(4, 6, 8));
  EXPECT_TRUE(r2.direction == Vector3(0, 1, 0));
}

// Scenario : Scaling a ray
//  Given r ← ray(point(1, 2, 3), vector(0, 1, 0))
//  And m ← scaling(2, 3, 4)
//  When r2 ← transform(r, m)
//  Then r2.origin = point(2, 6, 12)
//  And r2.direction = vector(0, 3, 0)
TEST(RayTests, ScaleRay) {
  Ray r(Point3(1, 2, 3), Vector3(0, 1, 0));

  Matrix4x4<double> m = Matrix4x4<double>::scale(2, 3, 4);

  Ray r2 = m * r;
  EXPECT_TRUE(r2.origin == Point3(2, 6, 12));
  EXPECT_TRUE(r2.direction == Vector3(0, 3, 0));
}

// Scenario: A sphere's default transformation
//  Given s ← sphere()
//  Then s.transform = identity_matrix
TEST(RayTests, SphereDefaultTransform) {
  Sphere s(0);

  EXPECT_TRUE(s.transform == Matrix4x4<double>::identity());
}

// Scenario : Changing a sphere's transformation
//  Given s ← sphere()
//  And t ← translation(2, 3, 4)
//  When set_transform(s, t)
//  Then s.transform = t
TEST(RayTests, SetSphereTransform) {
  Sphere s(0);
  Matrix4x4<double> m = Matrix4x4<double>::translation(2, 3, 4);
  s.SetTransform(m);

  EXPECT_TRUE(s.transform == m);
}

// Scenario: Intersecting a scaled sphere with a ray
//  Given r ← ray(point(0, 0, -5), vector(0, 0, 1))
//  And s ← sphere()
//  When set_transform(s, scaling(2, 2, 2))
//  And xs ← intersect(s, r)
//  Then xs.count = 2
//  And xs[0].t = 3
//  And xs[1].t = 7
TEST(RayTests, RayIntersectsScaledSphere) {
  Ray r(Point3(0, 0, -5), Vector3(0, 0, 1));
  Sphere s(0);

  s.SetTransform(Matrix4x4<double>::scale(2, 2, 2));

  auto xs = Intersection::intersect(r, s);

  EXPECT_TRUE(xs.size() == 2);
  EXPECT_TRUE(xs[0].t == 3);
  EXPECT_TRUE(xs[1].t == 7);
} 
// Scenario: Intersecting a translated sphere with a ray
//  Given r ← ray(point(0, 0, -5), vector(0, 0, 1))
//  And s ← sphere()
//  When set_transform(s, translation(5, 0, 0))
//  And xs ← intersect(s, r)
//  Then xs.count = 0
TEST(RayTests, RayIntersectsTranslatedSphere) {
  Ray r(Point3(0, 0, -5), Vector3(0, 0, 1));
  Sphere s(0);

  s.SetTransform(Matrix4x4<double>::scale(2, 2, 2));

  auto xs = Intersection::intersect(r, s);

  EXPECT_TRUE(xs.size() == 2);
  EXPECT_TRUE(xs[0].t == 3);
  EXPECT_TRUE(xs[1].t == 7);
}