#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdint.h>
#include <SDL2/SDL.h>

#include "Geometry.h"
#include "World.h"

static const int SCR_W = 640;
static const int SCR_H = 480;
static const int SCR_X = 100;
static const int SCR_Y = 100;

class Graphics {
    private:
        Vec2 offset;
        double zoom;
        SDL_Renderer* renderer;
        SDL_Window* window;

    public:
        Graphics();
        ~Graphics();
        void Draw(World*);
        void Draw(Image*);
        void Draw(Grid);
};

#endif
