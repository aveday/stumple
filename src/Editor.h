#ifndef EDITOR_H
#define EDITOR_H

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
        Tool tool = BOX;
        Entity_upl entities; 
        void CycleTexture(Direction d);
        void SetCorner(int);
        Texture GetTexture();
        TextureCache::iterator textureIt = Model::tCache.end();
        SDL_Rect box = {0,0,16,16};//FIXME
        bool drag = false;
};

#endif
