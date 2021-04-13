#include "Ray.h"
#include "pch.h"

using namespace jdRay;

Point3 Ray::position(double time) {
  return origin + direction * time;
}
