#include <iostream>

#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "stumble.h"

int main(int argc, char *argv[]) {
    
    // Create engine objects
    World *world        = new World(b2Vec2(0.0f, 5.0f));
    Graphics *graphics  = new Graphics( new Grid(64, 0xff101010, 0xff000000) );
    Control *control    = new Control();
    Clock *clock        = new Clock();

    // Load textures and create sprites
    Spritesheet *bricks = graphics->CreateSpritesheet("assets/brick.png", 16, 16, 2, 5);
    Spritesheet *rocks  = graphics->CreateSpritesheet("assets/rocks.png", 32, 16, 4, 8);
    Spritesheet *items  = graphics->CreateSpritesheet("assets/items.png", 16, 16, 4, 4);
    Spritesheet *tests  = graphics->CreateSpritesheet("assets/test.png",  32, 32, 2, 2);
	//                                ords, size, amt
    Sprite *crate = bricks->GetSprite(1, 0, 1, 1, 1, 1);
    Sprite *brick = bricks->GetSprite(0, 0, 1, 1, 1, 4);
    Sprite *rock  =  rocks->GetSprite(0, 0, 2, 1, 4, 8);
    Sprite *test  =  tests->GetSprite(0, 0, 1, 1, 1, 1);

	Character *player = new Character(world, items);

    // Create tiles
    for(int i = 0; i < 12; i++)
		world->AddTile(brick, i, 10);

    // Create game objects
    for(int i = 0; i < 6; i++) {
		world->AddEntity(test, 5.0f, -5-i*2.0f, 0);
		world->AddEntity(rock, 5.0f, i*2.0f, 0);
	}

    for(int i = 0; i < 18; i++)
		world->AddEntity(crate, 1.0f, -i, 0);

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
