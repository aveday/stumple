#include "Sprite.h"

Sprite* Spritesheet::GetSprite(int x, int y, float w, float h, int xs, int ys) {
	// construct all the source rectangles of the texture
	SDL_Rect **srcs = new SDL_Rect*[xs*ys];
	int n = 0;
	for(int i = x; i < x+xs; i++) {
		for(int j = y; j < y+ys; j++) {
			srcs[n] = new SDL_Rect();
			srcs[n]->x = i*width;
			srcs[n]->y = j*height;
			srcs[n]->w = width;
			srcs[n]->h = height;
			n++;
		}
	}
	// set the shape of the fixture
	b2PolygonShape *shape = new b2PolygonShape();
	shape->SetAsBox(w/2.0f, h/2.0f);
	return new Sprite(texture, srcs, n, (b2Shape*)shape);
}

