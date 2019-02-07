#include <SDL2/SDL.h>
#include <Box2D/Box2D.h>

#include "Editor.h"
#include "Model.h"

Editor::Editor(): World(b2Vec2(0,0)) {}

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

bool PointInRect(SDL_Point p, SDL_Rect r) {
    return (p.x >= r.x && p.y >= r.y && p.x < r.x + r.w && p.y < r.y + r.h);
}

void Editor::MakeRelative(int &x, int &y) {
    // transform the position to be relative to the texture
    Texture t = GetTexture();
    x = (x - t.pos.x);
    y = (y - t.pos.y);
}

//TODO make utility file for stuff like this
void confine(int &n, int min, int max) {
    n = std::min(n, max);
    n = std::max(n, min);
}

void Editor::StartBox(int x, int y) {
    MakeRelative(x, y);
    // create a new modeldef with texture_file and box corner
    defs.push_back({});
    def = &defs.back();
    def->name = "editorModel";
    def->texture_file = textureIt->first;
    def->box = {x, y, 0, 0};
    def->shape = {x, y, 0, 0};
    def->xTiles = 1;
    def->yTiles = 1;

}

void Editor::DragBox(int x, int y) {
    if(def == nullptr)
        return;
    MakeRelative(x, y);
    // update the width and height of the box
    SDL_Rect &box = def->box;
    box.w = x - box.x;
    box.h = y - box.y;
}

void Editor::StartShape(int x, int y) {
    // check if the shaped is being drawn inside a box
    def = GetClicked(x, y, false);
    if(def != nullptr) {
        // confine the shape inside the box
        MakeRelative(x, y);
        SDL_Rect &box = def->box;
        confine(x, box.x, box.x + box.w);
        confine(y, box.y, box.y + box.h);
        // draw a new shape for the current bounding box
        def->shape = {x, y, 0, 0};
    }
}

void Editor::DragShape(int x, int y) {
    if(def == nullptr)
        return;
    MakeRelative(x, y);
    // confine the shape inside the box
    SDL_Rect &box = def->box;
    confine(x, box.x, box.x + box.w);
    confine(y, box.y, box.y + box.h);
    // update the width and height of the shape
    SDL_Rect &shape = def->shape;
    shape.w = x - shape.x;
    shape.h = y - shape.y;
}

ModelDef* Editor::GetClicked(int x, int y, bool shape) {
    // get unzoomed screen position of the mouse click
    SDL_Point mouse = {x, y};

    // get unzoomed screen rect of each shape or box
    Texture t = GetTexture();
    for(auto def = defs.rbegin(); def != defs.rend(); def++) {
        SDL_Rect src = shape ? def->shape : def->box;
        SDL_Rect rect = {
            t.pos.x + src.x,
            t.pos.y + src.y,
            src.w, src.h, };

        // check if the click was inside the rect
        if( PointInRect(mouse, rect) )
            return &*def;
    }
    return nullptr;
}

void Editor::Grab(int x, int y) {
    def = GetClicked(x, y, true);
    if(def != nullptr) {
        // get world position of mouse 
        b2Vec2 wPos( (double)x/PPM, (double)y/PPM);
        printf("box: %d, %d\n", def->box.w, def->box.h);

        models.push_back( Model(*def) ); //FIXME duplicates
        grabbed = new Entity((World&)*this, models.back(), wPos, 1, 1);
    }
}

Texture Editor::GetTexture() {
    int w, h, access;
    uint32_t format;
    SDL_Texture *t = textureIt->second;
    SDL_QueryTexture(t, &format, &access, &w, &h);
    SDL_Rect src = {0, 0, w, h};
    SDL_Point pos = {10, 10}; // FIXME recenter
    return {t, src, pos};
}
