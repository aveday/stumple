#include "Control.h"

Control::Control() { }

bool Control::GetInput(Character_sp player) {
    while(SDL_PollEvent(&event) != 0 ) {

        if ( event.type == SDL_QUIT )
            return false;
        if(event.key.type == SDL_KEYDOWN 
				&& !(event.key.repeat)) {

            switch( event.key.keysym.sym ) {
                case SDLK_UP:
                    break;
                case SDLK_DOWN:
                    break;
                case SDLK_LEFT:
                    break;
                case SDLK_RIGHT:
                    break;
                case SDLK_SPACE:
                    break;
            }
        }
    }
    return true;
}
