#ifndef WORLD_H
#define WORLD_H

#include <Box2D/Box2D.h>

#include "Control.h"

#define MAX_ENTITIES 1000
#define MAX_CHARACTERS 100
#define WORLD_SIZE 128

static const int32 velocityIterations = 6;
static const int32 positionIterations = 2;

class Character;
class Entity;
class Sprite;

class World : public b2World {
    public:
        Entity *entities[MAX_ENTITIES];
        Character *characters[MAX_CHARACTERS];
        int entityCount;
        int characterCount;
		b2Body *body;
        void Update(int);
        void AddTile(Sprite*, int, int);
        World(b2Vec2);
};

#endif
