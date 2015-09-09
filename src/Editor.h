#ifndef EDITOR_H
#define EDITOR_H

#include <map>
#include <list>

#include "Model.h"
#include "Entity.h"
#include "World.h"

enum Direction { FORWARD, BACKWARD };
enum Tool { BOX, SHAPE, MOVE };

typedef struct {
    SDL_Texture* texture;
    SDL_Rect src;
    SDL_Rect dst;
} Texture; //FIXME rename

class Editor : public World {
    public:
        Editor();
        bool TextureLoaded = false;
        Tool tool = BOX;
        void CycleTexture(Direction d);
        void MakeRelative(int &x, int &y);
        void MakeGlobal(int &x, int &y);
        void StartBox(int x, int y);
        void DragBox(int x, int y);
        void StartShape(int x, int y);
        void DragShape(int x, int y);
        void Grab(int x, int y);
        void Drag(int x, int y);
        ModelDef* GetClicked(int x, int y, bool shape);
        Texture GetTexture();
        TextureCache::iterator textureIt = Model::tCache.end();

        Entity *grabbed = nullptr;
        ModelDef *def = nullptr;
        ModelDef_v defs;
        std::list<Model> models;

        std::map<Tool, uint32_t> toolColors = {
            {BOX,   0xa00000ff},
            {SHAPE, 0xa000ff00},
        };
};

#endif
