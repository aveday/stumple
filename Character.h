#ifndef CHARACTER_H
#define CHARACTER_H

#include <Box2D/Box2D.h>
#include "World.h"
#include "Sprite.h"

class Character {
	public:
		Character(World*, Spritesheet*);
        Entity *head, *foot[2], *hand[2];
};

#endif
