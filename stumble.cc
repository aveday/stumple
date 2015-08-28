#include "stumble.h"
#include "modeldefs.h"

int main(int argc, char *argv[]) {
    int z = (argc > 1) ? atoi(argv[1]) : 2;
    
    // Create engine objects
    b2Vec2 gravity(0, 5);
    Grid grid(0xff101010, 0xff000000);
    World world(gravity);
    Graphics graphics(z, grid);
    Control control;
    Clock clock;

    // Load textures and create models
    LoadModels(Model::cache, modeldefs);

	world.Add( new Character(world) );

    int tx = SCR_W/(z*PPM);
    int ty = SCR_H/(z*PPM);
    // Create tiles
    for(int x = 0; x < tx; x++)
        for(int y = ty-2; y < ty; y++)
            world.AddTile("brick", x, y);

    // Create some game objects
    for(int y = ty-12; y < ty-5; y++)
        world.Add( new Entity(world, "rock", 2, y, 0, 0) );

    for(int y = 0; y < 4; y++)
        for(int x = 0; x < tx; x+=4)
            world.Add( new Entity(world, "crate", x, y, 0, 0) );

    // Accept input
    while(control.GetInput(*world.characters.begin())) { // FIXME
        int ms = clock.Sleep(); // Delay to maintain FPS
        world.Update(ms);       // Update the game world
        graphics.Draw(world);   // Draw to the screen
    }

    return 0;
}
