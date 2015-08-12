#include <iostream>

#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "engine.h"

int main(int argc, char *argv[]) {
    
    // Create engine objects
    World *world        = new World();
    Graphics *graphics  = new Graphics();
    Control *control    = new Control();
    Clock *clock        = new Clock();

    // Create game objects
    Entity *player = new Entity( Vec2(10, 10), Polygon(4, 1, 0), GREY );
    world->AddEntity(player);
   
    // Accept input
    while(control->GetInput()) {
        clock->Sleep();         // Delay to maintain FPS
        world->Update();        // Update the game world
        graphics->Draw(world);  // Draw to the screen
    }

    // Destroy all the things
    graphics->~Graphics();
    
    return 0;
}
