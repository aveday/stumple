#include <stdint.h>

#include <Box2D/Box2D.h>
#include "Entity.h"

Entity::Entity(World &w, Sprite &sprite, float x, float y, int gid, int d):
        depth(d) {
	
    if (w.entityCount == MAX_ENTITIES)
        exit(EXIT_FAILURE); // TODO error handle entity overflow

    w.entities[w.entityCount++] = this;

	b2BodyDef bDef;
	bDef.type = b2_dynamicBody;
	bDef.position.Set(x, y);

	body = w.CreateBody(&bDef);

	// TODO allow for multiple fixtures
    b2FixtureDef fDef;
    fDef.shape = sprite.shape;
    fDef.userData = &sprite;
    fDef.density = 10;
    fDef.filter.groupIndex = -gid; //TODO change filtering to use masks
	body->CreateFixture(&fDef);
}
