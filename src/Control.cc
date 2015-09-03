#include "Control.h"
#include "Graphics.h"
#include "Model.h"

TextureCache::iterator Control::editorTextureIt = Model::tCache.end();
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

EditorTexture Control::GetEditorTexture() {
    int w, h, access;
    uint32_t format;
    SDL_Texture *t = editorTextureIt->second;
    SDL_QueryTexture(t, &format, &access, &w, &h);
    SDL_Rect src = {0, 0, w, h};
    SDL_Rect dst = {
        (int)(SCR_W - w*zoom)/2, (int)(SCR_H - h*zoom)/2,
        (int)(w*zoom), (int)(h*zoom) };
    return {t, src, dst};
}

void Control::CycleEditorTexture(Direction d) {
    if(d == FORWARD)
        if(editorTextureIt == Model::tCache.end())
            editorTextureIt = Model::tCache.begin();
        else editorTextureIt++;
    else if(d == BACKWARD)
        if(editorTextureIt == Model::tCache.begin())
            editorTextureIt = Model::tCache.end();
        else editorTextureIt--;
}

void Control::EditorControl(SDL_Event& event) {
    if(event.key.type == SDL_KEYDOWN) {
        switch( event.key.keysym.sym ) {
            case SDLK_RIGHT:
                CycleEditorTexture(FORWARD);
                break;
            case SDLK_LEFT:
                CycleEditorTexture(BACKWARD);
                break;
            case SDLK_SPACE:
                mode = RUN;
                break;
        }
    }
    else if(event.type == SDL_MOUSEBUTTONDOWN) {
    }
}

void Control::PlayerControl(SDL_Event& event, Character& player) {
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
