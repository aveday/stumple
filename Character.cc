#include "Character.h"

void Join(World *world,
		Entity *e1, b2Vec2 p1,
		Entity *e2, b2Vec2 p2,
		float low, float high) {

	b2RevoluteJointDef jointDef;
	jointDef.bodyA = e1->body;
	jointDef.bodyB = e2->body;
	jointDef.localAnchorA = p1;
	jointDef.localAnchorB = p2;

	jointDef.enableLimit = true;
	jointDef.lowerAngle = low;
	jointDef.upperAngle = high;

    world->CreateJoint(&jointDef);
}

Character::Character(World *world, Spritesheet *sheet) {
	// load the sprites
    Sprite *waist1 =  sheet->GetSprite(0, 0,.4,.4, 1, 1);
    Sprite *thigh1 =  sheet->GetSprite(0, 1,.3,.8, 1, 1);
    Sprite *calf1  =  sheet->GetSprite(0, 2,.3,.8, 1, 1);
    Sprite *shoe1  =  sheet->GetSprite(0, 3,.3,.3, 1, 1);

	// create entities with the sprites
	Entity *waist = world->AddEntity(waist1,7.0f, 6);
	waist->body->SetFixedRotation(true);
	Entity *thigh = world->AddEntity(thigh1,7.0f, 7);
	Entity *calf  = world->AddEntity(calf1, 7.0f, 8);
	Entity *shoe  = world->AddEntity(shoe1, 7.0f, 9);

	// link up the parts
	Join(world, waist, b2Vec2(0,0.2), thigh, b2Vec2(0,-0.4), -2*b2_pi/3.0, b2_pi/3.0);
	Join(world, thigh, b2Vec2(0,0.4), calf,  b2Vec2(0,-0.4), 0.0,        2*b2_pi/3.0);
	Join(world, calf,  b2Vec2(0,0.4), shoe,  b2Vec2(0,-0.2), -b2_pi/6.0,   b2_pi/3.0);
}
