#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>

struct Sprite {
	SDL_Texture *texture;
	SDL_Rect *src;
	Sprite(SDL_Texture* t, SDL_Rect* r):
		texture(t), src(r) { }
};

struct Spritesheet {
	SDL_Texture *texture;
	int w, h, nx, ny;
	Spritesheet(SDL_Texture* t, int w, int h, int nx, int ny):
		texture(t), w(w), h(h), nx(nx), ny(ny) { }
	Sprite* GetSprite(int, int);
};


#endif
