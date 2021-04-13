#pragma once
#include <initializer_list>
#include <vector>
#include "Ray.h"
#include "Sphere.h"
namespace jdRay {
typedef class Intersection* IntersectionPtr;

// stores intersection point and object of Ray
class Intersection {
 public:
  Intersection(double _t, Sphere _obj) : t(_t), shape(_obj){};

  bool operator==(const Intersection& rhs) const {
    return utils::IsEqual(t, rhs.t) && shape == rhs.shape;
  }
  static std::vector<Intersection> intersect(const Ray& ray, const Sphere& sphere);

  static IntersectionPtr hit(std::vector<Intersection>& intersections);

  static std::vector<Intersection> intersections(const std::initializer_list<Intersection>& list) {
    std::vector<Intersection> intersectionList;
    for (auto elem : list) {
      intersectionList.push_back(elem);
    }
    return intersectionList;
  }

  // member variables
  double t;
  Sphere shape;
};

} // namespace jdRay
