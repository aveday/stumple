#ifndef EDITOR_H
#define EDITOR_H

#include <map>

#include "Model.h"
#include "Entity.h"

enum Direction { FORWARD, BACKWARD };
enum Tool { BOX, SHAPE, MOVE };
enum Mouse { CLICK, DRAG, RELEASE };

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
        void SetCorner(int, int, Mouse);
        Texture GetTexture();
        TextureCache::iterator textureIt = Model::tCache.end();

        ModelDef_v defs;

        std::map<Tool, uint32_t> toolColors = {
            {BOX,   0xff0000ff},
            {SHAPE, 0xff00ff00},
        };
};

#endif
