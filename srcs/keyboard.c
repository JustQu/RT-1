#include "gui.h"
#include "rt.h"

void	event_keyboard(t_rt *rt)
{
	rt = 0;
}

void	keyboard(t_rt *rt, t_all_rect *all_rect, t_colors *color)
{

	while (SDL_PollEvent(&rt->sdl.event))
	{
		if (rt->sdl.event.type == SDL_QUIT || rt->sdl.event.key.keysym.sym == SDLK_ESCAPE)
			exit(0);
		if (rt->sdl.event.type == SDL_KEYDOWN)
		{
			event_keyboard(rt);
		}
		if (rt->sdl.event.type == SDL_MOUSEMOTION || rt->sdl.event.type == SDL_MOUSEBUTTONDOWN)
		{
			mouse_move(rt, all_rect, color);
		}
	}
	SDL_RenderPresent(rt->sdl.render);
}
