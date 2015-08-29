#ifndef MODELDEFS_H
#define MODELDEFS_H

#include "Model.h"

// FIXME change def names to an enum or something
// maybe use a map like CharacterDefs
ModelDef_v modeldefs = {
    // environment models
    {"brick", "assets/bricks.png", 64, 64, {0,0,1,1}, {0,0,64,64}},
    {"crate", "assets/items.png",  16, 16, {1,0,1,1}, {0,0,16,16}},
    {"rock",  "assets/rocks.png",  32, 16, {0,0,4,8}, {0,0,32,16}},
    // character models
    {"head",  "assets/body.png", 32, 32, {0,0,1,1}, {12, 8,10,20}},
    {"torso", "assets/body.png", 32, 32, {0,1,1,1}, {10, 2,14,26}},
    {"thigh", "assets/body.png", 32, 32, {0,2,1,1}, {10, 2,10,26}},
    {"calf",  "assets/body.png", 32, 32, {0,3,1,1}, {12, 2, 8,30}},
    {"foot",  "assets/body.png", 32, 32, {0,4,1,1}, {12,11,20, 8}},
    {"fore",  "assets/body.png", 32, 32, {1,1,1,1}, {10, 2, 8,26}},
    {"upper", "assets/body.png", 32, 32, {1,2,1,1}, {12, 8, 6,20}},
    {"hand",  "assets/body.png", 32, 32, {1,3,1,1}, {12,16, 8,14}},

};

#endif
