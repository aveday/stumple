#include "Control.h"
#include "Graphics.h"
#include "Model.h"

Mode Control::mode = EDIT;
double Control::zoom = 1;

Control::Control(double z) {
    zoom = z;
}

b2Vec2 Control::GetMouseWorldPos() {
    int x, y; 
    SDL_GetMouseState(&x, &y);
    return b2Vec2( x/zoom/PPM, y/zoom/PPM );
}

void Control::Input(SDL_Event& event, Editor& editor) {
    if(event.key.type == SDL_KEYDOWN) {
        switch( event.key.keysym.sym ) {
            case SDLK_RIGHT:
                editor.CycleTexture(FORWARD);
                break;
            case SDLK_LEFT:
                editor.CycleTexture(BACKWARD);
                break;
            case SDLK_SPACE:
                mode = RUN;
                break;
        }
    }
    else if(event.type == SDL_MOUSEMOTION)
        editor.SetCorner(0);
    else if(event.type == SDL_MOUSEBUTTONDOWN)
        editor.SetCorner(1);
    else if(event.type == SDL_MOUSEBUTTONUP)
        editor.SetCorner(2);
}

void Control::Input(SDL_Event& event, Character& player) {
    // make the player's head face towards the mouse
    //(*player).parts["head"]->AngleTowards( GetWorldMousePos(), 0);
    if(event.key.type == SDL_KEYDOWN && !(event.key.repeat)) {
        int f = 10000;
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

bool Control::GetInput(Character &player, Editor &editor) {
    // handle key input
    SDL_Event event;
    while(SDL_PollEvent(&event) != 0 ) {
        if ( event.type == SDL_QUIT )
            return false;
        if ( mode == EDIT )
            Input(event, editor);
        else if ( mode == RUN )
            Input(event, player);
    }
    return true;
}
