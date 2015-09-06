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
    for(int x = 0; x < def.xTiles; x++)
        for(int y = 0; y < def.yTiles; y++)
            srcs.push_back( {
                def.box.x + def.box.w * x,
                def.box.y + def.box.h * y,
                def.box.w, def.box.h });

    // set the shape of the fixture
    // TODO allow for other shapes
    float mx = def.shape.x - def.box.w/2.0f;
    float my = def.shape.y - def.box.h/2.0f;
    b2Vec2 points[]{
        1.0/PPM * b2Vec2(mx,     my),
        1.0/PPM * b2Vec2(mx+def.shape.w, my),
        1.0/PPM * b2Vec2(mx+def.shape.w, my+def.shape.h),
        1.0/PPM * b2Vec2(mx,     my+def.shape.h)
    };

    b2PolygonShape *sh= new b2PolygonShape();
    sh->Set(points, 4);
    shape = static_cast<b2Shape*>(sh);
}
