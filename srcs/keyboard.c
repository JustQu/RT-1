/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 10:51:50 by alex              #+#    #+#             */
/*   Updated: 2020/08/28 16:36:41 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "gui.h"
#include "rt.h"


void	event_keyboard(t_rt *rt, t_all_rect *all_rect, t_colors *color)
{
	if (rt->sdl.event.key.keysym.sym == SDLK_SPACE)
	{
		main_gui(rt, all_rect, color);
		progress_bar(rt, color, all_rect);
		if (rt->is_pressed.render_tab)
		{
			draw_render_tab(rt, all_rect, color);
			color_tab_render(rt, color, all_rect);
		}
		else if (rt->is_pressed.main_tab)
		{
			draw_main_tab(rt, all_rect, color);
			color_tab_main(rt, color, all_rect);
		}
		else
		{
			main_gui(rt, all_rect, color);
		}
	}
}

void	keyboard(t_rt *rt, t_all_rect *all_rect, t_colors *color)
{
	while (SDL_PollEvent(&rt->sdl.event))
	{
		if (rt->sdl.event.type == SDL_QUIT || rt->sdl.event.key.keysym.sym == SDLK_ESCAPE)
			exit(0);
		if (rt->sdl.event.type == SDL_KEYDOWN)
		{
			event_keyboard(rt, all_rect, color);
		}
		if (rt->sdl.event.type == SDL_MOUSEBUTTONDOWN)
		{
			mouse_move(rt, all_rect, color);
		}
	}
}
