#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL2_rotozoom.h>
#include <SDL2/SDL_image.h>

#include "Colors.h"
#include "Graphics.h"

static const bool DEBUG = false;

static const char* WINDOW_TITLE = "engine";

Sprite* Spritesheet::GetSprite(int x, int y) {
	SDL_Rect *src = new SDL_Rect();	
	src->x = w*x;
	src->y = h*y;
	src->w = w;
	src->h = h;
	return new Sprite(texture, src);
}

Spritesheet* Graphics::CreateSpritesheet(
		const char* fname, int x, int y, int nx, int ny) {
	SDL_Texture *t = GetTexture(fname);
	return new Spritesheet(t, x, y, nx, ny);
}

Graphics::Graphics(Grid *g):
        offset(Vec2(0, 0)),
        zoom(1),
        grid(g) {

    /* init SDL, create window and renderer */
    SDL_Init( SDL_INIT_EVERYTHING );
    window = SDL_CreateWindow(WINDOW_TITLE,
            SCR_X, SCR_Y, SCR_W, SCR_H, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

Graphics::~Graphics() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

SDL_Texture* Graphics::GetTexture(const char* file) {
	// check if the texture has already been cached
    TextureCacheEntry entry = tCache.find(file);
	if(entry != tCache.end())
		return entry->second;
	// otherwise load the texture into the cache
	SDL_Texture *t = IMG_LoadTexture(renderer, file);
	tCache[file] = t;
	return t;
}

void Graphics::Draw(World *world) {
    // clear the screen
    SDL_RenderClear(renderer);

    // draw grid and tiles
    Draw(grid);
	Draw(world->body);

    // draw entities
    for(int i = 0; i < world->entityCount; i++)
        Draw(world->entities[i]->body);

    // display the drawn frame
    SDL_RenderPresent(renderer);
}

void Graphics::Draw(Grid *g) {
    boxColor(renderer, 0, 0, SCR_W, SCR_H, g->background);
    for(int x = (int)(offset.x)%g->size; x < SCR_W; x += g->size)
        lineColor(renderer, x, 0, x, SCR_H, g->color);
    for(int y = (int)(offset.y)%g->size; y < SCR_H; y += g->size)
        lineColor(renderer, 0, y, SCR_W, y, g->color);
}

void Graphics::Draw(b2Body *body) {
    b2Vec2 pos = body->GetPosition();
	pos *= grid->size;

	float angle = body->GetAngle() / M_PI * 180;

	for(b2Fixture *f = body->GetFixtureList(); f; f = f->GetNext()) {
		Image *image = (Image*)f->GetUserData();

		SDL_Rect dst = {
			(int)(pos.x + image->dst->x),
			(int)(pos.y + image->dst->y),
			grid->size, grid->size};

		SDL_RenderCopyEx(renderer, image->texture, image->src, &dst,
				angle, NULL, SDL_FLIP_NONE);

		if(DEBUG)
			Draw((b2PolygonShape*)f->GetShape(), pos);
	}
}

void Graphics::Draw(b2PolygonShape *shape, b2Vec2 pos) {
    int n = shape->GetVertexCount();
    Sint16 x[n], y[n];
    for( int i = 0; i < n; i++ ) {
        x[i] = grid->size * shape->GetVertex(i).x + pos.x;
        y[i] = grid->size * shape->GetVertex(i).y + pos.y;
    }
    filledPolygonColor(renderer, x, y, n, 0x80800000);
}
