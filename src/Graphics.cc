#include <SDL2/SDL2_gfxPrimitives.h>
#include <Box2D/Box2D.h>

#include "Graphics.h"
#include "Entity.h"
#include "Model.h"
#include "Control.h"

double Graphics::zoom = 1;
static const char* WINDOW_TITLE = "Stumble";

SDL_Renderer* Graphics::renderer;

Graphics::Graphics(double z, Grid &g):
        grid(&g) {

    zoom = z;
    /* init SDL, create window and renderer */
    SDL_Init( SDL_INIT_EVERYTHING );
    window = SDL_CreateWindow(WINDOW_TITLE,
            SCR_X, SCR_Y, SCR_W, SCR_H, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

Graphics::~Graphics() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

//FIXME probably make Editor its own class
// maybe subclass into ModelEditor, CharacterEditor, LevelEditor
void Graphics::DrawEditor() {
    if(Control::editorTextureIt == Model::tCache.end())
        return;
    SDL_Texture *t = Control::editorTextureIt->second;
    int w, h, access;
    uint32_t format;
    SDL_QueryTexture(t, &format, &access, &w, &h);
    SDL_Rect src = {0, 0, w, h};
    SDL_Rect dst = {
        (int)(SCR_W - w*zoom)/2, (int)(SCR_H - h*zoom)/2,
        (int)(w*zoom), (int)(h*zoom) };
    SDL_RenderCopyEx(renderer, t, &src, &dst, 0, NULL, SDL_FLIP_NONE);
}

void Graphics::Draw(const World &world) {
    // clear the screen
    SDL_RenderClear(renderer);

    // draw grid
    Draw(*grid);

    if(Control::mode == RUN) {
        // draw world
        Draw(*world.body);
        // draw entities
        for(auto it = world.entities.begin(); it != world.entities.end(); it++)
            Draw(*(*it)->body);
    }
    else if(Control::mode == EDIT) {
        DrawEditor();
    }

    // display the drawn frame
    SDL_RenderPresent(renderer);
}

void Graphics::Draw(const Grid &g) {
	// draw background and orthogonal lines
    boxColor(renderer, 0, 0, SCR_W, SCR_H, g.background);
    for(int x = 0; x < SCR_W; x += PPM*zoom)
        lineColor(renderer, x, 0, x, SCR_H, g.color);
    for(int y = 0; y < SCR_H; y += PPM*zoom)
        lineColor(renderer, 0, y, SCR_W, y, g.color);
}

void Graphics::Draw(const b2Body &body) {
	float angle = body.GetAngle() / M_PI * 180;

	for(const b2Fixture *f = body.GetFixtureList(); f; f = f->GetNext()) {
		Model &model = *static_cast<Model*>(f->GetUserData());

        //FIXME this is hacky. maybe add a random seed to each body
		// select sprite variant based on fixture pointer value
		int i = (int)(uintptr_t)f / 32 % model.srcs.size();
		SDL_Rect &src = model.srcs.at(i);

		// calculate the destination rectangle
        b2Vec2 center = f->GetAABB(0).GetCenter();
		SDL_Rect dst = {
			(int)(zoom * (center.x * PPM - src.w / 2.0)),
			(int)(zoom * (center.y * PPM - src.h / 2.0)),
			(int)(zoom * src.w),
			(int)(zoom * src.h)
		};

		// draw the fixture sprite
		SDL_RenderCopyEx(renderer, model.texture, &model.srcs.at(i), &dst,
				angle, NULL, SDL_FLIP_NONE);
	}
}
