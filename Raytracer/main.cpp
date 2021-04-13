// RayTracerChallenge.cpp : Defines the entry point for the console application.

#include "ClockMain.h"
#include "MissleMain.h"
#include "SilhouetteMain.h"
#include "pch.h"

int main() {
  // MissleMain::main();


  //jdRay::ClockMain cm;
  //cm.drawClock();

  Silhouette::SilhouetteMain sm;
  sm.raycastSphere();

  return 0;
}
