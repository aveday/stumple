#ifndef MODEL_H
#define MODEL_H

#include <map>
#include <string>
#include <vector>
#include <SDL2/SDL.h>

class b2Shape;

typedef struct {
    std::string name;
    std::string texture_file;
    int cellw, cellh;
    SDL_Rect grid, model;
} ModelDef;

class Model;
typedef std::map<std::string, Model> ModelCache;
typedef std::map<std::string, SDL_Texture*> TextureCache;
typedef std::vector<ModelDef> ModelDef_v;

class Model {
    public:
        Model() {}; // required for map
        explicit Model(const ModelDef&);
        b2Shape *shape;
        SDL_Texture *texture;
        std::vector<SDL_Rect> srcs;
        static ModelCache cache;
        static TextureCache tCache;
};

void LoadModels(ModelCache&, const ModelDef_v&);

#endif
