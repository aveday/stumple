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
    TextureLoaded = (textureIt != Model::tCache.end());
}

void Editor::SetCorner(int x, int y, Mouse action) {
    x = (x - GetTexture().dst.x) / Control::zoom;
    y = (y - GetTexture().dst.y) / Control::zoom;

    if(action == CLICK) {
        ModelDef def = {"", textureIt->first, {x, y, 0, 0}, {0,0,0,0}, 1, 1};
        defs.push_back(def);
    }
    else if(action == DRAG) {
        SDL_Rect &rect = defs.back().box;
        rect = {rect.x, rect.y, x-rect.x, y-rect.y};
    }
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
