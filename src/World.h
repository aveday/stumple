#ifndef WORLD_H
#define WORLD_H

#include <Box2D/Box2D.h>

#include "Entity.h"
#include "Character.h"

static const int32 velocityIterations = 6;
static const int32 positionIterations = 2;

class World : public b2World {
    public:
        Entity_wpl entities; 
        Character_spl characters; // make upl
		b2Body *body;
        void Update(int);
        void Tile(const std::string &sid, int, int);
        explicit World(b2Vec2);
        void Insert(const Entity_sp &e);
        void Add(Entity *e);
        void Add(Character *c);
    private:
        Entity_spl ownEntities; //FIXME move/rename? // make upl
};

#endif
