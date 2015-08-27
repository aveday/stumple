#include <SDL2/SDL_image.h>
#include <string>

#include "Model.h"
#include "Graphics.h"

TextureCache Model::tCache;
ModelCache Model::cache;

void LoadModels(ModelCache &cache, const ModelDef_v &defs) {
    for(auto it = defs.begin(); it != defs.end(); it++)
        cache.insert( std::make_pair(it->name, Model(*it)) );
}

Model::Model(const ModelDef &def) {
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
    float mx = def.model.x - def.cellw/2.0f;
    float my = def.model.y - def.cellh/2.0f;
    b2Vec2 points[] = {
        1.0/PPM * b2Vec2(mx,     my),
        1.0/PPM * b2Vec2(mx+def.model.w, my),
        1.0/PPM * b2Vec2(mx+def.model.w, my+def.model.h),
        1.0/PPM * b2Vec2(mx,     my+def.model.h)
    };

    b2PolygonShape *sh= new b2PolygonShape();
    sh->Set(points, 4);
    shape = (b2Shape*)sh;
}
