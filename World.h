#ifndef WORLD_H
#define WORLD_H

#include "Entity.h"

#define MAX_ENTITIES 1000

class World {
    public:
        Grid grid;
        Entity *entities[MAX_ENTITIES];
        int entityCount;
        void Update();
        void AddEntity(Entity *e);
        World(Grid);
};

#endif
