#include "Character.h"
#include "Entity.h"
#include "World.h"

//FIXME after editor. this should probably be somewhere else
#include "characterdefs.h"

void Character::JoinPart(World &w, JointDef &j, b2Vec2 pos) {
    pos += 1.0/PPM * j.pos;
	b2RevoluteJointDef jointDef;
    jointDef.Initialize(parts[j.p1]->body, parts[j.p2]->body, pos);
	jointDef.enableLimit = true;
	jointDef.lowerAngle = j.min;
	jointDef.upperAngle = j.max;
    w.CreateJoint(&jointDef);
}

void Character::AddPart(World &w, PartDef &p, b2Vec2 pos) {
    pos += 1.0/PPM * p.pos;
    Entity *part = new Entity(w, p.sid, pos, gid, p.depth);
    w.Add(part);
    parts.insert( std::make_pair(p.name, part) );
}

Character::Character(World &w, std::string cid, b2Vec2 pos, int g):
        gid(g) {
    // FIXME after editor. same as above
    CharacterDef def = characterdefs[cid];

    // create the parts mentions in the definition
    for(auto it = def.parts.begin(); it != def.parts.end(); it++)
        AddPart(w, *it, pos);

    // make the joint between the parts
    for(auto it = def.joints.begin(); it != def.joints.end(); it++)
        JoinPart(w, *it, pos);

    // set the starting stance
    Act({"thighL", -0.2, 140.0f});
    Act({"thighR",  0.3, 140.0f});
    Act({"calfL",  -0.2, 100.0f});
    Act({"calfR",  -0.2, 100.0f});
    Act({"torso",   0.0, 220.0f});
    Act({"head",    0.0,  30.0f});

}

void Character::Act(Command c) {
    Entity &t = *parts[c.part];
    t.targetAngle = c.target;
    t.strength = c.strength;
}

void Character::Update(int ms) {
    // FIXME after editor. character behaviour depends on CharacterDef
    double n = 0.1;
    if((parts["torso"]->GetPos().x > parts["footL"]->GetPos().x+n
    && parts["torso"]->GetPos().x > parts["footL"]->GetPos().x+n)
    || (parts["torso"]->GetPos().x < parts["footR"]->GetPos().x-n
    && parts["torso"]->GetPos().x < parts["footR"]->GetPos().x-n)) {
        parts["head"]->strength = 0;
        parts["torso"]->strength = 0;
        parts["calfR"]->strength = 0;
        parts["calfL"]->strength = 0;
        parts["thighR"]->strength = 0;
        parts["thighL"]->strength = 0;
    } else {
        parts["head"]->strength   = 100;
        parts["torso"]->strength  = 1100;
        parts["calfR"]->strength  = 600;
        parts["calfL"]->strength  = 600;
        parts["thighR"]->strength = 600;
        parts["thighL"]->strength = 600;
    }
    for(auto it = parts.begin(); it != parts.end(); it++) {
        Entity &t = *it->second;
        b2Body &b = *it->second->body;
        double diff = t.targetAngle - b.GetAngle();
        double max = 0.5;
        if(diff > max)
            diff = max;
        if(diff < -max)
            diff = -max;
        b.ApplyTorque(t.strength * diff, true);
    }
}

