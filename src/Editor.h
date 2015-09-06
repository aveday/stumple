#ifndef EDITOR_H
#define EDITOR_H

#include <map>

#include "Model.h"
#include "Entity.h"

enum Direction { FORWARD, BACKWARD };
enum Tool { BOX, SHAPE, MOVE };

typedef struct {
    SDL_Texture* texture;
    SDL_Rect src;
    SDL_Rect dst;
} Texture; //FIXME rename

class Editor {
    public:
        bool TextureLoaded = false;
        Tool tool = BOX;
        Entity_upl entities; 
        void CycleTexture(Direction d);
        void SetCorner(int, int, bool);
        Texture GetTexture();
        TextureCache::iterator textureIt = Model::tCache.end();

        ModelDef_v defs;

        std::map<Tool, uint32_t> toolColors = {
            {BOX,   0xa00000ff},
            {SHAPE, 0xa000ff00},
        };
};

#endif
