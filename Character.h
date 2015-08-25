#ifndef CHARACTER_H
#define CHARACTER_H

#include <memory>
#include <Box2D/Box2D.h>
#include "Sprite.h"

class World;
class Entity;

class Character {
	public:
		Character(World &w, Spritesheet *s);
        World *world;
        std::unique_ptr<Entity> head, torso,
            foot[2], hand[2], thigh[2], calf[2], upper[2], fore[2];
        //Entity *head, *foot[2], *hand[2];
        void Update(int);
};

#endif
