#include "Control.h"

Control::Control() { }

int f = 10000;

bool Control::GetInput(Character_sp player) {
    while(SDL_PollEvent(&event) != 0 ) {

        if ( event.type == SDL_QUIT )
            return false;
        if(event.key.type == SDL_KEYDOWN 
				&& !(event.key.repeat)) {

            switch( event.key.keysym.sym ) {
                case SDLK_UP:
                    (*player).parts["torso"]->body->ApplyForceToCenter(b2Vec2(0, -f), true);
                    break;
                case SDLK_DOWN:
                    (*player).parts["torso"]->body->ApplyForceToCenter(b2Vec2(0, f), true);
                    break;
                case SDLK_LEFT:
                    (*player).parts["torso"]->body->ApplyForceToCenter(b2Vec2(-f, 0), true);
                    break;
                case SDLK_RIGHT:
                    (*player).parts["torso"]->body->ApplyForceToCenter(b2Vec2(f, 0), true);
                    break;
                case SDLK_SPACE:
                    break;
            }
        }
    }
    return true;
}
