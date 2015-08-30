#include "Control.h"
#include "Graphics.h"

Control::Control() { }

b2Vec2 GetMousePos() {
    int x, y; 
    SDL_GetMouseState(&x, &y);
    double z = Graphics::zoom;
    return b2Vec2( x/z/PPM, y/z/PPM );
}

bool Control::GetInput(Character_sp player) {
    // make the player's head face towards the mouse
    (*player).parts["head"]->AngleTowards( GetMousePos(), 20);

    // handle key input
    while(SDL_PollEvent(&event) != 0 ) {

        if ( event.type == SDL_QUIT )
            return false;

        if(event.key.type == SDL_KEYDOWN 
				&& !(event.key.repeat)) {
            int f = 10000;
            switch( event.key.keysym.sym ) {
                case SDLK_w:
                    (*player).parts["torso"]->body->ApplyForceToCenter(b2Vec2(0, -f), true);
                    break;
                case SDLK_s:
                    (*player).parts["torso"]->body->ApplyForceToCenter(b2Vec2(0, f), true);
                    break;
                case SDLK_a:
                    (*player).parts["torso"]->body->ApplyForceToCenter(b2Vec2(-f, 0), true);
                    break;
                case SDLK_d:
                    (*player).parts["torso"]->body->ApplyForceToCenter(b2Vec2(f, 0), true);
                    break;
                case SDLK_SPACE:
                    break;
            }
        }
    }
    return true;
}
