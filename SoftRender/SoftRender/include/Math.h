#pragma once
#include <iostream>
#include <cassert>

class Vector2f
{
public:
	float x;
	float y;

	Vector2f();
	Vector2f(float x, float y);
	Vector2f(const Vector2f& vec);
	~Vector2f();

	Vector2f operator +(const Vector2f& vec);
	Vector2f operator -(const Vector2f& vec);
	Vector2f operator *(const Vector2f& vec);
	Vector2f operator /(const Vector2f& vec);

	Vector2f operator *(float k);
	Vector2f operator /(float k);

	Vector2f operator +();
	Vector2f operator -();

	float Dot(const Vector2f& v2);
	Vector2f Normalize();
	float Magnitude();

	static float Dot(const Vector2f& v1, const Vector2f& v2);

	void printVec();
	Vector2f lerp(Vector2f v2, double weight);

private:
};
class Vector3f
{
public:
	float x;
	float y;
	float z;

	Vector3f();
	Vector3f(float x, float y, float z);
	Vector3f(const Vector3f& vec);
	Vector3f(const Vector2f& vec, float z);
	~Vector3f();

	Vector3f operator +(const Vector3f& vec);
	Vector3f operator -(const Vector3f& vec);
	Vector3f operator *(const Vector3f& vec);
	Vector3f operator /(const Vector3f& vec);

	Vector3f operator *(float k);
	Vector3f operator /(float k);

	Vector3f operator +();
	Vector3f operator -();

	float Dot(const Vector3f& v2);
	Vector3f Product(const Vector3f& v2);
	float Magnitude();
	Vector3f Normalize();

	static float Dot(const Vector3f& v1, const Vector3f& v2);
	static Vector3f Product(const Vector3f& v1, const Vector3f& v2);

	void printVec();
	Vector3f lerp(Vector3f v2, double weight);

private:

};
class Vector4f
{
public:
	float x;
	float y;
	float z;
	float w;

	Vector4f();
	Vector4f(float x, float y, float z, float w);
	Vector4f(const Vector4f& vec);
	Vector4f(const Vector3f& vec, float w);
	~Vector4f();

	Vector4f operator +(const Vector4f& vec);
	Vector4f operator -(const Vector4f& vec);
	Vector4f operator *(const Vector4f& vec);
	Vector4f operator /(const Vector4f& vec);

	Vector4f operator *(float k);
	Vector4f operator /(float k);

	Vector4f operator +();
	Vector4f operator -();

	float Dot(const Vector4f& v2);
	float Magnitude();
	Vector4f Normalize();


	static float Dot(const Vector4f& v1, const Vector4f& v2);

	Vector4f lerp(Vector4f v2, double weight);
	void printVec();
private:

};
class Matrix4x4 {
public:
	float operator()(int i, int j) const;
	void set(int x, int y, float value);

	Matrix4x4();
	Matrix4x4(const Matrix4x4& mat);
	Matrix4x4(const float matValue[4][4]);
	~Matrix4x4();

	Matrix4x4 operator + (const Matrix4x4& m1);
	Matrix4x4 operator - (const Matrix4x4& m1);

	Matrix4x4 operator * (const Matrix4x4& m1);
	Vector4f operator * (const Vector4f& v1);
	Matrix4x4 operator * (const float n);

	Vector4f rowVector(int i);
	Vector4f colVector(int j);

	Matrix4x4 Transpose();
	static Matrix4x4 Identity();
	void printMat();

private:
	float element[4][4];
};