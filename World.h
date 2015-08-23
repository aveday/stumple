#ifndef WORLD_H
#define WORLD_H

#include <Box2D/Box2D.h>

#include "Entity.h"
#include "Sprite.h"

#define MAX_ENTITIES 1000
#define WORLD_SIZE 128

static const int32 velocityIterations = 6;
static const int32 positionIterations = 2;

class World : public b2World {
    public:
        Entity *entities[MAX_ENTITIES];
		b2Body *body;
        int entityCount;
        void Update(int);
        Entity *AddEntity(Sprite*, float, float, int, int);
        void AddTile(Sprite*, int, int);
        World(b2Vec2);
};

#endif
