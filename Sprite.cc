#include "Sprite.h"

Sprite* Spritesheet::GetSprite(int x, int y, int xs, int ys) {
	SDL_Rect **srcs = new SDL_Rect*[xs*ys];
	int n = 0;
	for(int i = x; i < x+xs; i++) {
		for(int j = y; j < y+ys; j++) {
			srcs[n] = new SDL_Rect();
			srcs[n]->x = i*w;
			srcs[n]->y = j*h;
			srcs[n]->w = w;
			srcs[n]->h = h;
			n++;
		}
	}
	return new Sprite(texture, srcs, n);
}

