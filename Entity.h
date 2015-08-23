#ifndef ENTITY_H
#define ENTITY_H

#include <stdint.h>
#include <SDL2/SDL.h>
#include <Box2D/Box2D.h>

#include "Geometry.h"

class Entity {
	public:
		Entity(b2Body*, int);
		b2Body *body;
        int depth;
};

#endif
