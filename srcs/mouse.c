/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 10:51:39 by alex              #+#    #+#             */
/*   Updated: 2020/08/25 19:16:05 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "gui.h"

int		is_press_button(t_rt *rt, SDL_Rect *rect)
{
	if (rt->sdl.event.type == SDL_MOUSEBUTTONDOWN && rt->sdl.event.motion.y >= rect->y
		&& rt->sdl.event.motion.y <= rect->h
		&& rt->sdl.event.motion.x >= rect->x && rt->sdl.event.motion.x <= rect->w)
		return (1);
	else
		return (0);
}



void	mouse_move(t_rt *rt, t_all_rect *all_rect, t_colors *color)
{
	if (is_press_button(rt, &all_rect->tab_main_button))
	{
		main_gui(rt, all_rect, color);
		draw_main_tab(rt, all_rect, color);
		color_tab_main(rt, color, all_rect);
	}
	if (is_press_button(rt, &all_rect->tab_render_button))
	{
		main_gui(rt,all_rect, color);
		draw_render_tab(rt, all_rect, color);
		color_tab_render(rt, color, all_rect);
	}
	if (is_press_button(rt, &all_rect->checkbox_button))
	{

	}
}
