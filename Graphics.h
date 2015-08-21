#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdint.h>
#include <SDL2/SDL.h>
#include <map>
#include <string>

#include "Geometry.h"
#include "World.h"

static const int SCR_W = 640;
static const int SCR_H = 480;
static const int SCR_X = 100;
static const int SCR_Y = 100;

typedef std::map<std::string, SDL_Texture*> TextureCache;
typedef TextureCache::iterator TextureCacheEntry;

class Spritesheet {
	public:
		SDL_Texture *texture;
		int x, y, nx, ny;
		Spritesheet(SDL_Texture*, int, int, int, int);
};

class Graphics {
    private:
        Vec2 offset;
        double zoom;
		Grid* grid;
        SDL_Renderer* renderer;
        SDL_Window* window;
        TextureCache tCache;

    public:
        Graphics(Grid*);
        ~Graphics();
		Spritesheet *CreateSpritesheet(const char*, int, int, int, int);
		SDL_Texture *GetTexture(const char*);
        void Draw(World*);
		void Draw(b2Body*);
        void Draw(Grid*);
		void Draw(b2PolygonShape*, b2Vec2);
};

#endif
