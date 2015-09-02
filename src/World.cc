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
    characters.insert(characters.begin(), Character_up(c));
}

// Add an entity to the world
void World::Add(Entity *e) { // FIXME change to accept model and pos?
    Insert( *ownEntities.insert(ownEntities.begin(), Entity_sp(e)) );
}

void World::Insert(const Entity_sp &e) {
    auto pos = entities.begin();
    // FIXME there's probably a std method for this
    for(; pos != entities.end(); pos++)
        if( Entity_sp(*pos)->depth <= (*e).depth )
            break;
    entities.insert(pos, Entity_wp(e));
}

void World::Update(int t) {
    for(auto it = characters.begin(); it != characters.end(); it++)
        (*it)->Update(t);
    //      v dodgy hack
    Step(SPF/2, velocityIterations, positionIterations);

    ClearForces();
}

void World::Tile(const std::string &sid, int x, int y) {
	// create a tile fixture with userdata pointing to model
    Model &model = Model::cache[sid];
    double w2 = (double)model.srcs[0].w / PPM / 2;
    double h2 = (double)model.srcs[0].w / PPM / 2;
	b2PolygonShape box;
	box.SetAsBox(w2, h2, b2Vec2(x+0.5f, y+0.5f), 0.0f);//FIXME
	b2Fixture *fixture = body->CreateFixture((b2Shape*)&box, 10);
	fixture->SetUserData((void*)&model);
}

