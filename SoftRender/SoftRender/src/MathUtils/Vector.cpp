#include <cassert>
#include <cmath>
#include <iostream>
#include "../../include/Math.h"

Vector2f::Vector2f() :x(0.f), y(0.f) {}

Vector2f::Vector2f(float x, float y) :x(x), y(y) {}

Vector2f::Vector2f(const Vector2f& vec) : x(vec.x), y(vec.y) {}

Vector2f::~Vector2f() {}

Vector2f Vector2f::operator+(const Vector2f& vec)
{
	return Vector2f(this->x + vec.x, this->y + vec.y);
}

Vector2f Vector2f::operator-(const Vector2f& vec)
{
	return Vector2f(this->x - vec.x, this->y - vec.y);
}

Vector2f Vector2f::operator*(const Vector2f& vec)
{
	return Vector2f(this->x * vec.x, this->y * vec.y);
}

Vector2f Vector2f::operator/(const Vector2f& vec)
{
	assert(vec.x != 0 && vec.y != 0);
	return Vector2f(this->x / vec.x, this->y / vec.y);

}

Vector2f Vector2f::operator*(float k)
{
	return Vector2f(this->x * k, this->y * k);
}

Vector2f Vector2f::operator/(float k)
{
	assert(k != 0.0f);
	return Vector2f(this->x / k, this->y / k);
}

Vector2f Vector2f::operator+()
{
	return *this;
}

Vector2f Vector2f::operator-()
{
	return Vector2f(-this->x, -this->y);
}

float Vector2f::Dot(const Vector2f& v2)
{
	Vector2f& v1 = *this;
	return v1.x * v2.x + v1.y * v2.y;
}

Vector2f Vector2f::Normalize()
{
	float length = Magnitude();
	if (length != 0) {
		return Vector2f(*this / length);
	}
	return Vector2f(0.0f, 0.0f);
}

float Vector2f::Magnitude()
{
	return sqrt(this->x * this->x + this->y * this->y);
}

float Vector2f::Dot(const Vector2f& v1, const Vector2f& v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

void Vector2f::printVec() {
	std::cout << "(x:" << x << " y:" << y << ")" << std::endl;
}


Vector2f Vector2f::lerp(Vector2f v2, double weight) {
	return Vector2f(
		this->x * (1.0 - weight) + weight * v2.x,
		this->y * (1.0 - weight) + weight * v2.y);
}



Vector3f::Vector3f() :x(0.0f), y(0.0f), z(0.0f) {}

Vector3f::Vector3f(float x, float y, float z) :x(x), y(y), z(z) {}

Vector3f::Vector3f(const Vector3f& vec) : x(vec.x), y(vec.y), z(vec.z) {}

Vector3f::Vector3f(const Vector2f& vec, float z) : x(vec.x), y(vec.y), z(z) {}

Vector3f::~Vector3f() {}


Vector3f Vector3f::operator+(const Vector3f& vec)
{
	return Vector3f(this->x + vec.x, this->y + vec.y, this->z + vec.z);
}

Vector3f Vector3f::operator-(const Vector3f& vec)
{
	return Vector3f(this->x - vec.x, this->y - vec.y, this->z - vec.z);
}

Vector3f Vector3f::operator*(const Vector3f& vec)
{
	return Vector3f(this->x * vec.x, this->y * vec.y, this->z * vec.z);
}

Vector3f Vector3f::operator/(const Vector3f& vec)
{
	assert(vec.x != 0.0 && vec.y != 0.0 && vec.z != 0.0);
	return Vector3f(this->x / vec.x, this->y / vec.y, this->z / vec.z);
}

Vector3f Vector3f::operator*(float k)
{
	return Vector3f(this->x * k, this->y * k, this->z * k);
}

Vector3f Vector3f::operator/(float k)
{
	assert(k != 0);
	return Vector3f(this->x / k, this->y / k, this->z / k);
}

Vector3f Vector3f::operator+()
{
	return *this;
}

Vector3f Vector3f::operator-()
{
	return Vector3f(-this->x, -this->y, -this->z);
}

float Vector3f::Dot(const Vector3f& v2)
{
	Vector3f& v1 = *this;
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

Vector3f Vector3f::Product(const Vector3f& v2)
{
	Vector3f& v1 = *this;
	float xTerm = v1.y * v2.z - v1.z * v2.y;
	float yTerm = v2.x * v1.z - v1.x * v2.z;
	float zTerm = v1.x * v2.y - v2.x * v1.y;
	return Vector3f(xTerm, yTerm, zTerm);
}

float Vector3f::Magnitude()
{
	return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}

Vector3f Vector3f::Normalize()
{
	float length = Magnitude();
	if (length != 0.0f) {
		return Vector3f(*this / length);
	}
	return Vector3f(0.0f, 0.0f, 0.0f);
}

float Vector3f::Dot(const Vector3f& v1, const Vector3f& v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

Vector3f Vector3f::Product(const Vector3f& v1, const Vector3f& v2)
{
	float xTerm = v1.y * v2.z - v1.z * v2.y;
	float yTerm = v2.x * v1.z - v1.x * v2.z;
	float zTerm = v1.x * v2.y - v2.x * v1.y;
	return Vector3f(xTerm, yTerm, zTerm);
}


void Vector3f::printVec() {
	std::cout << "(x:" << x << " y:" << y << " z:" << z << ")" << std::endl;
}

Vector3f Vector3f::lerp(Vector3f v2, double weight) {
	return Vector3f(
		this->x * (1.0 - weight) + weight * v2.x,
		this->y * (1.0 - weight) + weight * v2.y,
		this->z * (1.0 - weight) + weight * v2.z
	);
}


Vector4f::Vector4f() :x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}

Vector4f::Vector4f(float x, float y, float z, float w) :x(x), y(y), z(z), w(w) {}

Vector4f::Vector4f(const Vector4f& vec) : x(vec.x), y(vec.y), z(vec.z), w(vec.w) {}

Vector4f::Vector4f(const Vector3f& vec, float w) : x(vec.x), y(vec.y), z(vec.z), w(w) {}

Vector4f::~Vector4f() {}

Vector4f Vector4f::operator+(const Vector4f& vec)
{
	return Vector4f(this->x + vec.x, this->y + vec.y, this->z + vec.z, this->w + vec.w);
}

Vector4f Vector4f::operator-(const Vector4f& vec)
{
	return Vector4f(this->x - vec.x, this->y - vec.y, this->z - vec.z, this->w - vec.w);
}

Vector4f Vector4f::operator*(const Vector4f& vec)
{
	return Vector4f(this->x * vec.x, this->y * vec.y, this->z * vec.z, this->w * vec.w);
}

Vector4f Vector4f::operator/(const Vector4f& vec)
{
	assert(vec.x != 0.0 && vec.y != 0.0 && vec.z != 0.0 && vec.w != 0.0);
	return Vector4f(this->x / vec.x, this->y / vec.y, this->z / vec.z, this->w / vec.w);
}

Vector4f Vector4f::operator*(float k)
{
	return Vector4f(this->x * k, this->y * k, this->z * k, this->w * k);
}

Vector4f Vector4f::operator/(float k)
{
	assert(k != 0);
	return Vector4f(this->x / k, this->y / k, this->z / k, this->w / k);
}

Vector4f Vector4f::operator+()
{
	return *this;
}

Vector4f Vector4f::operator-()
{
	return Vector4f(-this->x, -this->y, -this->z, -this->w);
}

float Vector4f::Dot(const Vector4f& v2)
{
	Vector4f& v1 = *this;
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w);
}

float Vector4f::Magnitude()
{
	return sqrt(this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w);
}

Vector4f Vector4f::Normalize()
{
	float length = Magnitude();
	if (length != 0.0f) {
		return Vector4f(*this / length);
	}
	return Vector4f(0.0f, 0.0f, 0.0f, 0.0f);
}


float Vector4f::Dot(const Vector4f& v1, const Vector4f& v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w);
}

void Vector4f::printVec() {
	std::cout << "(x:" << x << " y:" << y << " z:" << z << " w:" << w << ")" << std::endl;
}

Vector4f Vector4f::lerp(Vector4f v2, double weight) {
	return Vector4f(
		this->x * (1.0 - weight) + weight * v2.x,
		this->y * (1.0 - weight) + weight * v2.y,
		this->z * (1.0 - weight) + weight * v2.z,
		this->w * (1.0 - weight) + weight * v2.w
	);
}
