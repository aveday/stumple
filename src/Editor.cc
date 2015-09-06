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

    // drawing the bounding box for the model sprite
    if(tool == BOX) {
        if(action == CLICK) {
            // FIXME put something as model name, or get rid of it
            ModelDef def = {"", textureIt->first, {x, y, 0, 0}, {x,y,0,0}, 1, 1};
            defs.push_back(def);
        }
        else if(action == DRAG) {
            SDL_Rect &box = defs.back().box;
            box = {box.x, box.y, x-box.x, y-box.y};
        }
    }
    // drawing the shape for the model body
    else if(tool == SHAPE) {
        SDL_Rect &box = defs.back().box;
        SDL_Rect &shape = defs.back().shape;

        // FIXME also deal with negatives
        // restrict the shape to stay within the bounding box
        x = std::min(x, box.x+box.w);
        y = std::min(y, box.y+box.h);
        x = std::max(x, box.x);
        y = std::max(y, box.y);

        if(action == CLICK)
            shape = {x, y, 0, 0};
        else if(action == DRAG)
            shape = {shape.x, shape.y, x-shape.x, y-shape.y};
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
