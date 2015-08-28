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
typedef std::shared_ptr<Character> Character_sp;
typedef std::list<std::shared_ptr<Character>> Character_spl;
typedef std::map<std::string,std::shared_ptr<Character>> Character_spm;
typedef std::map<std::string, CharacterDef> CharacterDef_m;

class Character {
	public:
		Character(World &w, std::string cid, b2Vec2);
        void Update(int);
    private:
        Entity_spm parts;
        void AddPart(World &w, PartDef &p, b2Vec2 pos);
        void JoinPart(World &w, JointDef &j, b2Vec2 pos);
};
#endif
