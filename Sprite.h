#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>

struct Sprite {
	SDL_Texture *texture;
	SDL_Rect **srcs;
	int n_srcs;
	Sprite(SDL_Texture* t, SDL_Rect** rs, int n):
		texture(t), srcs(rs), n_srcs(n) { }
};

struct Spritesheet {
	SDL_Texture *texture;
	int w, h, nx, ny;
	Spritesheet(SDL_Texture* t, int w, int h, int nx, int ny):
		texture(t), w(w), h(h), nx(nx), ny(ny) { }
	Sprite* GetSprite(int, int, int, int);
};


#endif
