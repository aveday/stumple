#include "Character.h"
#include "Entity.h"
#include "World.h"

#include "characterdefs.h" //FIXME this should probably be somewhere else

void Character::JoinPart(World &w, JointDef &j, b2Vec2 pos) {
	b2RevoluteJointDef jointDef;
    jointDef.Initialize(parts[j.p1]->body, parts[j.p2]->body, pos+j.pos);
	jointDef.enableLimit = true;
	jointDef.lowerAngle = j.min;
	jointDef.upperAngle = j.max;
    w.CreateJoint(&jointDef);
}

void Character::AddPart(World &w, PartDef &p, b2Vec2 pos) {
    auto sp = Entity_sp( new Entity(w, p.sid, pos+p.pos, 1, p.depth) );
    parts.insert( std::make_pair(p.name, sp) );
    w.Insert(sp);
}

Character::Character(World &w, std::string cid, b2Vec2 pos) {
    CharacterDef def = characterdefs[cid]; // FIXME same as above

    // create the parts mentions in the definition
    for(auto it = def.parts.begin(); it != def.parts.end(); it++)
        AddPart(w, *it, pos);

    // make the joint between the parts
    for(auto it = def.joints.begin(); it != def.joints.end(); it++)
        JoinPart(w, *it, pos);
}

void Character::Update(int ms) {
    // FIXME character behaviour depends on CharacterDef
    b2Body &HEAD=*parts["head"]->body;
    b2Body &LF = *parts["footL"]->body;
    b2Body &RF = *parts["footR"]->body;

    float d = LF.GetPosition().y - HEAD.GetPosition().y;
    float n = 3.5;
    float forceX = 0, forceY = 0;

    float feetD = abs(LF.GetPosition().x - RF.GetPosition().x - 2);
    float feetX = ( LF.GetPosition().x +
                    RF.GetPosition().x ) / 2;
    forceX = (feetX - HEAD.GetPosition().x)+1;

    if(d < n && d > 0)
        forceY = -pow((n-d)/n, 1.2) * 1000;

    HEAD.ApplyForceToCenter(b2Vec2(forceX, forceY), true);

    LF.ApplyForceToCenter(b2Vec2(-feetD, 10), true);
    RF.ApplyForceToCenter(b2Vec2( feetD, 10), true);
}

