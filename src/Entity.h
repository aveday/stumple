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

class Entity {
	public:
        Entity(World &w, const std::string&, b2Vec2 pos, int gid, int d);
        Entity(const Entity&) = delete;
        void AngleTowards(b2Vec2 pos, float s);
        b2Vec2 GetPos();
		b2Body *body;
        int depth = 0;
        // FIXME make these private?
        float targetAngle = 0;
        float strength = 0;
};

#endif
