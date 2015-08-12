#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL2_rotozoom.h>

#include "Colors.h"
#include "Graphics.h"

static const char* WINDOW_TITLE = "engine";
static const int GRID_SIZE = 16;

Graphics::Graphics():
        offset(Vec2(0, 0)),
        zoom(1) {

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

void Graphics::Draw(World *world) {
    // clear the screen and draw background
    SDL_RenderClear(renderer);
    boxColor(renderer, 0, 0, SCR_W, SCR_H, GREEN);

    // draw world
    DrawGrid();
    for(int i = 0; i < world->entityCount; i++) {
        Entity *e = world->entities[i];
        Polygon *shape = &(e->shape);
        DrawShape(shape, e->position, e->rotation, e->color);
    }
    // display the drawn frame
    SDL_RenderPresent(renderer);
}

void Graphics::DrawGrid() {
    // draw grid
    for(int x = (int)(offset.x)%GRID_SIZE; x < SCR_W; x += GRID_SIZE)
        lineColor(renderer, x, 0, x, SCR_H, LIGHTGREEN);
    for(int y = (int)(offset.y)%GRID_SIZE; y < SCR_H; y += GRID_SIZE)
        lineColor(renderer, 0, y, SCR_W, y, LIGHTGREEN);
}


void Graphics::DrawShape(
        Polygon *shape, Vec2 position, float angle, Uint32 color) {
    int n = shape->vertexCount;
    Sint16 x[n], y[n];
    for( int i = 0; i < n; i++ ) {
        Vec2 v = *shape->vertices[i];
        rotateVec2(&v, angle);
        v.add(position);

        x[i] = (Sint16)(v.x * GRID_SIZE +0.3); // adding 0.3 corrects floating 
        y[i] = (Sint16)(v.y * GRID_SIZE +0.3); // point error when typecasting
    }

    filledPolygonColor(renderer, x, y, n, color);
    for( int i = 0; i < n; i++ )
        aalineColor(renderer, x[i], y[i], x[(i+1)%n], y[(i+1)%n], 0xff000000);
}


