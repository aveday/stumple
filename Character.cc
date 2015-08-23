#include "Character.h"
#include "Entity.h"
#include "World.h"

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

Character::Character(World *w, Spritesheet *sheet):
        world(w) {
	// load the sprites
    Sprite *head1  = sheet->GetSprite(0, 0,.4,.4, 1, 1);
    Sprite *torso1 = sheet->GetSprite(0, 1,.5, 1, 1, 1);

    Sprite *thigh1 = sheet->GetSprite(0, 2,.3,.8, 1, 1);
    Sprite *calf1  = sheet->GetSprite(0, 3,.3,.8, 1, 1);
    Sprite *foot1  = sheet->GetSprite(0, 4,.4,.2, 1, 1);

	Sprite *fore1  = sheet->GetSprite(1, 1,.2,.6, 1, 1);
	Sprite *upper1 = sheet->GetSprite(1, 2,.2,.6, 1, 1);
	Sprite *hand1  = sheet->GetSprite(1, 3,.2,.2, 1, 1);


	// start with the head & torso
	Entity *head  = w->AddEntity(head1,  7, 4, 1, 2);
	Entity *torso = w->AddEntity(torso1, 7, 5, 1, 2);
	// torso->body->SetFixedRotation(true);
	// head->body->SetFixedRotation(true);
	Join(world, head,  b2Vec2(0,0.2), torso, b2Vec2(0,-0.5), -b2_pi/3.0, b2_pi/3.0);
    this->head = head;

	// arms
	for(int i = 0; i < 2; i++) {
        Entity *upper = world->AddEntity(upper1,7, 6, 1, i*2+1);
        Entity *fore  = world->AddEntity(fore1, 7, 5, 1, i*2+1);
        Entity *hand  = world->AddEntity(hand1, 7, 7, 1, i*2+1);
        Join(world, torso, b2Vec2(0,-0.4), upper, b2Vec2(0,-0.3), -b2_pi, b2_pi/3.0);
        Join(world, upper, b2Vec2(0, 0.3), fore,  b2Vec2(0,-0.3), -5*b2_pi/6, 0);
        Join(world, fore,  b2Vec2(0, 0.3), hand,  b2Vec2(0,-0.1), -b2_pi/6.0,   b2_pi/3.0);
        this->hand[i] = hand;
    }
    // legs
	for(int i = 0; i < 2; i++) {
        Entity *thigh = world->AddEntity(thigh1,7, 7, 1, i*3+1);
        Entity *calf  = world->AddEntity(calf1, 7, 8, 1, i*3+1);
        Entity *foot  = world->AddEntity(foot1, 7, 9, 1, i*3+1);
        Join(world, torso, b2Vec2(0,0.5), thigh, b2Vec2(0,-0.4), -2*b2_pi/3.0, b2_pi/6.0);
        Join(world, thigh, b2Vec2(0,0.4), calf,  b2Vec2(0,-0.4), 0.0, 2*b2_pi/3.0);
        Join(world, calf,  b2Vec2(0,0.4), foot,  b2Vec2(0,-0.0), -b2_pi/6.0,   b2_pi/3.0);
        this->foot[i] = foot;
    }
}

void Character::Update(int t) {
    float d = foot[0]->body->GetPosition().y - head->body->GetPosition().y;
    float n = 3.5;
    float forceX = 0, forceY = 0;

    float feetD = abs(foot[0]->body->GetPosition().x - foot[1]->body->GetPosition().x - 2);
    float feetX = ( foot[0]->body->GetPosition().x +
                    foot[1]->body->GetPosition().x ) / 2;
    forceX = (feetX - head->body->GetPosition().x)+1;

    if(d < n && d > 0)
        forceY = -pow((n-d)/n, 1.2) * 500;

    head->body->ApplyForceToCenter(b2Vec2(forceX, forceY), true);

    foot[0]->body->ApplyForceToCenter(b2Vec2(-feetD, 10), true);
    foot[1]->body->ApplyForceToCenter(b2Vec2( feetD, 10), true);
}

