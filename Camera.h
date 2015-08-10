#ifndef CAMERA_H
#define CAMERA_H

#include "Geometry.h"

struct Camera {
	Vec2 offset;
	double zoom;
	Camera();
};

#endif
