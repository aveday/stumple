#include "Image.h"



Image::Image(SDL_Texture* t, SDL_Rect *s, SDL_Rect *d, b2Fixture* f):
	texture(t), src(s), dst(d), fixture(f) {
}
