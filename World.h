#ifndef WORLD_H
#define WORLD_H

#include "Entity.h"

#define MAX_ENTITIES 1000

class World {
    public:
        Entity entities[MAX_ENTITIES];
        int entityCount;
        void Update(int dt);
};

#endif
