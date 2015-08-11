#include <iostream>

#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "Graphics.h"
#include "Input.h"
#include "Geometry.h"
#include "World.h"
#include "Entity.h"
#include "Colors.h"

#include "engine.h"


int main(int argc, char *argv[]) {
 
    // create game world, graphics, and input
    World *world = new World();
    Graphics *graphics = new Graphics();
    Input *input = new Input();

    // scratch code !!!

    Entity *player = new Entity( Vec2(10, 10), Polygon(8, 2, 0), GREY );

    world->AddEntity(player);
   
    /* init events, time */
    int time = SDL_GetTicks();

    while( input->Run() ) {

        // manage time
        int dt = 0;
        do dt = SDL_GetTicks() - time;
        while( dt < 1000.0/60.0 );
        time = SDL_GetTicks();

        /* update and draw entities */
        world->Update(dt);
        graphics->Draw(world);
    }

    graphics->~Graphics();
    delete world;
    delete graphics;
    delete input;
    
    return 0;
}
