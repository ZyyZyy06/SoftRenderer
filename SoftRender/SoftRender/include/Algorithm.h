#pragma once
#include "Math.h"

Matrix4x4 TranslationMat(const Vector3f& vec);

Matrix4x4 ScaleMat(const Vector3f& vec);

Matrix4x4 RotationMat(double angle, char axis);

Matrix4x4 worldToView(Vector3f& cameraPos, Vector3f& target, Vector3f& up);

Matrix4x4 viewToClip_projection(double fovY, double aspect, double near, double far);

Matrix4x4  viewPort(unsigned int width, unsigned int height);