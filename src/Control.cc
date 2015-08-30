#include "Control.h"
#include "Graphics.h"

Control::Control() { }

int f = 10000;

bool Control::GetInput(Character_sp player) {
    // get the world position of the mouse
    int x, y; 
    SDL_GetMouseState(&x, &y);
    double z = Graphics::zoom;
    b2Vec2 m( x/z/PPM, y/z/PPM );
    // get the world position of the head
    Entity &head = *(*player).parts["head"];
    b2Vec2 h( head.body->GetPosition() );
    // make the head target th mouse
    head.targetAngle = atan( (m.y-h.y) / (m.x-h.x) );

    // handle key input
    while(SDL_PollEvent(&event) != 0 ) {

        if ( event.type == SDL_QUIT )
            return false;
        if(event.key.type == SDL_KEYDOWN 
				&& !(event.key.repeat)) {

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
