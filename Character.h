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
        Entity_sp
            head, torso,
            foot[2], calf[2], thigh[2],
            hand[2], fore[2], upper[2];
};
#endif
