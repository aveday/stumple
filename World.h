#ifndef WORLD_H
#define WORLD_H

#include <list>
#include <Box2D/Box2D.h>

#include "Control.h"

#define MAX_ENTITIES 1000
#define MAX_CHARACTERS 100
#define WORLD_SIZE 128

static const int32 velocityIterations = 6;
static const int32 positionIterations = 2;

class Character;
class Entity;
class Sprite;

class World : public b2World {
    public:
        std::list<Entity> entities;
        Character *characters[MAX_CHARACTERS];
		b2Body *body;
        void Update(int);
        void AddTile(const Sprite&, int, int);
        World(b2Vec2);
        void Add(Entity *e);
};

#endif
