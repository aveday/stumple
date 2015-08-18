#include "Control.h"

Control::Control() { }

bool Control::GetInput(Entity *player) {
    while(SDL_PollEvent(&event) != 0 ) {

        if ( event.type == SDL_QUIT )
            return false;
        if ( event.key.type == SDL_KEYDOWN && !(event.key.repeat) ) {

            switch( event.key.keysym.sym ) {
                case SDLK_UP:
					player->Move(IVec2(0,-1));
                    break;
                case SDLK_DOWN:
					player->Move(IVec2(0,1));
                    break;
                case SDLK_LEFT:
					player->Move(IVec2(-1,0));
                    break;
                case SDLK_RIGHT:
					player->Move(IVec2(1,0));
                    break;
                case SDLK_SPACE:
                    break;
            }
        }
    }
    return true;
}
