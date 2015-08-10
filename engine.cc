#include <iostream>

#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "Graphics.h"
#include "Geometry.h"
#include "World.h"
#include "Entity.h"
#include "Colors.h"

#include "engine.h"


int main(int argc, char *argv[]) {
 
    // create game world and graphics
    World *world = new World();
    Graphics *graphics = new Graphics();

    // scratch code !!!

    Vec2 pos = Vec2(10, 10);
    Polygon square = Polygon(8, 2, 0);
    Entity *player = new Entity(pos, square, GREY);
    world->AddEntity(player);
   
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


        /* update and draw entities */
        world->Update(dt);
        graphics->Draw(world);

    }

    graphics->~Graphics();
    
    return 0;
}
