#include "rt.h"
#include "gui.h"

void	mouse_move(t_rt *rt, t_all_rect *all_rect, t_colors *color)
{
	if (rt->sdl.event.type == SDL_MOUSEMOTION)
	{
		rt->direction.x = rt->sdl.event.motion.x;
		rt->direction.y = rt->sdl.event.motion.y;
		main_gui(rt, all_rect, color);
	}
}
