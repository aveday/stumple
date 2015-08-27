#ifndef MODEL_H
#define MODEL_H

#include <map>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <Box2D/Box2D.h>


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
        Model(const ModelDef&);
        b2Shape *shape;
        SDL_Texture *texture;
        SDL_Rect **srcs;
        int n_srcs;
        static ModelCache cache;
    private:
        static TextureCache tCache;
};

void LoadModels(ModelCache&, const ModelDef_v&);

#endif