#include <iostream>

#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "engine.h"

int main(int argc, char *argv[]) {
    
    // Create engine objects
    World *world        = new World();
    Graphics *graphics  = new Graphics( new Grid(16, LIGHTGREEN, GREEN) );
    Control *control    = new Control();
    Clock *clock        = new Clock();

    graphics->GetTexture("assets/brick.png");

    // Create game objects
    Entity *player = new Entity( IVec2(10, 10),
            Image(Polygon(4,16,0), GREY, 0));

    world->AddEntity(player);
   
    // Accept input
    while(control->GetInput(player)) {
        clock->Sleep();         // Delay to maintain FPS
        world->Update();        // Update the game world
        graphics->Draw(world);  // Draw to the screen
    }

    // Destroy all the things
    graphics->~Graphics();
    
    return 0;
}
