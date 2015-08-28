#ifndef ENTITY_H
#define ENTITY_H

#include <list>
#include <memory>
#include <stdint.h>
#include <SDL2/SDL.h>
#include <Box2D/Box2D.h>

class World;
class Entity;

#include "Model.h"

typedef std::shared_ptr<Entity> Entity_sp;
typedef std::list<std::shared_ptr<Entity>> Entity_spl;

class Entity {
	public:
        Entity(World &w, const std::string, float x, float y, int gid, int d);
        //Entity(const Entity&) = delete; // FIXME list requires copy constructor?
		b2Body *body;
        int depth;
        static int GetCount() { return count; }
    private:
        static int count;
};

#endif
