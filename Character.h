#ifndef CHARACTER_H
#define CHARACTER_H

#include <Box2D/Box2D.h>
#include "Sprite.h"

class World;
class Entity;

class Character {
	public:
		Character(World *w, Spritesheet *s);
        World *world;
        Entity *head, *foot[2], *hand[2];
        void Update(int);
};

#endif
