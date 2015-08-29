#ifndef CHARACTERDEFS_H
#define CHARACTERDEFS_H

#include "Character.h"

CharacterDef_m characterdefs = {
    {"human", {
        { // parts
            {"head",  "head",   b2Vec2(0.0,-3.2), 3},
            {"torso", "torso",  b2Vec2(0.0, 11.2), 3},
            // arms
            {"upperL", "upper", b2Vec2(0.0, 9.6), 1},
            {"upperR", "upper", b2Vec2(0.0, 9.6), 5},
            {"foreL",  "fore",  b2Vec2(0.0, 19.2), 1},
            {"foreR",  "fore",  b2Vec2(0.0, 19.2), 5},
            {"handL",  "hand",  b2Vec2(0.0, 20.8), 0},
            {"handR",  "hand",  b2Vec2(0.0, 20.8), 6},
            // legs
            {"thighL", "thigh", b2Vec2(0.0, 24.0), 2},
            {"thighR", "thigh", b2Vec2(0.0, 24.0), 4},
            {"calfL",  "calf",  b2Vec2(0.0, 36.8), 2},
            {"calfR",  "calf",  b2Vec2(0.0, 36.8), 4},
            {"footL",  "foot",  b2Vec2(-1.6, 44.8), 2},
            {"footR",  "foot",  b2Vec2(-1.6, 44.8), 4}
        },
        { // joints
            {"neck",      "head",   "torso",  b2Vec2(0.0, 3.2), -1.3, 1.1},
            // arms
            {"shoulderL", "torso",  "upperL", b2Vec2(0.0, 4.8), -1.1, 3.1},
            {"shoulderR", "torso",  "upperR", b2Vec2(0.0, 4.8), -1.1, 3.1},
            {"elbowL",    "upperL", "foreL",  b2Vec2(0.0, 14.4), -2.6, 0.0},
            {"elbowR",    "upperR", "foreR",  b2Vec2(0.0, 14.4), -2.6, 0.0},
            {"wristL",    "foreL",  "handL",  b2Vec2(0.0, 20.8), -0.5, 1.0},
            {"wristR",    "foreR",  "handR",  b2Vec2(0.0, 20.8), -0.5, 1.0},
            // legs
            {"hipL",      "torso",  "thighL", b2Vec2(0.0, 17.6), -2.1, 0.5},
            {"hipR",      "torso",  "thighR", b2Vec2(0.0, 17.6), -2.1, 0.5},
            {"kneeL",     "thighL", "calfL",  b2Vec2(0.0, 30.4), -0.0, 2.1},
            {"kneeR",     "thighR", "calfR",  b2Vec2(0.0, 30.4), -0.0, 2.1},
            {"ankleL",    "calfL",  "footL",  b2Vec2(0.0, 43.2), -0.5, 1.1},
            {"ankleR",    "calfR",  "footR",  b2Vec2(0.0, 43.2), -0.5, 1.1}
        }
    }}
};

#endif
