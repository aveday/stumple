#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL2_gfxPrimitives.h"
#include "SDL2/SDL2_rotozoom.h"

#include "engine.h"

void drawShape(SDL_Renderer* ren,
        Polygon *shape, Vec2 position, float angle, Uint32 color) {
    int n = shape->vertexCount;
    Sint16 x[n], y[n];
    for( int i = 0; i < n; i++ ) {
        Vec2 v = shape->vertices[i];
        rotateVec2(&v, angle);
        v.add(position);
        x[i] = (Sint16)(v.x * GRID_SIZE);
        y[i] = (Sint16)(v.y * GRID_SIZE);
    }
    filledPolygonColor(ren, x, y, n, color);
    polygonColor(ren, x, y, n, 0xff000000);

}

void update(SDL_Renderer* ren, World* world, int dt) {
    // simulate world
    world->Update(dt);

    // draw world
    for(int i = 0; i < world->entityCount; i++) {
        Entity *e = &(world->entities[i]);
        Polygon *shape = &(e->shape);
        drawShape(ren, shape, e->coords, e->rotation, e->color);
    }
}

int main(int argc, char *argv[]) {
    World *world = new World();

    /* init SDL, create window and renderer */
    SDL_Init( SDL_INIT_EVERYTHING );
    SDL_Window* win = SDL_CreateWindow(WINDOW_TITLE,
            SCR_X, SCR_Y, SCR_W, SCR_H, SDL_WINDOW_SHOWN);
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    
    /* init events, time and random seed */
    int quit = 0;
    SDL_Event e;
    srand(time(NULL));
    int time = SDL_GetTicks();

    while( !quit ) {

        // manage time
        int dt = 0;
        do dt = SDL_GetTicks() - time;
        while( dt < 1000.0/60.0 );
        time = SDL_GetTicks();

        /* handle events */
        while( SDL_PollEvent(&e) != 0 ) {
            if ( e.type == SDL_QUIT )
                quit = 1;
            if ( e.key.type == SDL_KEYDOWN && !(e.key.repeat) ) {

                switch( e.key.keysym.sym ) {\
                    case SDLK_UP:
                        break;
                    case SDLK_DOWN:
                        break;
                    case SDLK_LEFT:
                        break;
                    case SDLK_RIGHT:
                        break;
                    case SDLK_SPACE:
                        break;
                }
            }
        }

        /* clear screen, draw background */
        SDL_RenderClear(ren);
        boxColor(ren, 0, 0, SCR_W, SCR_H, 0xffe06070);

        /* update and draw entities */
        update(ren, world, dt);

        /* , refresh screen */
        SDL_RenderPresent(ren);
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    
    return 0;
}
