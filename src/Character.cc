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
    auto sp = Entity_sp( new Entity(w, p.sid, pos, 1, p.depth) );
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
    std::map<std::string,std::pair<double,double>> targets = {
        {"thighL", {-0.2, 140.0f}},
        {"thighR", { 0.3, 140.0f}},
        {"calfL",  {-0.2, 100.0f}},
        {"calfR",  {-0.2, 100.0f}},
        {"torso",  { 0.0, 220.0f}},
        {"head",  { 0.0, 30.0f}},
    };

    for(auto it = targets.begin(); it != targets.end(); it++) {
        Entity &t = *parts[it->first];
        t.targetAngle = it->second.first;
        t.strength = it->second.second;
    }

    for(auto it = parts.begin(); it != parts.end(); it++) {
        Entity &t = *it->second;
        b2Body &b = *it->second->body;
        b.ApplyTorque(t.strength * (t.targetAngle - b.GetAngle()), true);
    }
}

