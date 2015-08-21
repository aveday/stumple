#ifndef WORLD_H
#define WORLD_H

#include <Box2D/Box2D.h>

#include "Entity.h"
#include "Sprite.h"

#define MAX_ENTITIES 1000
#define WORLD_SIZE 128

static const int32 velocityIterations = 6;
static const int32 positionIterations = 2;

class World : b2World {
    public:
        Entity *entities[MAX_ENTITIES];
		Image *tiles[WORLD_SIZE][WORLD_SIZE];
		b2Body *body;
        int entityCount;
        void Update();
        Entity *AddEntity( SDL_Texture*, Rect*, float, float);
        void AddTile(SDL_Texture*, Rect*, int, int);
        World(b2Vec2);
};

#endif
