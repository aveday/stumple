#ifndef IMAGE_H
#define IMAGE_H

#include <stdint.h>

#include "Geometry.h"

class Image {
    public:
        Polygon shape;
        uint32_t color;
        double rotation;
        Image(Polygon, uint32_t, double);
};

#endif
