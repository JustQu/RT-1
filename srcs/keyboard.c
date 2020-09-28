/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 10:51:50 by alex              #+#    #+#             */
/*   Updated: 2020/08/28 16:47:43 by user             ###   ########.fr       */
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
