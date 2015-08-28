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

// Add a character to the world
void World::Add(Character *c) {
    characters.insert(characters.begin(), Character_sp(c));
}

// Add an entity to the world
void World::Add(Entity *e) {
    ownEntities.insert(ownEntities.begin(), Entity_sp(e));
    Insert(*ownEntities.begin());
}

void World::Insert(const Entity_sp &e) {
    entities.insert(entities.begin(), Entity_wp(e)); // TODO put depth code here
}

void World::Update(int t) {
    for(auto it = characters.begin(); it != characters.end(); it++)
        (*it)->Update(t);

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

