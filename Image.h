#ifndef IMAGE_H
#define IMAGE_H

#include <stdint.h>

#include "Geometry.h"

class Image {
	public:
		Vec2 position;
        Polygon shape;
        uint32_t color;
        double rotation;
		Image(Vec2, Polygon, uint32_t, double);
};

#endif
