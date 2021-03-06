#include <Box2D/Box2D.h>
#include "Entity.h"
#include "Model.h"
#include "World.h"

Entity::Entity(World &w, const std::string &sid, b2Vec2 pos, int gid, int d):
    Entity(w, Model::cache[sid], pos, gid, d) { }

Entity::Entity(World &w, const Model& model, b2Vec2 pos, int gid, int d):
        depth(d) {

	b2BodyDef bDef;
	bDef.type = b2_dynamicBody;
	bDef.position = pos;

	body = w.CreateBody(&bDef);

	// TODO allow for multiple fixtures
    b2FixtureDef fDef;
    fDef.shape = model.shape;
    fDef.userData = (void*)&model;
    fDef.density = 200;
    fDef.filter.groupIndex = -gid; //TODO change filtering to use masks
	body->CreateFixture(&fDef);
}

void Entity::AngleTowards(b2Vec2 pos, float s) {
    b2Vec2 p = body->GetPosition();
    targetAngle = atan( (pos.y-p.y) / (pos.x-p.x) );
    strength = s;
}

b2Vec2 Entity::GetPos() {
    return body->GetPosition();
}
