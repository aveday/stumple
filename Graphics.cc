#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL2_rotozoom.h>
#include <SDL2/SDL_image.h>

#include "Colors.h"
#include "Graphics.h"

static const bool DEBUG = false;

static const char* WINDOW_TITLE = "engine";

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
	// draw background and orthogonal lines
    boxColor(renderer, 0, 0, SCR_W, SCR_H, g->background);
    for(int x = (int)(offset.x)%g->size; x < SCR_W; x += g->size)
        lineColor(renderer, x, 0, x, SCR_H, g->color);
    for(int y = (int)(offset.y)%g->size; y < SCR_H; y += g->size)
        lineColor(renderer, 0, y, SCR_W, y, g->color);
}

void Graphics::Draw(b2Body *body) {
	float angle = body->GetAngle() / M_PI * 180;

	for(b2Fixture *f = body->GetFixtureList(); f; f = f->GetNext()) {
		// select sprite variant based on fixture pointer value
		Sprite *sprite = (Sprite*)f->GetUserData();
		int i = (int)(uintptr_t)f / 32 % sprite->n_srcs;
		SDL_Rect *src = sprite->srcs[i];

		// calculate the destination rectangle
		b2Vec2 center= f->GetAABB(0).GetCenter();
		SDL_Rect dst = {
			(int)((center.x - src->w/32.0f) * grid->size),
			(int)((center.y - src->h/32.0f) * grid->size),
			src->w*2, src->h*2
		};

		// draw the sprite
		SDL_RenderCopyEx(renderer, sprite->texture, sprite->srcs[i], &dst,
				angle, NULL, SDL_FLIP_NONE);
	}
}

void Graphics::Draw(b2PolygonShape *shape, b2Vec2 pos) {
	// draw a transparent overlay (used for testing)
    int n = shape->GetVertexCount();
    Sint16 x[n], y[n];
    for( int i = 0; i < n; i++ ) {
        x[i] = grid->size * shape->GetVertex(i).x + pos.x;
        y[i] = grid->size * shape->GetVertex(i).y + pos.y;
    }
    filledPolygonColor(renderer, x, y, n, 0x80800000);
}
