#ifndef CONTROL_H
#define CONTROL_H

#include <SDL2/SDL.h>
#include <Box2D/Box2D.h>

#include "Character.h"
#include "Model.h"

enum Mode { EDIT, RUN };
enum Direction { FORWARD, BACKWARD };

typedef struct {
    int x;
    int y;
} gVec2;

typedef struct {
    SDL_Texture* texture;
    SDL_Rect src;
    SDL_Rect dst;
} EditorTexture;

class Control {
    public:
        Control(double);
        static Mode mode;
        static double zoom;
        bool GetInput(Character&);
        static EditorTexture GetEditorTexture();
        //FIXME move to editor class
        static TextureCache::iterator editorTextureIt;
    private:
        b2Vec2 GetMouseWorldPos();
        void CycleEditorTexture(Direction);
        gVec2 editorTexturePos;
        void EditorControl(SDL_Event&);
        void PlayerControl(SDL_Event&, Character&);
};

#endif
