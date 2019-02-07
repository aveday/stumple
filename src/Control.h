#ifndef CONTROL_H
#define CONTROL_H

#include <SDL2/SDL.h>

class Graphics;
class Character;
class Editor;

enum Mode { EDIT, RUN };

class Control {
    public:
        static Mode mode;
        bool GetInput(Graphics&, Character&, Editor&);
    private:
        void Input(SDL_Event&, Graphics&, Editor&);
        void Input(SDL_Event&, Graphics&, Character&);
};

#endif
