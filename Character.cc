#include "Character.h"
#include "Entity.h"
#include "World.h"

void Join(World &w,
		const Entity_sp &e1, b2Vec2 p1,
		const Entity_sp &e2, b2Vec2 p2,
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

Entity_sp &Character::Add(World &w, Entity *e) {
    parts.insert(parts.begin(), Entity_sp(e));
    w.Insert(*parts.begin());
    return *parts.begin();
}

int Character::count = 0;
Character::Character(World &w) {
    w.characters[count++] = this;

	// start with the head & torso
    auto head  = Add( w, new Entity(w, "head",  7, 4, 1, 2) );
    auto torso = Add( w, new Entity(w, "torso", 7, 5, 1, 2) );
	Join(w, head, b2Vec2(0,0.2), torso, b2Vec2(0,-0.5), -1.3, 1.1);

	for(int i = 0; i < 2; i++) {
        // arms
        auto u = Add( w, new Entity(w, "upper",7, 6, 1, i*2+1) );
        auto f = Add( w, new Entity(w, "fore", 7, 5, 1, i*2+1) );
        auto h = Add( w, new Entity(w, "hand", 7, 7, 1, i*2+1) );
        Join(w, torso, b2Vec2(0,-0.4), u, b2Vec2(0,-0.3), -3.1, 1.1);
        Join(w, u,     b2Vec2(0, 0.3), f,  b2Vec2(0,-0.3), -2.6, 0.0);
        Join(w, f,     b2Vec2(0, 0.1), h,  b2Vec2(0,-0.0), -0.5, 1.0);

        // legs
        auto t = Add( w, new Entity(w, "thigh",7, 7, 1, i*3+1) );
        auto c = Add( w, new Entity(w, "calf", 7, 8, 1, i*3+1) );
        auto o = Add( w, new Entity(w, "foot", 7, 9, 1, i*3+1) );
        Join(w, torso, b2Vec2(0,0.4), t,b2Vec2(0,-0.4), -2.1, 0.5);
        Join(w, t,     b2Vec2(0,0.4), c, b2Vec2(0,-0.4), -0.0, 2.1);
        Join(w, c,     b2Vec2(0,0.4), o, b2Vec2(0.2,-0), -0.5, 1.1);
    }
}

void Character::Update(int ms) {
    /*
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
    */
}

