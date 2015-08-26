#include <stdint.h>

#include <Box2D/Box2D.h>
#include "Entity.h"
#include "Sprite.h"

int Entity::count = 0;

Entity::Entity(World &w, const Sprite &sprite, float x, float y, int gid, int d):
        depth(d) {
	
    if (count >= MAX_ENTITIES)
        exit(EXIT_FAILURE); // TODO error handle entity overflow

    w.entities[count++] = this;

	b2BodyDef bDef;
	bDef.type = b2_dynamicBody;
	bDef.position.Set(x, y);

	body = w.CreateBody(&bDef);

	// TODO allow for multiple fixtures
    b2FixtureDef fDef;
    fDef.shape = sprite.shape;
    fDef.userData = (void*)&sprite;
    fDef.density = 10;
    fDef.filter.groupIndex = -gid; //TODO change filtering to use masks
	body->CreateFixture(&fDef);
}
