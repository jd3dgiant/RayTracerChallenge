#include "ClockMain.h"
#include "Matrix.h"
#include "pch.h"

using namespace jdRay;
void ClockMain::drawClock() {
  drawHourDots();
}

void ClockMain::drawHourDots() {
  Matrix4x4<double> rotation = Matrix4x4<double>::rotateZ(
      utils::PI / 6); // only diving by 6 and not 12 as a full 360 spin is 2 * pi

  Point3 clockDrawPoint = centerPoint - clockHandVector;
  Vector3 currentVectorRot = clockHandVector;

  // drawing center and starting 12 o clock pixel as its position is already defined
  clockCanvas.write_pixel(centerPoint.x(), centerPoint.y(), dotColor);
  clockCanvas.write_pixel(clockDrawPoint.x(), clockDrawPoint.y(), dotColor);

  // looping to 1 o clock to 11 o clock
  for (unsigned i = 0; i < 11; ++i) {
    currentVectorRot = rotation * currentVectorRot;
    clockDrawPoint = centerPoint - currentVectorRot;
    clockCanvas.write_pixel(clockDrawPoint.x(), clockDrawPoint.y(), dotColor);
  }

  std::cout << "SAVING TO DISK" << std::endl;

  clockCanvas.saveToDisk("Clock.ppm");
}
