#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>

class Input {
    public:
        SDL_Event event;
        Input();
        bool Run();
};

#endif
