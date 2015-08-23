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

void World::Update(int t) {
    Step(SPF, velocityIterations, positionIterations);
    ClearForces();
}

Entity* World::AddEntity(Sprite *sprite, float x, float y, int gid, int depth) {
    if (entityCount == MAX_ENTITIES)
        exit(EXIT_FAILURE); // TODO error handle entity overflow
	
	b2BodyDef bDef;
	bDef.type = b2_dynamicBody;
	bDef.position.Set(x, y);

	b2Body *body = CreateBody(&bDef);
    Entity *added = new Entity(body, depth);

    // insert the entities into the depth-sorted entity array
    entities[entityCount++] = added;
    if(depth > 0) {
        for(int n = 0; n < entityCount-1; n++) {
            if(entities[n]->depth < entities[entityCount-1]->depth) {
                Entity *swap = entities[n];
                entities[n] = entities[entityCount-1];
                entities[entityCount-1] = swap;
            }
        }
    }

	// TODO allow for multiple fixtures
    b2FixtureDef fDef;
    fDef.shape = sprite->shape;
    fDef.userData = sprite;
    fDef.density = 10;
    fDef.filter.groupIndex = -gid; //TODO change filtering to use masks
	body->CreateFixture(&fDef);

	return added;
}

void World::AddTile(Sprite *sprite, int x, int y) {
	// create a tile fixture with userdata pointing to sprite
	b2PolygonShape box;
	box.SetAsBox(0.5f, 0.5f, b2Vec2(x+0.5f, y+0.5f), 0.0f);
	b2Fixture *fixture = body->CreateFixture((b2Shape*)&box, 10);
	fixture->SetUserData(sprite);
}

