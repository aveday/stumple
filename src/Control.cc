#include "Control.h"
#include "Graphics.h"

Mode Control::mode = EDIT;
Control::Control() { }

b2Vec2 GetMousePos() {
    int x, y; 
    SDL_GetMouseState(&x, &y);
    double z = Graphics::zoom;
    return b2Vec2( x/z/PPM, y/z/PPM );
}

void Control::EditorControl(SDL_Event& event) {
    if(event.key.type == SDL_KEYDOWN) {
        switch( event.key.keysym.sym ) {
            case SDLK_SPACE:
                mode = RUN;
                break;
        }
    }
    else if(event.type == SDL_MOUSEBUTTONDOWN) {
        b2Vec2 pos = GetMousePos();
    }
}

void Control::PlayerControl(SDL_Event& event, Character& player) {
    // make the player's head face towards the mouse
    //(*player).parts["head"]->AngleTowards( GetMousePos(), 0);
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

bool Control::GetInput(Character &player) {
    // handle key input
    SDL_Event event;
    while(SDL_PollEvent(&event) != 0 ) {
        if ( event.type == SDL_QUIT )
            return false;
        if ( mode == EDIT )
            EditorControl(event);
        else if ( mode == RUN )
            PlayerControl(event, player);
    }
    return true;
}
