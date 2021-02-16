// RayTracerChallenge.cpp : Defines the entry point for the console application.
//

#include "pch.h"
#include <iostream>
#include <string> 
#include "Tuples.h"

struct environment {
	environment(Vector3 inGravity, Vector3 inWind) :
		gravity(inGravity), wind(inWind){}
		Vector3 gravity;
		Vector3 wind;
};

struct projectile {
	projectile(Point3 inStartPos, Vector3 inVelocity) :
		position(inStartPos), velocity(inVelocity) {}

	Point3 position;
	Vector3 velocity;
};

void tick(environment &env, projectile &missle) {
	missle.position = missle.position + missle.velocity;
	missle.velocity = missle.velocity + env.gravity + env.wind;
}

int main() {

	environment env(Vector3(0, -0.1, 0), Vector3(-.01, 0, 0));
	projectile missle(Point3(0, 1, 0), Vector3(1, 1, 0).normalize());

	int tickCount = 0;
	while (missle.position.y() > 0.0) {
		tick(env, missle);
		tickCount++;
		std::cout << "missle position: " << "x: " + std::to_string(missle.position.x()) +
			" y: " + std::to_string(missle.position.y()) +
			" z: " + std::to_string(missle.position.z()) << std::endl;
	}
	std::cout << "Total Tick Count: " + std::to_string(tickCount);
    return 0;
}
