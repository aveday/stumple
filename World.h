#ifndef WORLD_H
#define WORLD_H

#include "Entity.h"
#include "Tile.h"

#define MAX_ENTITIES 1000
#define WORLD_SIZE 128

class World {
    public:
        Entity *entities[MAX_ENTITIES];
		Tile *tiles[WORLD_SIZE][WORLD_SIZE];
        int entityCount;
        void Update();
        void AddEntity(Entity*);
        void AddTile(Tile*, int, int);
        World();
};

#endif
