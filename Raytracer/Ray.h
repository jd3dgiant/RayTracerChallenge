#pragma once
///
/// handles casting any ray component logic for the raytracer
///
#include <array>
#include "Tuples.h"

namespace jdRay {

class Ray {
 public:
  Ray() = default;

  Ray(const Point3& _origin, const Vector3& _direction) : origin(_origin), direction(_direction){};

  Point3 position(double time);

  bool operator==(const Ray& rhs) const {
    return origin == rhs.origin && direction == rhs.direction;
  }

  bool operator!=(const Ray& rhs) const {
    return !operator==(rhs);
  }

  Point3 origin;
  Vector3 direction;
};
} // namespace jdRay
