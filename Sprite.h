#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>
#include <Box2D/Box2D.h>

struct Sprite {
	SDL_Texture *texture;
	SDL_Rect **srcs;
	int n_srcs;
	b2Shape* shape;
	Sprite(SDL_Texture* t, SDL_Rect** rs, int n, b2Shape* sh):
		texture(t), srcs(rs), n_srcs(n), shape(sh) { }
};

struct Spritesheet {
    Spritesheet(const Spritesheet&) = delete;
	SDL_Texture *texture;
	int width, height, nx, ny;
	Spritesheet(SDL_Texture* t, int w, int h, int nx, int ny):
		texture(t), width(w), height(h), nx(nx), ny(ny) { }
	Sprite* GetSprite(int, int, float, float, int, int);
};

#endif
