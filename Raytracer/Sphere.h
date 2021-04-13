#pragma once
#include "Matrix.h"
namespace jdRay {
class Sphere {
 public:
  Sphere() = default;
  Sphere(int _id)
      : ID(_id), transform(Matrix4x4<double>::identity()){}; // TODO can this be constexpr
  Sphere(int _id, Point3 _worldPos)
      : ID(_id),
        transform(Matrix4x4<double>::translation(_worldPos.x(), _worldPos.y(), _worldPos.z())){};

  bool operator==(const Sphere& rhs) const {
    return (transform == rhs.transform && ID == rhs.ID);
  }

  Point3 GetPosition() const {
    return Point3(transform.m4[3], transform.m4[7], transform.m4[11]);
  }

  void SetTransform(const Matrix4x4<double>& newTransform) {
    transform = newTransform;
  }

  Matrix4x4<double> transform;
  int ID;
};
} // namespace jdRay
