#ifndef WORLD_H
#define WORLD_H

#include <Box2D/Box2D.h>

#include "Entity.h"

#define MAX_ENTITIES 1000
#define MAX_CHARACTERS 100
#define WORLD_SIZE 128

static const int32 velocityIterations = 6;
static const int32 positionIterations = 2;

class Character;

class World : public b2World {
    public:
        Entity_wpl entities;
        Character *characters[MAX_CHARACTERS];
		b2Body *body;
        void Update(int);
        void AddTile(const std::string sid, int, int);
        World(b2Vec2);
        void Insert(const Entity_sp &e);
        void Add(Entity *e); // TODO privatise
    private:
        Entity_spl ownEntities; //FIXME move to main?
};

#endif
