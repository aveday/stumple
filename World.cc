#include <stdlib.h>
#include <stdio.h>

#include "World.h"

World::World():
    entityCount(0) {
}

void World::Update() {
    for(int i = 0; i < entityCount; i++) {
        Entity *e = entities[i];
    }
}

void World::AddEntity(Entity *e) {
    if (entityCount == MAX_ENTITIES)
        exit(EXIT_FAILURE); // TODO error handle entity overflow

    entities[entityCount++] = e;
    return;
}


