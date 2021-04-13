#pragma once
#include "Canvas.h"
#include "Intersect.h"
#include "Ray.h"
using namespace jdRay;

namespace Silhouette {
class SilhouetteMain {
 public:
  SilhouetteMain() : silhouetteCanvas(CANVASDIMENSIONS, CANVASDIMENSIONS){};

  // takes in all current data to draw on a canvas the current clock data
  void raycastSphere();

 private:
  const int CANVASDIMENSIONS = 500;
  const float WALLSIZE = 15;

  Color hitColor = Color(1, 0, 0);
  Color misColor = Color(0, 0, 0);

  Canvas silhouetteCanvas;
};
} // namespace jdRay
