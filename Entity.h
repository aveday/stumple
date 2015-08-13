#ifndef ENTITY_H
#define ENTITY_H

#include <stdint.h>

#include "Geometry.h"

class Entity {
    public:
        Vec2 position;
        Polygon shape;
        uint32_t color;
        double rotation;
        Entity(Vec2, Polygon, uint32_t);
};

#endif
