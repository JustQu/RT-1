#include "gui.h"
#include "rt.h"

void draw_gradient(SDL_Renderer * renderer,
		SDL_Rect *back_rect, const SDL_Color c1, const SDL_Color c2)
{
	int i;
	SDL_Color start;
	SDL_Color end;
	SDL_Rect rect;
    float yt;
	float ys;
	yt = back_rect->y;
    start.r = c1.r;
    start.g = c1.g;
    start.b = c1.b;
    start.a = c1.a;
	ys = back_rect->h / COLOR_STEP;
    end.r = (c2.r - c1.r) / COLOR_STEP;
    end.g = (c2.g - c1.g) / COLOR_STEP;
    end.b = (c2.b - c1.b) / COLOR_STEP;
    end.a = (c2.a - c1.a) / COLOR_STEP;
	i = 0;
	while (i < COLOR_STEP)
	{
		rect.x = back_rect->x;
		rect.y = yt;
		rect.w = back_rect->w;
		rect.h = ys + 1;
		SDL_SetRenderDrawColor(renderer, start.r, start.g, start.b, start.a);
		SDL_RenderFillRect(renderer, &rect);
		yt += ys;
        start.r += end.r;
        start.g += end.g;
        start.b += end.b;
        start.a += end.a;
		i++;
	}
}
