#ifndef CONTROL_H
#define CONTROL_H

#include <SDL2/SDL.h>

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
        Control();
        static Mode mode;
        bool GetInput(Character&);
        //FIXME move to editor class
        static EditorTexture GetEditorTexture();
        static TextureCache::iterator editorTextureIt;
    private:
        void CycleEditorTexture(Direction);
        gVec2 editorTexturePos;
        void EditorControl(SDL_Event&);
        void PlayerControl(SDL_Event&, Character&);
};

#endif
