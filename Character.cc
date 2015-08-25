#include "Character.h"
#include "Entity.h"
#include "World.h"

void Join(World &w,
		std::unique_ptr<Entity> const &e1, b2Vec2 p1,
		std::unique_ptr<Entity> const &e2, b2Vec2 p2,
		float low, float high) {

	b2RevoluteJointDef jointDef;
	jointDef.bodyA = e1->body;
	jointDef.bodyB = e2->body;
	jointDef.localAnchorA = p1;
	jointDef.localAnchorB = p2;

	jointDef.enableLimit = true;
	jointDef.lowerAngle = low;
	jointDef.upperAngle = high;

    w.CreateJoint(&jointDef);
}

Character::Character(World &w, Spritesheet *sheet) {
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
	head.reset( new Entity(w, *head1,  7, 4, 1, 2) );
    torso.reset(  new Entity(w, *torso1, 7, 5, 1, 2) );

	Join(w, head,  b2Vec2(0,0.2), torso, b2Vec2(0,-0.5), -1.3, 1.1);

	for(int i = 0; i < 2; i++) {
        // arms
        upper[i].reset(new Entity(w, *upper1,7, 6, 1, i*2+1) );
        fore[i].reset( new Entity(w, *fore1, 7, 5, 1, i*2+1) );
        hand[i].reset( new Entity(w, *hand1, 7, 7, 1, i*2+1) );
        Join(w, torso,    b2Vec2(0,-0.4), upper[i], b2Vec2(0,-0.3), -3.1, 1.1);
        Join(w, upper[i], b2Vec2(0, 0.3), fore[i],  b2Vec2(0,-0.3), -2.6, 0.0);
        Join(w, fore[i],  b2Vec2(0, 0.3), hand[i],  b2Vec2(0,-0.1), -0.5, 1);

        // legs
        thigh[i].reset(new Entity(w, *thigh1,7, 7, 1, i*3+1) );
        calf[i].reset( new Entity(w, *calf1, 7, 8, 1, i*3+1) );
        foot[i].reset( new Entity(w, *foot1, 7, 9, 1, i*3+1) );
        Join(w, torso,    b2Vec2(0,0.5), thigh[i],b2Vec2(0,-0.4), -2.1, 0.5);
        Join(w, thigh[i], b2Vec2(0,0.4), calf[i], b2Vec2(0,-0.4), -0.0, 2.1);
        Join(w, calf[i],  b2Vec2(0,0.4), foot[i], b2Vec2(0,-0.0), -0.5, 1.1);
    }
}

void Character::Update(int ms) {
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

