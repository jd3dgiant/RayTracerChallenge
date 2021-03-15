#pragma once
#include <cmath> 

namespace utils {
  float const EPSILON = 0.0001;

  inline bool IsEqual(float lhs, float rhs) {
    return std::abs(lhs - rhs) < EPSILON;
  }
};
