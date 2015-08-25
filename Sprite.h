#ifndef SPRITE_H
#define SPRITE_H

#include <map>
#include <SDL2/SDL.h>
#include <Box2D/Box2D.h>

typedef std::map<std::string, SDL_Texture*> TextureCache;

struct Sprite {
    Sprite(const char *file,
            int cellW, int cellH, SDL_Rect gridR, SDL_Rect spriteR);
    SDL_Texture *texture;
    SDL_Rect **srcs;
    int n_srcs;
    b2Shape* shape;
    static TextureCache tCache;
};

#endif
