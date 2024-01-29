#include "../../include/Algorithm.h"

Matrix4x4 TranslationMat(const Vector3f& vec)
{
	Matrix4x4 mat = Matrix4x4::Identity();
	;	mat.set(0, 3, vec.x);
	mat.set(1, 3, vec.y);
	mat.set(2, 3, vec.z);
	return mat;
}

Matrix4x4 ScaleMat(const Vector3f& vec)
{
	Matrix4x4 mat = Matrix4x4::Identity();
	mat.set(0, 0, vec.x);
	mat.set(1, 1, vec.y);
	mat.set(2, 2, vec.z);
	return mat;
}

Matrix4x4 RotationMat(double angle, char axis)
{
	float radian = angle * (3.14159265 / 180.0);
	Matrix4x4 mat = Matrix4x4::Identity();
	if (axis == 'x') {
		mat.set(1, 1, cosf(radian));
		mat.set(1, 2, -sinf(radian));
		mat.set(2, 1, sinf(radian));
		mat.set(2, 2, cosf(radian));
	}
	else if (axis == 'y') {
		mat.set(0, 0, cosf(radian));
		mat.set(0, 2, sinf(radian));
		mat.set(2, 0, -sinf(radian));
		mat.set(2, 2, cos(radian));
	}
	else if (axis == 'z') {
		mat.set(0, 0, cosf(radian));
		mat.set(0, 1, -sinf(radian));
		mat.set(1, 0, sinf(radian));
		mat.set(1, 1, cosf(radian));
	}
	return mat;
}



Matrix4x4 worldToView(Vector3f& cameraPos, Vector3f& target, Vector3f& up) {

	Vector3f zAxis = (cameraPos - target).Normalize();
	Vector3f xAxis = Vector3f::Product(up, zAxis).Normalize();
	Vector3f yAxis = Vector3f::Product(zAxis, xAxis).Normalize();


	Matrix4x4 view = Matrix4x4();
	view.set(0, 0, xAxis.x);
	view.set(0, 1, xAxis.y);
	view.set(0, 2, xAxis.z);

	view.set(1, 0, yAxis.x);
	view.set(1, 1, yAxis.y);
	view.set(1, 2, yAxis.z);

	view.set(2, 0, zAxis.x);
	view.set(2, 1, zAxis.y);
	view.set(2, 2, zAxis.z);

	view.set(0, 3, -(xAxis.Dot(cameraPos)));
	view.set(1, 3, -(yAxis.Dot(cameraPos)));
	view.set(2, 3, -(zAxis.Dot(cameraPos)));
	//view.set(0, 3, -cameraPos.x);
	//view.set(1, 3, -cameraPos.y);
	//view.set(2, 3, -cameraPos.z);

	view.set(3, 3, 1);

	return view;
}


Matrix4x4 viewToClip_projection(double fovY, double aspect, double near, double far) {
	float radiusFov = fovY * 3.1415926 / 180.0;
	float tanHalfFovy = tanf(static_cast<float>(radiusFov * 0.5f));

	Matrix4x4 mat = Matrix4x4();
	mat.set(0, 0, 1.0 / (aspect * tanHalfFovy));
	mat.set(1, 1, 1.0 / (tanHalfFovy));
	mat.set(2, 2, -(far + near) / (far - near));
	mat.set(2, 3, -(2.0 * far * near) / (far - near));
	mat.set(3, 2, -1.0);
	return mat;
}

Matrix4x4  viewPort(unsigned int width, unsigned int height) {

	Matrix4x4 mat = Matrix4x4::Identity();
	// x' = w/2 + w * x / 2
	mat.set(0, 0, width / 2.0);
	mat.set(0, 3, width / 2.0);
	// y' = h / 2 - y*h / 2
	mat.set(1, 1, -(height / 2.0));
	mat.set(1, 3, height / 2.0);
	// z' = z, w' = w;
	return mat;
}