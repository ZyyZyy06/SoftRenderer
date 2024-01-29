#include "../../include/Math.h"

float  Matrix4x4::operator()(int i, int j) const
{
	//assert(x >= 0 && x <= 3 && y >= 0 && y <= 3);
	return this->element[i][j];
}

Matrix4x4::Matrix4x4(const Matrix4x4& mat)
{
	for (int i = 0; i <= 3; i++) {
		for (int j = 0; j <= 3; j++) {
			element[i][j] = mat(i, j);
		}
	}
}

Matrix4x4::Matrix4x4() : element{ 0.0f } {}

Matrix4x4::Matrix4x4(const float matValue[4][4])
{
	for (int i = 0; i <= 3; i++) {
		for (int j = 0; j <= 3; j++) {
			element[i][j] = matValue[i][j];
		}
	}
}

Matrix4x4::~Matrix4x4() {}

Matrix4x4 Matrix4x4::operator+(const Matrix4x4& m1)
{
	Matrix4x4 mr = Matrix4x4();
	for (int i = 0; i <= 3; i++) {
		for (int j = 0; j <= 3; j++) {
			mr.set(i, j, this->operator()(i, j) + m1(i, j));
		}
	}
	return mr;
}

Matrix4x4 Matrix4x4::operator-(const Matrix4x4& m1)
{
	Matrix4x4 mr = Matrix4x4();
	for (int i = 0; i <= 3; i++) {
		for (int j = 0; j <= 3; j++) {
			mr.set(i, j, this->operator()(i, j) - m1(i, j));
		}
	}
	return mr;
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4& m1)
{
	Matrix4x4 mr = Matrix4x4();
	for (int i = 0; i <= 3; i++) {
		for (int j = 0; j <= 3; j++) {
			float tempSum = 0.0f;
			for (int k = 0; k <= 3; k++) {
				tempSum += this->operator()(i, k) * m1(k, j);
			}
			mr.set(i, j, tempSum);
		}
	}
	return mr;
}

Vector4f Matrix4x4::operator*(const Vector4f& v1)
{
	Vector4f vr = Vector4f();
	vr.x = this->rowVector(0).Dot(v1);
	vr.y = this->rowVector(1).Dot(v1);
	vr.z = this->rowVector(2).Dot(v1);
	vr.w = this->rowVector(3).Dot(v1);
	return vr;
}

Matrix4x4 Matrix4x4::operator*(const float n)
{
	Matrix4x4 mr = Matrix4x4();
	for (int i = 0; i <= 3; i++) {
		for (int j = 0; j <= 3; j++) {
			mr.set(i, j, this->operator()(i, j) * n);
		}
	}
	return mr;
}

Vector4f Matrix4x4::rowVector(int i)
{
	assert(i <= 3 && i >= 0);
	return Vector4f(element[i][0], element[i][1], element[i][2], element[i][3]);
}

Vector4f Matrix4x4::colVector(int j)
{
	assert(j <= 3 && j >= 0);
	return Vector4f(element[0][j], element[1][j], element[2][j], element[3][j]);
}

Matrix4x4 Matrix4x4::Transpose()
{
	Matrix4x4 mr = Matrix4x4();
	for (int i = 0; i <= 3; i++) {
		for (int j = 0; j <= 3; j++) {
			mr.set(i, j, this->operator()(j, i));
		}
	}
	return mr;
}

Matrix4x4 Matrix4x4::Identity()
{
	Matrix4x4 mat = Matrix4x4();
	mat.set(0, 0, 1.0);
	mat.set(1, 1, 1.0);
	mat.set(2, 2, 1.0);
	mat.set(3, 3, 1.0);
	return mat;
}

void Matrix4x4::set(int x, int y, float value)
{
	assert(x >= 0 && x <= 3 && y >= 0 && y <= 3);
	element[x][y] = value;
}

void Matrix4x4::printMat()
{
	std::cout << "[";
	for (int i = 0; i <= 3; i++) {
		std::cout << "[";
		for (int j = 0; j <= 3; j++) {
			std::cout << this->operator()(i, j) << " ";
		}
		std::cout << "]" << std::endl;
	}
}