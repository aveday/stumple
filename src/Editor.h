#ifndef EDITOR_H
#define EDITOR_H

#include "Model.h"

enum Direction { FORWARD, BACKWARD };

typedef struct {
    SDL_Texture* texture;
    SDL_Rect src;
    SDL_Rect dst;
} Texture; //FIXME rename

class Editor {
    public:
        void CycleTexture(Direction d);
        void SetCorner(int);
        Texture GetTexture();
        TextureCache::iterator textureIt = Model::tCache.end();
        SDL_Rect box = {0,0,16,16};//FIXME
        bool drag = false;
};

#endif
