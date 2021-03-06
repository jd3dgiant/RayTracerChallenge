#include "MissleMain.h"
#include <iostream>
#include <string>
#include "Canvas.h"
#include "Tuples.h"
#include "pch.h"
using namespace jdRay;
struct Environment {
  Environment(Vector3 inGravity, Vector3 inWind) : gravity(inGravity), wind(inWind) {}
  Vector3 gravity;
  Vector3 wind;
};

struct Projectile {
  Projectile(Point3 inStartPos, Vector3 inVelocity) : position(inStartPos), velocity(inVelocity) {}

  Point3 position;
  Vector3 velocity;
};

void tick(Environment& env, Projectile& missle) {
  missle.position = missle.position + missle.velocity;
  missle.velocity = missle.velocity + env.gravity + env.wind;
}

void MissleMain::main() {
  Canvas c(900, 550);
  Color drawColor(.75, .25, .25);

  Projectile missle(Point3(0, 1, 0), Vector3(1, 1.8, 0).normalize() * 11.25);
  Environment env(Vector3(0, -0.1, 0), Vector3(-.01, 0, 0));

  int tickCount = 0;
  while (missle.position.y() > 0.0) {
    tick(env, missle);
    tickCount++;

    int xPos = missle.position.x();
    int yPos = c._height - missle.position.y();

    c.write_pixel(xPos, yPos, drawColor);
  }
  std::cout << "SAVING TO DISK" << std::endl;

  c.saveToDisk("Test.ppm");
}
