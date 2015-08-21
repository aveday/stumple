#include "Sprite.h"


Sprite* Spritesheet::GetSprite(int x, int y) {
	SDL_Rect *src = new SDL_Rect();	
	src->x = w*x;
	src->y = h*y;
	src->w = w;
	src->h = h;
	return new Sprite(texture, src);
}

