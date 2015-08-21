#include <iostream>

#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "engine.h"

int main(int argc, char *argv[]) {
    
    // Create engine objects
    World *world        = new World(b2Vec2(0.0f, 5.0f));
    Graphics *graphics  = new Graphics( new Grid(32, 0xff101010, 0xff000000) );
    Control *control    = new Control();
    Clock *clock        = new Clock();

    // Load textures and create sprites
    Spritesheet *blocks = graphics->CreateSpritesheet(
	    "assets/brick.png", 16, 16, 2, 5);
    Sprite *crate = blocks->GetSprite(1,0);
    Sprite *brick = blocks->GetSprite(0,0);

    // Create tiles
    for(int i = 0; i < 12; i++)
	world->AddTile(brick, i, 12);

    // Create game objects
    Entity *player = world->AddEntity(crate, 3.0f, 0.0f);
    for(int i = 0; i < 18; i++)
	world->AddEntity(crate, 1.0f, -i);

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
