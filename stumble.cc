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
    Sprite brick("assets/bricks.png", 16, 16, {0,0,4,4}, {0,0,16,16});
    Sprite crate("assets/items.png",  16, 16, {1,0,1,1}, {0,0,16,16});
    Sprite rock( "assets/rocks.png",  32, 16, {0,0,4,8}, {0,0,32,16});

	Character player(world);

    int tx = SCR_W/grid.size;
    int ty = SCR_H/grid.size;
    // Create tiles
    for(int x = 0; x < tx; x++)
        for(int y = ty-2; y < ty; y++)
            world.AddTile(&brick, x, y);

    // Create some game objects
    for(int y = ty-12; y < ty-5; y++)
        new Entity(world, rock, 2, y, 0, 0);

    for(int y = 0; y < 4; y++)
        for(int x = 0; x < tx; x+=4)
            new Entity(world, crate, x, y, 0, 0);

    // Accept input
    while(control.GetInput((Character*)NULL)) { // FIXME
        int ms = clock.Sleep();         // Delay to maintain FPS
        world.Update(ms);       // Update the game world
        graphics.Draw(&world);  // Draw to the screen
    }

    return 0;
}
