#include "Intersect.h"
#include "pch.h"
using namespace jdRay;

std::vector<Intersection> Intersection::intersect(const Ray& ray, const Sphere& sphere) {
  //# the vector from the sphere's center, to the ray origin
  //  # remember: the sphere is centered at the world origin
  //  sphere_to_ray ← ray.origin - point(0, 0, 0)
  //  a ← dot(ray.direction, ray.direction)
  //  b ← 2 * dot(ray.direction, sphere_to_ray)
  //  c ← dot(sphere_to_ray, sphere_to_ray) - 1
  //  discriminant ← b² - 4 * a * c
  Ray invertedR = sphere.transform.inverse() * ray;

  Vector3 rayOriginToSphereOrigin = invertedR.origin - sphere.GetPosition();
  float detAComponent = Vector3::dotProduct(invertedR.direction, invertedR.direction);
  float detBComponent = 2.0 * Vector3::dotProduct(invertedR.direction, rayOriginToSphereOrigin);
  float detCComponent = Vector3::dotProduct(rayOriginToSphereOrigin, rayOriginToSphereOrigin) - 1;

  float discriminant = detBComponent * detBComponent - 4 * detAComponent * detCComponent;
  if (discriminant < 0) {
    return {};
  }
  else {
    float t1 = (-detBComponent - std::sqrt(discriminant)) / (2 * detAComponent);
    float t2 = (-detBComponent + std::sqrt(discriminant)) / (2 * detAComponent);

    Intersection i1(t1, sphere);
    Intersection i2(t2, sphere);
    return Intersection::intersections({ i1, i2 });
  }
}

// TODO why cant this be a shared ptr or unique
// also since this pointer return is to a vector I do not have to delete the pointer because the
// vector will handle that when its out of scope?
IntersectionPtr Intersection::hit(std::vector<Intersection>& intersections) {
  double lowestIntersection = 0.0;
  IntersectionPtr returnIntersection = nullptr;
  for (unsigned i = 0; i < intersections.size(); ++i) {
    if (intersections[i].t > 0.0) { // ignore negative intersection points
      if (!returnIntersection) {
        returnIntersection = &intersections[i];
        lowestIntersection = intersections[i].t;
      } else if (lowestIntersection > intersections[i].t) {
        returnIntersection = &intersections[i];
        lowestIntersection = intersections[i].t;
      }
    }
  }
  return returnIntersection;
}
