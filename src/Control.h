#ifndef CONTROL_H
#define CONTROL_H

#include <SDL2/SDL.h>
#include <Box2D/Box2D.h>

#include "Character.h"
#include "Model.h"
#include "Editor.h"

enum Mode { EDIT, RUN };

class Control {
    public:
        Control(double);
        static Mode mode;
        static double zoom;
        bool GetInput(Character&, Editor&);
        static b2Vec2 GetMouseWorldPos();
    private:
        void Input(SDL_Event&, Editor&);
        void Input(SDL_Event&, Character&);
};

#endif
