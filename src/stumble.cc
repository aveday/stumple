#include "stumble.h"
#include "modeldefs.h"

int main(int argc, char *argv[]) {
    int z = (argc > 1) ? atoi(argv[1]) : 2;
    

    // Create engine objects
    b2Vec2 gravity(0, 9.8);
    Grid grid(0xff101010, 0xff000000);
    World world(gravity);
    Graphics graphics(z, grid);
    Control control;
    Clock clock;

    // Load textures and create models
    LoadModels(Model::cache, modeldefs);

    int tx = SCR_W/(z*PPM);
    int ty = SCR_H/(z*PPM);

    // Create tiles
    for(int x = 0; x < tx; x++)
        for(int y = ty-2; y < ty; y++)
            world.AddTile("brick", x, y);

    for(int x = 0; x < tx; x+=3) {
        world.Add( new Character(world, "human", b2Vec2(x,0)) );
        world.Add( new Entity(world, "rock", b2Vec2(x,-2), 0, 0) );
        for(int y = 3; y < 8; y++)
                world.Add( new Entity(world, "crate", b2Vec2(x,y), 0, 0) );
    }

    // Accept input
    while(control.GetInput(*world.characters.begin())) { // FIXME
        int ms = clock.Sleep(); // Delay to maintain FPS
        world.Update(ms);       // Update the game world
        graphics.Draw(world);   // Draw to the screen
    }

    return 0;
}
