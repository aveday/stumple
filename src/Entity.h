#ifndef ENTITY_H
#define ENTITY_H

#include <map>
#include <list>
#include <memory>
#include <string>
#include <Box2D/Box2D.h>

class b2Body;
class World;
class Entity;

static const int PPM = 64;

typedef std::unique_ptr<Entity> Entity_up;
typedef std::list<std::unique_ptr<Entity>> Entity_upl;
typedef std::map<std::string,Entity*> Entity_pm;

// FIXME could probably get rid of entity and just use b2Body...
class Entity {
	public:
        Entity(World &w, const std::string&, b2Vec2 pos, int gid, int d);
        //Entity(const Entity&) = delete; // FIXME list requires copy constructor?
        void AngleTowards(b2Vec2 pos, float s);
        b2Vec2 GetPos();
		b2Body *body; // FIXME change to unique_ptr? b2d manages memory...
        int depth = 0;
        float targetAngle = 0; // FIXME make these private?
        float strength = 0;
};

#endif
