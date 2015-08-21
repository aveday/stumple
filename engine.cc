#include <iostream>

#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "engine.h"

int main(int argc, char *argv[]) {
    
    // Create engine objects
    World *world        = new World(b2Vec2(0.0f, 1.0f));
    Graphics *graphics  = new Graphics( new Grid(32, 0xff101010, 0xff000000) );
    Control *control    = new Control();
    Clock *clock        = new Clock();

	// Create tiles
    SDL_Texture *t = graphics->GetTexture("assets/brick.png");
	for(int i = 0; i < 12; i++) {
		Rect *src = new Rect(0, 16*(i%4), 16, 16);
		world->AddTile(t, src, i, 12);
	}

    // Create game objects
	Rect *src = new Rect(16, 0, 16, 16);
    Entity *player = world->AddEntity(t, src, 0.0f, 0.0f);

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
