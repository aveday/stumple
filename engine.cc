#include <iostream>

#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "Graphics.h"
#include "Input.h"
#include "Clock.h"
#include "Geometry.h"
#include "World.h"
#include "Entity.h"
#include "Colors.h"

#include "engine.h"


int main(int argc, char *argv[]) {
    
    // Create engine objects
    World *world        = new World();
    Graphics *graphics  = new Graphics();
    Input *input        = new Input();
    Clock *clock        = new Clock();

    // Create game objects
    Entity *player = new Entity( Vec2(10, 10), Polygon(4, 1, 0), GREY );
    world->AddEntity(player);
   
    // Accept input
    while(input->Run()) {
        clock->Sleep();         // Delay to maintain FPS
        world->Update();        // Update the game world
        graphics->Draw(world);  // Draw to the screen
    }

    // Destroy all the things
    graphics->~Graphics();
    delete world;
    delete graphics;
    delete input;
    
    return 0;
}
