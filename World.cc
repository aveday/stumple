#include <stdlib.h>

#include "World.h"

World::World():
	entityCount(0) {
}

void World::Update(int dt) {
}

void World::AddEntity(Entity *e) {
	if (entityCount == MAX_ENTITIES)
		return; // TODO error handle entity overflow

	entities[entityCount++] = e;
	return;
}


