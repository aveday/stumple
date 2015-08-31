#ifndef CONTROL_H
#define CONTROL_H

#include <SDL2/SDL.h>

#include "Character.h"

enum Mode { EDIT, RUN };

class Control {
    public:
        SDL_Event event;
        Control();
        static Mode mode;
        bool GetInput(Character&);
};

#endif
