#ifndef CHARACTER_H
#define CHARACTER_H

#include "Entity.h"

class World;

class Character {
	public:
		Character(World &w);
        void Update(int);
        static int GetCount() { return count; }
    private:
        static int count;
        Entity_spl parts;
        void Add(World &w, Entity *e);
};
#endif
