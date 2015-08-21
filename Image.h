#ifndef IMAGE_H
#define IMAGE_H

#include <SDL2/SDL.h>
#include "Box2D/Box2D.h"

class Image {
	public:
		SDL_Texture *texture;
		SDL_Rect *src, *dst;
		b2Fixture *fixture;

		Image(SDL_Texture*, SDL_Rect *src, SDL_Rect *dst, b2Fixture*);
};

#endif

