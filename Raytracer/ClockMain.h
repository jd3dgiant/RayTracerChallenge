#pragma once
#include "Canvas.h"
namespace jdRay {
class ClockMain {
 public:
  ClockMain() : clockCanvas(CANVASDIMENSIONS, CANVASDIMENSIONS) {
    if (CANVASDIMENSIONS > 2) {
      float centerPos = float((CANVASDIMENSIONS / 2) - 1);
      centerPoint = Point3(centerPos, centerPos, 0);
    }
  };

  // takes in all current data to draw on a canvas the current clock data
  void drawClock();

 private:
  void drawHourDots();

  const int CANVASDIMENSIONS = 300;

  Point3 centerPoint = Point3(0, 0, 0);
  Vector3 clockHandVector = Vector3(0, 75, 0);

  Color dotColor = Color(1, 1, 1);

  Canvas clockCanvas;
};
} // namespace jdRay
