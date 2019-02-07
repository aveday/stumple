#include <SDL2/SDL2_gfxPrimitives.h>
#include <Box2D/Box2D.h>

#include "Graphics.h"
#include "Entity.h"
#include "Model.h"

static const char* WINDOW_TITLE = "Stumble";

SDL_Renderer* Graphics::renderer;

Graphics::Graphics(Grid &g, double z):
        grid(&g), zoom(z) {

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

void Graphics::MakeAbsolute(int &x, int &y) {
    //TODO account for camera offset here
    x /= zoom;
    y /= zoom;
}

void Graphics::Draw(Editor& editor) {
    //FIXME duplication
    SDL_RenderClear(renderer);
    Draw(*grid);

    if(editor.TextureLoaded) {

        // draw the current texture
        Texture et = editor.GetTexture();
        SDL_Rect dst = {
            (int)(et.pos.x*zoom),
            (int)(et.pos.y*zoom),
            (int)(et.src.w*zoom),
            (int)(et.src.h*zoom)
        };
        SDL_RenderCopyEx(renderer, et.texture, &et.src, &dst,
                0, NULL, SDL_FLIP_NONE);

        // draw boxes for each of the modeldefs
        for(auto it = editor.defs.begin(); it != editor.defs.end(); it++){
            int x1 = (et.pos.x + it->box.x) * zoom;
            int y1 = (et.pos.y + it->box.y) * zoom;
            int x2 = x1 + it->box.w * zoom;
            int y2 = y1 + it->box.h * zoom;
            rectangleColor(renderer, x1, y1, x2, y2, editor.toolColors[BOX]);

            x1 = (et.pos.x + it->shape.x) * zoom;
            y1 = (et.pos.y + it->shape.y) * zoom;
            x2 = x1 + it->shape.w * zoom;
            y2 = y1 + it->shape.h * zoom;
            rectangleColor(renderer, x1, y1, x2, y2, editor.toolColors[SHAPE]);
        }
    }

    for(auto it = editor.entities.begin(); it != editor.entities.end(); it++)
        Draw(*(*it)->body);
    if(editor.grabbed!= nullptr)
        Draw(*editor.grabbed->body);

    SDL_RenderPresent(renderer);
}

void Graphics::Draw(const World &world) {
    // clear the screen
    SDL_RenderClear(renderer);

    // draw grid
    Draw(*grid);

    // draw world
    Draw(*world.body);
    // draw entities
    for(auto it = world.entities.begin(); it != world.entities.end(); it++)
        Draw(*(*it)->body);

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
    //printf(" %.2f, %.2f\n", body.GetPosition().x, body.GetPosition().y);
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
        //printf(" %.2f, %.2f\n", center.x, center.y);

		// draw the fixture sprite
		SDL_RenderCopyEx(renderer, model.texture, &model.srcs.at(i), &dst,
				angle, NULL, SDL_FLIP_NONE);
	}
}
