#ifndef CHARACTERDEFS_H
#define CHARACTERDEFS_H

#include "Character.h"

CharacterDef_m characterdefs = {
    {"human", {
        { // parts
            {"head",  "head",   b2Vec2(0.0,-6.4), 12},
            {"torso", "torso",  b2Vec2(0.0, 22.4), 12},
            // arms
            {"upperL", "upper", b2Vec2(0.0, 19.2), 4},
            {"upperR", "upper", b2Vec2(0.0, 19.2), 20},
            {"foreL",  "fore",  b2Vec2(0.0, 38.4), 4},
            {"foreR",  "fore",  b2Vec2(0.0, 38.4), 20},
            {"handL",  "hand",  b2Vec2(-2.0,41.6), 0},
            {"handR",  "hand",  b2Vec2(-2.0,41.6), 24},
            // legs
            {"thighL", "thigh", b2Vec2(0.0, 48.0), 8},
            {"thighR", "thigh", b2Vec2(0.0, 48.0), 16},
            {"calfL",  "calf",  b2Vec2(0.0, 73.6), 8},
            {"calfR",  "calf",  b2Vec2(0.0, 73.6), 16},
            {"footL",  "foot",  b2Vec2(-6.0,89.6), 8},
            {"footR",  "foot",  b2Vec2(-6.0,89.6), 16}
        },
        { // joints
            {"neck",      "head",   "torso",  b2Vec2(0.0, 6.4), -1.3, 1.1},
            // arms
            {"shoulderL", "torso",  "upperL", b2Vec2(0.0, 9.6), -1.1, 3.1},
            {"shoulderR", "torso",  "upperR", b2Vec2(0.0, 9.6), -1.1, 3.1},
            {"elbowL",    "upperL", "foreL",  b2Vec2(0.0, 28.8),  -2.6, 0.0},
            {"elbowR",    "upperR", "foreR",  b2Vec2(0.0, 28.8),  -2.6, 0.0},
            {"wristL",    "foreL",  "handL",  b2Vec2(0.0, 44.1),  -0.5, 1.0},
            {"wristR",    "foreR",  "handR",  b2Vec2(0.0, 44.1),  -0.5, 1.0},
            // legs
            {"hipL",      "torso",  "thighL", b2Vec2(0.0, 35.2),  -2.1, 0.5},
            {"hipR",      "torso",  "thighR", b2Vec2(0.0, 35.2),  -2.1, 0.5},
            {"kneeL",     "thighL", "calfL",  b2Vec2(0.0, 60.8), -0.0, 2.1},
            {"kneeR",     "thighR", "calfR",  b2Vec2(0.0, 60.8), -0.0, 2.1},
            {"ankleL",    "calfL",  "footL",  b2Vec2(0.0, 86.4), -0.5, 1.1},
            {"ankleR",    "calfR",  "footR",  b2Vec2(0.0, 86.4), -0.5, 1.1}
        }
    }}
};

#endif

