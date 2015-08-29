#include "stumble.h"
#include "modeldefs.h"

int main(int argc, char *argv[]) {
    float z = (argc > 1) ? atoi(argv[1]) : 1;
    
    // Create engine objects
    b2Vec2 gravity(0, 2);
    Grid grid(0xff101010, 0xff000000);
    World world(gravity);
    Graphics graphics(z, grid);
    Control control;
    Clock clock;

    // Load textures and create models
    LoadModels(Model::cache, modeldefs);

    int tx = SCR_W/(z*PPM);
    int ty = SCR_H/(z*PPM);

    // Create player
    for(int x = 0; x < 3; x++)
        world.Add( new Character(world, "human",
                    b2Vec2(tx/2 - x, ty-2),
                    world.characters.size()+1) );

    // Create tiles
    for(int x = 0; x < tx; x++)
        world.Tile("brick", x, ty);

    // Create some objects
    for(float y = ty/3; y < ty; y+=0.25)
        for(float x = tx/2+2 + 0.2 * ((int)(y*4)%2) ; x < tx/2+3; x+=0.5)
            world.Add( new Entity(world, "rock", b2Vec2(x,y), 0, 0) );

    // Accept input
    while(control.GetInput(*world.characters.begin())) { // FIXME
        int ms = clock.Sleep(); // Delay to maintain FPS
        world.Update(ms);       // Update the game world
        graphics.Draw(world);   // Draw to the screen
    }

    return 0;
}
