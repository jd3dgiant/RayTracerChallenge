#pragma once
#include <cmath> 

namespace utils {
  float const EPSILON = 0.0001;
  //double const EPSILON = 0.0001; //TODO ask Derrick about this

  inline bool IsEqual(float lhs, float rhs) {
    return std::abs(lhs - rhs) < EPSILON;
  }

  //float const PI = 3.1415926535897932384;
  double const PI = 3.1415926535897932384;
};
