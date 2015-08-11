#include "Input.h"

Input::Input() { }

bool Input::Run() {
    bool running = true;

	while(SDL_PollEvent(&event) != 0 ) {

		if ( event.type == SDL_QUIT )
			running = false;
		if ( event.key.type == SDL_KEYDOWN && !(event.key.repeat) ) {

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
	return running;
}
