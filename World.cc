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

	for(int i = 0; i < WORLD_SIZE; i++)
		for(int j = 0; j < WORLD_SIZE; j++)
			tiles[i][j] = NULL;
}

void World::Update() {
    Step(SPF, velocityIterations, positionIterations);
    ClearForces();
}

Entity* World::AddEntity( SDL_Texture *texture, Rect *src, float x, float y) {
    if (entityCount == MAX_ENTITIES)
        exit(EXIT_FAILURE); // TODO error handle entity overflow
	
	b2BodyDef bDef;
	bDef.type = b2_dynamicBody;
	bDef.position.Set(x+0.5f, y+0.5f);

	b2Body *body = CreateBody(&bDef);
	entities[entityCount++] = new Entity(body);

	// TODO allow for multiple fixtures
	b2PolygonShape square;
	square.SetAsBox(0.5f, 0.5f);
	b2Fixture *fixture = body->CreateFixture((b2Shape*)&square, 10);

	Rect *dst = new Rect(-16, -16, 32, 32);
	Image *i = new Image(texture, src, dst, fixture);

	fixture->SetUserData(i);

	return new Entity(body);
}

void World::AddTile(SDL_Texture *t, Rect *src, int x, int y) {
	b2PolygonShape box;
	box.SetAsBox(0.5f, 0.5f, b2Vec2(x+0.5f, y+0.5f), 0.0f);

	b2Fixture *fixture = body->CreateFixture((b2Shape*)&box, 10);

	Rect *dst = new Rect(x*32, y*32, 32, 32);
	Image *i = new Image(t, src, dst, fixture); 
	fixture->SetUserData(i);

	tiles[x][y] = i;
}

