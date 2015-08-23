#ifndef WORLD_H
#define WORLD_H

#include <Box2D/Box2D.h>

#include "Entity.h"
#include "Character.h"
#include "Control.h"
#include "Sprite.h"

#define MAX_ENTITIES 1000
#define MAX_CHARACTERS 100
#define WORLD_SIZE 128

static const int32 velocityIterations = 6;
static const int32 positionIterations = 2;

class World : public b2World {
    public:
        Entity *entities[MAX_ENTITIES];
        Character *characters[MAX_CHARACTERS];
        int entityCount;
        int characterCount;
		b2Body *body;
        void Update(int);
        Entity *AddEntity(Sprite*, float, float, int, int);
        void AddTile(Sprite*, int, int);
        World(b2Vec2);
};

#endif
