#include "stumble.h"
#include "modeldefs.h"

int main(int argc, char *argv[]) {
    double z = (argc > 1) ? atof(argv[1]) : 1;
    
    // Create engine objects
    b2Vec2 gravity(0, 9.8);
    Grid grid(0xff101010, 0xff000000);
    World world(gravity);
    Graphics graphics(grid, z);
    Control control;
    Editor editor;
    Clock clock;

    // Load textures and create models
    LoadModels(Model::cache, modeldefs);

    int tx = SCR_W/(z*PPM);
    int ty = SCR_H/(z*PPM);

    // Create player
    Character *player = new Character(world, "human",
                    b2Vec2(tx/2, ty-2),
                    world.characters.size()+1);
    world.Add(player);
    // Create some other characters
    for(int x = 1; x < 3; x++)
        world.Add( new Character(world, "human",
                    b2Vec2(tx/2 - x, ty-2),
                    world.characters.size()+1) );

    // Create tiles
    for(int y = 0; y < ty; y++) {
        world.Tile("brick", 0, y);
        world.Tile("brick", tx-1, y);
    }
    for(int x = 0; x < tx; x++) {
        world.Tile("brick", x, ty);
        world.Tile("brick", x, 0);
    }

    // Create some objects
    for(float y = ty/2; y < ty; y+=0.25)
        for(float x = tx/2+1 + 0.25 * ((int)(y*4)%2) ; x < tx/2+3; x+=0.5)
            world.Add( new Entity(world, "rock", b2Vec2(x,y), 0, 0) );

    // Accept input
    while(control.GetInput(graphics, *player, editor)) {
        int ms = clock.Sleep(); // Delay to maintain FPS
        switch(Control::mode) {
            case EDIT:
                editor.Update(ms);
                graphics.Draw(editor);   // Draw to the screen
                break;
            case RUN:
                world.Update(ms);       // Update the game world
                graphics.Draw(world);   // Draw to the screen
                break;
        }
    }

    return 0;
}
