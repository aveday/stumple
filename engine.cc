#include <iostream>

#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "engine.h"

int main(int argc, char *argv[]) {
    
    // Create engine objects
    World *world        = new World();
    Graphics *graphics  = new Graphics( new Grid(32, 0xff101010, 0xff000000) );
    Control *control    = new Control();
    Clock *clock        = new Clock();

	// Create tiles
    SDL_Texture *t = graphics->GetTexture("assets/brick.png");
	world->AddTile(new Tile(t, 0, 0,  16, 16), 11, 10);
	world->AddTile(new Tile(t, 0, 16, 16, 16), 12, 10);
	world->AddTile(new Tile(t, 0, 32, 16, 16), 13, 10);
	world->AddTile(new Tile(t, 0, 48, 16, 16), 14, 10);
	world->AddTile(new Tile(t, 0, 64, 16, 16), 15, 10);

    // Create game objects
    Entity *player = new Entity( IVec2(14, 6),
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
