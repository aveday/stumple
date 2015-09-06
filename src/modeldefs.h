#ifndef MODELDEFS_H
#define MODELDEFS_H

#include "Model.h"

// FIXME change def names to an enum or something
// maybe use a map like CharacterDefs
ModelDef_v modeldefs = {
    // environment models
    {"brick", "assets/bricks.png", {0,0,64,64}, {0,0,64,64}, 1, 1},
    {"rock",  "assets/rocks.png",  {0,0,32,16}, {0,0,32,16}, 4, 8},
    // character models
    {"head",  "assets/body.png", { 0, 0,32,32}, {12, 8,10,20}, 1, 1},
    {"torso", "assets/body.png", { 0,32,32,32}, {10, 2,14,26}, 1, 1},
    {"thigh", "assets/body.png", { 0,64,32,32}, {10, 2,10,26}, 1, 1},
    {"calf",  "assets/body.png", { 0,96,32,32}, {12, 2, 8,30}, 1, 1},
    {"foot",  "assets/body.png", {0,128,32,32}, {12,11,20, 8}, 1, 1},
    {"fore",  "assets/body.png", {32,32,32,32}, {10, 2, 8,26}, 1, 1},
    {"upper", "assets/body.png", {32,64,32,32}, {12, 8, 6,20}, 1, 1},
    {"hand",  "assets/body.png", {32,96,32,32}, {12,16, 8,14}, 1, 1},

};

#endif
