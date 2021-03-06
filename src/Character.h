#ifndef CHARACTER_H
#define CHARACTER_H

#include <Box2D/Box2D.h>
#include <list>
#include <map>
#include <string>
#include <vector>
#include <memory>

#include "Entity.h"

class World;
class Character;

typedef struct {
    std::string name;
    std::string sid;
    b2Vec2 pos;
    int depth;
} PartDef;

typedef struct {
    std::string name;
    std::string p1;
    std::string p2;
    b2Vec2 pos;
    double min, max;
} JointDef;

typedef struct {
    std::vector<PartDef> parts;
    std::vector<JointDef> joints;
} CharacterDef;

typedef std::vector<CharacterDef> CharacterDef_v;
typedef std::map<std::string, CharacterDef> CharacterDef_m;
typedef std::unique_ptr<Character> Character_up;
typedef std::list<std::unique_ptr<Character>> Character_upl;

typedef struct {
    std::string part;
    float target;
    float strength;
} Command;

typedef std::list<Command> Command_l;

class Character {
	public:
		Character(World &w, std::string cid, b2Vec2, int);
        void Update(int);
        Entity_pm parts;
    private:
        void AddPart(World &w, PartDef &p, b2Vec2 pos);
        void JoinPart(World &w, JointDef &j, b2Vec2 pos);
        void Act(Command);
        int gid;
};
#endif
