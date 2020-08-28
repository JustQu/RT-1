#include "gui.h"
#include "rt.h"

void	draw_render_checkbox(t_rt *rt, SDL_Rect *all_rect, t_colors *color, char **str, int count)
{
	SDL_Rect rect;
	int i;


	i = 0;
	rect.x = all_rect->x;
	rect.y = all_rect->y;
	rect.w = all_rect->w;
	rect.h = all_rect->h;
	while (i < count)
	{
		draw_checkbox(rt, &rect, str[i], color);
		rect.y += HEIGHT_BUTTON + MARGIN_Y;
		rect.h += HEIGHT_BUTTON + MARGIN_Y;
		i++;
	}
}


