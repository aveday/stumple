#ifndef CHARACTER_H
#define CHARACTER_H

#include <list>
#include <memory>
#include "Entity.h"

class World;
class Character;

typedef std::shared_ptr<Character> Character_sp;
typedef std::list<std::shared_ptr<Character>> Character_spl;

class Character {
	public:
		Character(World &w);
        void Update(int);
    private:
        Entity_spl parts;
        Entity_sp &Add(World &w, Entity *e);
};
#endif
