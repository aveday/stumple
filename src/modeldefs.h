#ifndef MODELDEFS_H
#define MODELDEFS_H

#include "Model.h"

// FIXME change def names to an enum or something
// maybe use a map like CharacterDefs
ModelDef_v modeldefs = {
    // environment models
    {"brick", "assets/bricks.png", 16, 16, {0,0,4,4}, {0,0,16,16}},
    {"crate", "assets/items.png",  16, 16, {1,0,1,1}, {0,0,16,16}},
    {"rock",  "assets/rocks.png",  32, 16, {0,0,4,8}, {0,0,32,16}},

    // character models
    {"head",  "assets/body.png", 16, 16, {0,0,1,1}, {6,4,5,10}},
    {"torso", "assets/body.png", 16, 16, {0,1,1,1}, {5,1,7,13}},
    {"thigh", "assets/body.png", 16, 16, {0,2,1,1}, {5,1,5,14}},
    {"calf",  "assets/body.png", 16, 16, {0,3,1,1}, {6,1,4,15}},
    {"foot",  "assets/body.png", 16, 16, {0,4,1,1}, {6,6,10,4}},
    {"fore",  "assets/body.png", 16, 16, {1,1,1,1}, {5,1,4,13}},
    {"upper", "assets/body.png", 16, 16, {1,2,1,1}, {6,4,3,10}},
    {"hand",  "assets/body.png", 16, 16, {1,3,1,1}, {6,8,4,7}}

};

#endif
