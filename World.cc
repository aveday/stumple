#include <stdlib.h>
#include <stdio.h>

#include "World.h"
#include "Clock.h"
#include "Model.h"
#include "Character.h"

World::World(b2Vec2 g):
		b2World(g) {
	b2BodyDef def;
	def.type = b2_staticBody;
	def.position.Set(0,0);
	body = CreateBody(&def);
}

// Add an entity to the world, returning a shared pointer
Entity_sp World::Add(Entity *e) {
    Entity_sp sp(e);
    entities.insert(entities.begin(), sp);
    return sp;
}

void World::Update(int t) {
    for(int n = 0; n < Character::GetCount(); n++) {
        characters[n]->Update(t);
    }

    Step(SPF, velocityIterations, positionIterations);
    ClearForces();
}

void World::AddTile(const std::string sid, int x, int y) {
	// create a tile fixture with userdata pointing to model
    Model &model = Model::cache[sid];
	b2PolygonShape box;
	box.SetAsBox(0.5f, 0.5f, b2Vec2(x+0.5f, y+0.5f), 0.0f);
	b2Fixture *fixture = body->CreateFixture((b2Shape*)&box, 10);
	fixture->SetUserData((void*)&model);
}

