#pragma once
#include "Math.h"

class Camera {
public:
	Camera(){
		pos = Vector3f(0.0, 0.0, 0.0);
		target = Vector3f(0.0, 0.0, -1.0);
		up = Vector3f(0.0, 1.0, 0.0);
		fovY = 45.0;
		aspect = 1.6;
		nearDis = 0.01;
		farDis = 100.0;
	};
	Vector3f pos;
	Vector3f target;
	Vector3f up;
	double fovY;
	double aspect;
	double nearDis;
	double farDis;
};