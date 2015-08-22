#include <stdlib.h>
#include <stdio.h>

#include "World.h"
#include "Clock.h"

World::World(b2Vec2 g):
		b2World(g),
		entityCount(0) {
	b2BodyDef def;
	def.type = b2_staticBody;
	def.position.Set(0,0);
	body = CreateBody(&def);
}

void World::Update() {
    Step(SPF, velocityIterations, positionIterations);
    ClearForces();
}

Entity* World::AddEntity(Sprite *sprite, float x, float y) {
    if (entityCount == MAX_ENTITIES)
        exit(EXIT_FAILURE); // TODO error handle entity overflow
	
	b2BodyDef bDef;
	bDef.type = b2_dynamicBody;
	bDef.position.Set(x, y);

	b2Body *body = CreateBody(&bDef);
	entities[entityCount++] = new Entity(body);

	// TODO allow for multiple fixtures
	b2Fixture *fixture = body->CreateFixture(sprite->shape, 10);
	fixture->SetUserData(sprite);

	return new Entity(body);
}

void World::AddTile(Sprite *sprite, int x, int y) {
	// create a tile fixture with userdata pointing to sprite
	b2PolygonShape box;
	box.SetAsBox(0.5f, 0.5f, b2Vec2(x+0.5f, y+0.5f), 0.0f);
	b2Fixture *fixture = body->CreateFixture((b2Shape*)&box, 10);
	fixture->SetUserData(sprite);
}

