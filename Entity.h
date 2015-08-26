#ifndef ENTITY_H
#define ENTITY_H

#include <stdint.h>
#include <SDL2/SDL.h>
#include <Box2D/Box2D.h>

#include "World.h"
#include "Sprite.h"

class Entity {
	public:
        Entity(World&, Sprite&, float x, float y, int gid, int depth);
        Entity(const Entity&) = delete;
		b2Body *body;
        int depth;
        static int GetCount() { return count; }
    private:
        static int count;
};

#endif
