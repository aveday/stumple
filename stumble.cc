#include <iostream>

#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "stumble.h"

int main(int argc, char *argv[]) {
    int gs = 32;
    if(argc > 1) 
        gs = atoi(argv[1]);
    
    // Create engine objects
    b2Vec2 gravity(0, 5);
    Grid grid(gs, 0xff101010, 0xff000000);
    World world(gravity);
    Graphics graphics(grid);
    Control control;
    Clock clock;

    // Load textures and create sprites
    Spritesheet *items  = graphics.CreateSpritesheet("assets/items.png", 16, 16, 2, 5);
    Spritesheet *bricks = graphics.CreateSpritesheet("assets/bricks.png",16, 16, 4, 4);
    Spritesheet *rocks  = graphics.CreateSpritesheet("assets/rocks.png", 32, 16, 4, 8);
    Spritesheet *body   = graphics.CreateSpritesheet("assets/body.png",  16, 16, 4, 4);
    Spritesheet *tests  = graphics.CreateSpritesheet("assets/test.png",  32, 32, 2, 2);
	//                                 ords, size, amt
    Sprite *brick = bricks->GetSprite(0, 0, 1, 1, 4, 4);
    Sprite *crate =  items->GetSprite(1, 0, 1, 1, 1, 1);
    Sprite *rock  =   rocks->GetSprite(0, 0, 2, 1, 4, 8);
    Sprite *test  =   tests->GetSprite(0, 0, 1, 1, 1, 1);

	Character player = Character(world, body);
    world.characters[world.characterCount++] = &player;

    int tx = SCR_W/grid.size;
    int ty = SCR_H/grid.size;
    // Create tiles
    for(int x = 0; x < tx; x++)
        for(int y = ty-4; y < ty; y++)
            world.AddTile(brick, x, y);

    // Create some game objects
    for(int y = ty-12; y < ty-5; y++)
		world.AddEntity(rock, 2, y, 0, 0);

    for(int y = 0; y < 4; y++)
        for(int x = 0; x < tx; x+=4)
            world.AddEntity(crate, x, y, 0, 0);

    // Accept input
    while(control.GetInput((Character*)NULL)) { // FIXME
        int t = clock.Sleep();         // Delay to maintain FPS
                world.Update(t);       // Update the game world
                graphics.Draw(&world);  // Draw to the screen
    }

    return 0;
}
