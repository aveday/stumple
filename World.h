#ifndef WORLD_H
#define WORLD_H

#include "Box2D/Box2D.h"

#include "Entity.h"
#include "Tile.h"

#define MAX_ENTITIES 1000
#define WORLD_SIZE 128

class World : b2World {
    public:
        Entity *entities[MAX_ENTITIES];
		Tile *tiles[WORLD_SIZE][WORLD_SIZE];
        int entityCount;
        void Update();
        void AddEntity(Entity*);
        void AddTile(Tile*, int, int);
        World(b2Vec2);
};

#endif
