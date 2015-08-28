#ifndef ENTITY_H
#define ENTITY_H

#include <list>
#include <memory>

class b2Body;
class World;
class Entity;

typedef std::shared_ptr<Entity> Entity_sp;
typedef std::weak_ptr<Entity> Entity_wp;
typedef std::list<std::shared_ptr<Entity>> Entity_spl;
typedef std::list<std::weak_ptr<Entity>> Entity_wpl;

class Entity {
	public:
        Entity(World &w, const std::string, float x, float y, int gid, int d);
        //Entity(const Entity&) = delete; // FIXME list requires copy constructor?
		b2Body *body;
        int depth;
};

#endif
