#ifndef CHARACTER_H
#define CHARACTER_H

#include <memory>
#include <Box2D/Box2D.h>

#include "Entity.h"

class World;

class Character {
	public:
		Character(World &w);
        void Update(int);
        static int GetCount() { return count; }
    private:
        static int count;
        std::unique_ptr<Entity>
            head, torso,
            foot[2], calf[2], thigh[2],
            hand[2], fore[2], upper[2];
};

#endif
