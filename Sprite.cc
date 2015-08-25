#include <SDL2/SDL_image.h>

#include "Sprite.h"
#include "Graphics.h"

TextureCache Sprite::tCache;

Sprite::Sprite(const char *file,
        int cellW, int cellH, SDL_Rect gridR, SDL_Rect spriteR) {

    // check if the texture is in the cache
    auto entry = tCache.find(file);
	if(entry != tCache.end())
		texture = entry->second;

    // otherwise load the texture into the cache
    else {
        texture = IMG_LoadTexture(Graphics::renderer, file);
        tCache[file] = texture;
    }
    
	// construct all the source rectangles of the texture
	srcs = new SDL_Rect*[gridR.w*gridR.h];
	n_srcs = 0;
	for(int x = 0; x < gridR.w; x++) {
		for(int y = 0; y < gridR.h; y++) {
			srcs[n_srcs] = new SDL_Rect();
			srcs[n_srcs]->x = (x + gridR.x) * cellW;
			srcs[n_srcs]->y = (y + gridR.y) * cellH;
			srcs[n_srcs]->w = cellW;
			srcs[n_srcs]->h = cellH;
			n_srcs++;
		}
	}

	// set the shape of the fixture
    float mx = spriteR.x - cellW/2.0f;
    float my = spriteR.y - cellH/2.0f;
    b2Vec2 points[4] = {
        b2Vec2( mx/16.0f,               my/16.0f),
        b2Vec2((mx + spriteR.w)/16.0f,  my/16.0f),
        b2Vec2((mx + spriteR.w)/16.0f, (my + spriteR.h)/16.0f),
        b2Vec2( mx/16.0f,              (my + spriteR.h)/16.0f)
    };

	b2PolygonShape *s= new b2PolygonShape();
	s->Set(points, 4);
    shape = (b2Shape*)s;
}
