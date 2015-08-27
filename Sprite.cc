#include <SDL2/SDL_image.h>
#include <string>

#include "Sprite.h"
#include "Graphics.h"

TextureCache Sprite::tCache;
SpriteCache Sprite::cache;

void LoadSprites(SpriteCache &cache, const SpriteDef_v &defs) {
    for(auto it = defs.begin(); it != defs.end(); it++)
        cache.insert( std::make_pair(it->name, Sprite(*it)) );
}

Sprite::Sprite(const SpriteDef &def) {
    // load the texture into/from the texture cache
    auto entry = tCache.find(def.texture_file);
    if(entry == tCache.end()) {
        texture = IMG_LoadTexture(Graphics::renderer,def.texture_file.c_str());
        tCache[def.texture_file] = texture;
    } else
        texture = entry->second;
    
    // construct all the source rectangles of the texture
    srcs = new SDL_Rect*[def.grid.w*def.grid.h]; //FIXME replace with array
    n_srcs = 0;
    for(int x = 0; x < def.grid.w; x++) {
        for(int y = 0; y < def.grid.h; y++) {
            srcs[n_srcs] = new SDL_Rect();
            srcs[n_srcs]->x = (x + def.grid.x) * def.cellw;
            srcs[n_srcs]->y = (y + def.grid.y) * def.cellh;
            srcs[n_srcs]->w = def.cellw;
            srcs[n_srcs]->h = def.cellh;
            n_srcs++;
        }
    }

    // set the shape of the fixture // TODO allow for other shapes
    float mx = def.sprite.x - def.cellw/2.0f;
    float my = def.sprite.y - def.cellh/2.0f;
    b2Vec2 points[] = {
        1.0/PPM * b2Vec2(mx,     my),
        1.0/PPM * b2Vec2(mx+def.sprite.w, my),
        1.0/PPM * b2Vec2(mx+def.sprite.w, my+def.sprite.h),
        1.0/PPM * b2Vec2(mx,     my+def.sprite.h)
    };

    b2PolygonShape *sh= new b2PolygonShape();
    sh->Set(points, 4);
    shape = (b2Shape*)sh;
}
