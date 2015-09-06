#include <SDL2/SDL.h>
#include <Box2D/Box2D.h>

#include "Editor.h"
#include "Control.h"
#include "Model.h"

void Editor::CycleTexture(Direction d) {
    if(d == FORWARD) {
        if(textureIt == Model::tCache.end())
            textureIt = Model::tCache.begin();
        else textureIt++;
    }
    else if(d == BACKWARD) {
        if(textureIt == Model::tCache.begin())
            textureIt = Model::tCache.end();
        else textureIt--;
    }
}

void Editor::SetCorner(int corner) {
    if(corner == 1) drag = true;
    if(corner == 2) drag = false;

    int x, y; 
    SDL_GetMouseState(&x, &y);
    x = (x - GetTexture().dst.x) / Control::zoom;
    y = (y - GetTexture().dst.y) / Control::zoom;

    if(corner == 1)
        box = {x, y, x-box.x, y-box.y};
    if(drag)
        box = {box.x, box.y, x-box.x, y-box.y};
}

Texture Editor::GetTexture() {
    int w, h, access;
    uint32_t format;
    SDL_Texture *t = textureIt->second;
    SDL_QueryTexture(t, &format, &access, &w, &h);
    SDL_Rect src = {0, 0, w, h};
    SDL_Rect dst = {
        (int)(100), (int)(100), //FIXME recenter
        (int)(w*Control::zoom), (int)(h*Control::zoom) };
    return {t, src, dst};
}
