#include "SilhouetteMain.h"
#include "pch.h"

using namespace jdRay;

void Silhouette::SilhouetteMain::raycastSphere() {
  Sphere s(0);

  s.SetTransform(Matrix4x4<double>::rotateZ(utils::PI / 4)*Matrix4x4<double>::scale(.2, .5, 1));

  Point3 rayOrigin(0, 0, -5);

  int canvasHeight = silhouetteCanvas._height;
  int canvasWidth = silhouetteCanvas._width;

  int halfH = WALLSIZE / 2;
  int halfW = WALLSIZE / 2;

  float pixelStepY = WALLSIZE / canvasHeight;
  float pixelStepX = WALLSIZE / canvasWidth;

  float xOffset;
  float yOffset;
  for (unsigned y = 0; y < canvasHeight; y++) {
    yOffset = halfH - pixelStepY * y;
    for (unsigned x = 0; x < canvasWidth; x++) {
      xOffset = -halfW + pixelStepX * x;
      Point3 test(xOffset, yOffset, WALLSIZE);
      Ray ray(rayOrigin, Vector3(test - rayOrigin).normalize());

      auto xs = Intersection::intersect(ray, s);
      IntersectionPtr hit = Intersection::hit(xs);
      if (hit != nullptr) {
        silhouetteCanvas.write_pixel(x, y, hitColor);
      }
    }
  }

  std::cout << "SAVING TO DISK" << std::endl;

  silhouetteCanvas.saveToDisk("SilhouetteCanvas.ppm");
}
