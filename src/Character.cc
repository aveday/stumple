#include "Character.h"
#include "Entity.h"
#include "World.h"

#include "characterdefs.h" //FIXME this should probably be somewhere else

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
    auto sp = Entity_sp( new Entity(w, p.sid, pos, gid, p.depth) );
    parts.insert( std::make_pair(p.name, sp) );
    w.Insert(sp);
}

Character::Character(World &w, std::string cid, b2Vec2 pos, int g):
        gid(g) {
    CharacterDef def = characterdefs[cid]; // FIXME same as above

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
    // FIXME character behaviour depends on CharacterDef
    for(auto it = parts.begin(); it != parts.end(); it++) {
        Entity &t = *it->second;
        b2Body &b = *it->second->body;
        b.ApplyTorque(t.strength * (t.targetAngle - b.GetAngle()), true);
    }
}

