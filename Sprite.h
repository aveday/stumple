#ifndef SPRITE_H
#define SPRITE_H

#include <map>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <Box2D/Box2D.h>


typedef struct {
    std::string name;
    std::string texture_file;
    int cellw, cellh;
    SDL_Rect grid, sprite;
} SpriteDef;

class Sprite;
typedef std::map<std::string, Sprite> SpriteCache;
typedef std::map<std::string, SDL_Texture*> TextureCache;
typedef std::vector<SpriteDef> SpriteDef_v;

// TODO rename Sprites to Models, since they define b2Shapes as well
class Sprite {
    public:
        Sprite() {}; // required for map
        Sprite(const SpriteDef&);
        b2Shape *shape;
        SDL_Texture *texture;
        SDL_Rect **srcs;
        int n_srcs;
        static SpriteCache cache;
    private:
        static TextureCache tCache;
};

void LoadSprites(SpriteCache&, const SpriteDef_v&);

#endif
