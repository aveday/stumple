#ifndef CONTROL_H
#define CONTROL_H

#include <SDL2/SDL.h>

#include "Entity.h"

class Control {
    public:
        SDL_Event event;
        Control();
        bool GetInput(Entity*);
};

#endif
