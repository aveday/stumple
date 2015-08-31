#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdint.h>

#include "World.h"

class b2Body;
class SDL_Window;
class SDL_Renderer;

static const int SCR_W = 1280;
static const int SCR_H = 720;
static const int SCR_X = 180;
static const int SCR_Y = 100;

struct Grid {
    uint32_t color;
    uint32_t background;
    Grid(uint32_t c, uint32_t bg):
        color(c), background(bg) { }
};

class Graphics {
    private:
		Grid* grid;
        SDL_Window* window;

    public:
        static double zoom;
        static SDL_Renderer* renderer;
        Graphics(const Graphics&) = delete;
        Graphics(double z, Grid&);
        ~Graphics();
        void Draw(const World&);
		void Draw(const b2Body&);
        void Draw(const Grid&);
};

#endif
