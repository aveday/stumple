#include <stdlib.h>
#include <stdio.h>

#include "World.h"
#include "Clock.h"
#include "Sprite.h"

World::World(b2Vec2 g):
		b2World(g) {
    entityCount = 0;
    characterCount = 0;
	b2BodyDef def;
	def.type = b2_staticBody;
	def.position.Set(0,0);
	body = CreateBody(&def);
}

void World::Update(int t) {
    for(int n = 0; n < characterCount; n++) {
        characters[n]->Update(t);
    }

    Step(SPF, velocityIterations, positionIterations);
    ClearForces();
}

void World::AddTile(Sprite *sprite, int x, int y) {
	// create a tile fixture with userdata pointing to sprite
	b2PolygonShape box;
	box.SetAsBox(0.5f, 0.5f, b2Vec2(x+0.5f, y+0.5f), 0.0f);
	b2Fixture *fixture = body->CreateFixture((b2Shape*)&box, 10);
	fixture->SetUserData(sprite);
}

