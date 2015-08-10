#ifndef ENTITY_H
#define ENTITY_H

#include <stdlib.h>
#include <stdint.h>

#include "Geometry.h"

class Entity {
    public:
        uint32_t color;
        Vec2 coords;
        Polygon shape;
        int rotation;
};


#endif
