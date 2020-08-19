#include "gui.h"
#include "rt.h"

void	draw_button(t_rt *rt, SDL_Rect *rect, char *str, t_colors *color)
{
	SDL_Texture *text;
	int w;
	int h;

	roundedBoxRGBA(rt->sdl.render, rect->x, rect->y, rect->w, rect->h,
		5, color->preground.r, color->preground.g, color->preground.b, 255);
	roundedRectangleRGBA(rt->sdl.render, rect->x - 1, rect->y - 1,
		rect->w + 1, rect->h + 1, 5, 217, 217, 217, 255);
	if (str != 0)
	{
		text = render_text(str, "font/Title.ttf",
		color->title_text_color, FONT_SUBTITLE_SIZE, rt->sdl.render);
		SDL_QueryTexture(text, NULL, NULL, &w, &h);
		render_texture(text, rt->sdl.render, rect->x + w / 2, rect->y + 35);
	}
}
