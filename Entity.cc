#include <stdint.h>

#include <Box2D/Box2D.h>
#include "Entity.h"
#include "Model.h"
#include "World.h"

int Entity::count = 0;


Entity::Entity(World &w, const std::string sid, float x, float y, int gid, int d):
        depth(d) {

    Model &model = Model::cache[sid];
	b2BodyDef bDef;
	bDef.type = b2_dynamicBody;
	bDef.position.Set(x, y);

	body = w.CreateBody(&bDef);

	// TODO allow for multiple fixtures
    b2FixtureDef fDef;
    fDef.shape = model.shape;
    fDef.userData = (void*)&model;
    fDef.density = 10;
    fDef.filter.groupIndex = -gid; //TODO change filtering to use masks
	body->CreateFixture(&fDef);
}
