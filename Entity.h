#ifndef ENTITY_H
#define ENTITY_H

#include <stdint.h>

#include "Geometry.h"
#include "Image.h"

class Entity {
    public:
        IVec2 coords;
		Image image;
        Entity(IVec2, Image);
		Move(IVec2 v);
};

#endif
