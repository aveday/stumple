#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdint.h>
#include <SDL2/SDL.h>
#include <Box2D/Box2D.h>
#include <string>

#include "World.h"
#include "Sprite.h"

static const int SCR_W = 1280;
static const int SCR_H = 720;
static const int SCR_X = 180;
static const int SCR_Y = 100;

struct Grid {
    int size;
    uint32_t color;
    uint32_t background;
    Grid(int s, uint32_t c, uint32_t bg):
        size(s), color(c), background(bg) { }
};

class Graphics {
    private:
        double zoom;
		Grid* grid;
        SDL_Window* window;

    public:
        static SDL_Renderer* renderer;
        Graphics(const Graphics&) = delete;
        Graphics(Grid&);
        ~Graphics();
        void Draw(World*);
		void Draw(b2Body*);
        void Draw(Grid*);
};

#endif
