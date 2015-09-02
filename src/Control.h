#ifndef CONTROL_H
#define CONTROL_H

#include <SDL2/SDL.h>

#include "Character.h"

enum Mode { EDIT, RUN };

class Control {
    public:
        Control();
        static Mode mode;
        bool GetInput(Character&);
        void EditorControl(SDL_Event&);
        void PlayerControl(SDL_Event&, Character&);
};

#endif
