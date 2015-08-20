#include <stdlib.h>
#include <stdio.h>

#include "World.h"

World::World():
		entityCount(0) {
	for(int i = 0; i < WORLD_SIZE; i++)
		for(int j = 0; j < WORLD_SIZE; j++)
			tiles[i][j] = NULL;
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
}

void World::AddTile(Tile *t, int x, int y) {
	tiles[x][y] = t;
}
