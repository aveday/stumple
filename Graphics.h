#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdint.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL2_gfxPrimitives.h"
#include "SDL2/SDL2_rotozoom.h"

#include "Geometry.h"
#include "World.h"
#include "Colors.h"

static const int SCR_W = 640;
static const int SCR_H = 480;
static const int SCR_X = 100;
static const int SCR_Y = 100;


class Graphics {
	public:
		Vec2 offset;
		double zoom;
		SDL_Renderer* renderer;
		SDL_Window* window;

		Graphics();
		~Graphics();
		void Draw(World *world);
		void DrawGrid();
		void DrawShape(Polygon*, Vec2, float, Uint32);
};

#endif
