#pragma once
#include <cmath> 

class Tuple {
	public:
		Tuple() {}

		Tuple(float in0, float in1, float in2, float in3) {
			components[0] = in0;
			components[1] = in1;
			components[2] = in2;
			components[3] = in3;
		}

		float x() const { return components[0]; }
		float y() const { return components[1]; }
		float z() const { return components[2]; }
		float w() const { return components[3]; }
		float r() const { return components[0]; }
		float g() const { return components[1]; }
		float b() const { return components[2]; }
		float a() const { return components[3]; }

		bool IsEqual(float lhs, float rhs) const {
			return std::abs(lhs - rhs) < EPSILON;
		}

		bool IsVector3() const {
			return IsEqual(w(), 0.0f);
		}

		bool IsPoint3() const {
			return !IsVector3();
		}

		bool operator==(const Tuple &rhs) {
			return IsEqual(x(), rhs.x()) && IsEqual(y(), rhs.y()) && IsEqual(z(), rhs.z()) && IsEqual(w(), rhs.w());
		}

		bool operator!=(const Tuple &rhs) {
			return !operator==(rhs);
		}

		void operator=(const Tuple &rhs) {
			components[0] = rhs.x();
			components[1] = rhs.y();
			components[2] = rhs.z();
		}

		Tuple operator-() const {
			return Tuple(-x(), -y(), -z(), -w());
		}

		Tuple operator*(const float &rhs) const {
			return Tuple(x() * rhs, y() * rhs, z() * rhs, w() * rhs);
		}

		Tuple operator/(const float &rhs) const {
			return Tuple(x() / rhs, y() / rhs, z() / rhs, w() / rhs);
		}

		//constexpr float const TUPLESIZE = 4;

		float components[4];

	protected:
		float const EPSILON = 0.0001;
};

class Vector3 : public Tuple {
	public:
		Vector3(float in0, float in1, float in2) :
			Tuple(in0, in1, in2, 0.0) {}

		static Vector3 zero() {
			return Vector3(0.0, 0.0, 0.0);
		}

		Vector3 operator+(const Vector3 &rhs) const {
			return Vector3(x() + rhs.x(), y() + rhs.y(), z() + rhs.z());
		}

		Vector3 operator-(const Vector3 &rhs) const {
			return Vector3(x() - rhs.x(), y() - rhs.y(), z() - rhs.z());
		}

		float magnitude() const {
			float totalLength = 0;
			for (unsigned i = 0; i < 4; i++) { // come back and figure out how to compile the size
				totalLength += components[i] * components[i];
			}
			return sqrt(totalLength);
		}

		Vector3 normalize() const {
			float mag = magnitude();
			if (mag < EPSILON) {
				return zero();
			}
			return Vector3(x() / mag, y() / mag, z() / mag);
		}

		static float dotProduct(const Vector3 &firstV, const Vector3 &secondV) {
			return firstV.x() * secondV.x() + 
				firstV.y() * secondV.y() + 
				firstV.z() * secondV.z() + 
				firstV.w() * secondV.w(); 
		}

		static Vector3 crossProduct(const Vector3 &firstV, const Vector3 &secondV) {
			return Vector3(firstV.y() * secondV.z() - firstV.z() * secondV.y(),
				firstV.z() * secondV.x() - firstV.x() * secondV.z(),
				firstV.x() * secondV.y() - firstV.y() * secondV.x());
		}
};

class Point3 : public Tuple {
	public:
		Point3(float in0, float in1, float in2) :
			Tuple(in0, in1, in2, 1.0) {}

		Vector3 operator-(const Point3 &rhs) const {
			return Vector3(x() - rhs.x(), y() - rhs.y(), z() - rhs.z());
		}

		Point3 operator+(const Vector3 &rhs) const {
			return Point3(x() + rhs.x(), y() + rhs.y(), z() + rhs.z());
		}

		Point3 operator-(const Vector3 &rhs) const {
			return Point3(x() - rhs.x(), y() - rhs.y(), z() - rhs.z());
		}
};
