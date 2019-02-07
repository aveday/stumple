#include <SDL2/SDL.h>

#include "Control.h"
#include "Graphics.h"

Mode Control::mode = EDIT;

void Control::Input(SDL_Event& event, Graphics &graphics, Editor& editor) {

    // keyboard controls
    if(event.key.type == SDL_KEYDOWN) switch(event.key.keysym.sym) {

        // texture cycling
        case SDLK_RIGHT: editor.CycleTexture(FORWARD); break;
        case SDLK_LEFT: editor.CycleTexture(BACKWARD); break;
        // tool selection
        case SDLK_1: editor.tool = BOX;     break;
        case SDLK_2: editor.tool = SHAPE;   break;
        case SDLK_3: editor.tool = MOVE;    break;
        // switching back to RUN mode
        case SDLK_SPACE: mode = RUN;        break;
    }

    // handle mouse tools only if a texture is loaded
    if(!editor.TextureLoaded)
        return;

    // determine mouse action
    bool click = (event.type == SDL_MOUSEBUTTONDOWN);
    bool drag = (event.motion.state == SDL_PRESSED);

    // account for zoom in mouse position
    int x = drag ? event.motion.x : event.button.x;
    int y = drag ? event.motion.y : event.button.y;
    graphics.MakeAbsolute(x, y);

    switch(editor.tool) {

        // bounding box construction
        case BOX:
            if(click) editor.StartBox(x, y);
            if(drag)  editor.DragBox(x, y);
            break;

        // box2d shape construction
        case SHAPE:
            if(click) editor.StartShape(x, y);
            if(drag)  editor.DragShape(x, y);
            break;

        // dragging stuff around
        case MOVE:
            if(click) editor.Grab(x, y);
            break;
    }
}

void Control::Input(SDL_Event& event, Graphics &graphics, Character& player) {
    // make the player's head face towards the mouse
    //(*player).parts["head"]->AngleTowards( GetWorldMousePos(), 0);
    if(event.key.type == SDL_KEYDOWN && !(event.key.repeat)) {
        int f = 40000;
        switch( event.key.keysym.sym ) {
            case SDLK_w:
                player.parts["torso"]->body->ApplyForceToCenter(b2Vec2(0, -f), true);
                break;
            case SDLK_s:
                player.parts["torso"]->body->ApplyForceToCenter(b2Vec2(0, f), true);
                break;
            case SDLK_a:
                player.parts["torso"]->body->ApplyForceToCenter(b2Vec2(-f, 0), true);
                break;
            case SDLK_d:
                player.parts["torso"]->body->ApplyForceToCenter(b2Vec2(f, 0), true);
                break;
            case SDLK_SPACE:
                mode = EDIT;
                break;
        }
    }
}

bool Control::GetInput(Graphics &graphics, Character &player, Editor &editor) {
    // handle key input
    SDL_Event event;
    while(SDL_PollEvent(&event) != 0 ) {
        if ( event.type == SDL_QUIT )
            return false;
        if ( mode == EDIT )
            Input(event, graphics, editor);
        else if ( mode == RUN )
            Input(event, graphics, player);
    }
    return true;
}
