/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_tab_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 15:21:45 by alex              #+#    #+#             */
/*   Updated: 2020/12/06 16:36:39 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "rt.h"

void			option_tab_cont(t_window *win, t_rt *rt,
					t_colors *color, t_all_rect *rect)
{
	char		*str[4];

	if (win == NULL || rt == NULL || color == NULL || rect == NULL)
		rt_error("option_tab_cont(): given NULL pointer");
	get_float_data(rt->options.ambient_illumination, "Ambient_il", str); // get ambient il
	draw_button(win, &rect->fourth_button, str, color); // change ilum data
	free_str(str);
	type_ambien_il(win, rt, rect, color);
	draw_line(win, color, rect->background, rect->sixth_button);
	get_true_data(rt->options.shadows, "Shadows", str); // get shadows
	draw_button(win, &rect->seven_button, str, color);
	free_str(str);
	get_float_data(rt->options.depth, "Depth", str); // get depth
	draw_button(win, &rect->eight_button, str, color);
	free_str(str);
}

void			draw_color_button(t_window *win, t_colors *color,
					t_color fill_color, SDL_Rect *rect)
{
	SDL_Rect	button;

	if (win == NULL || color == NULL || rect == NULL)
		rt_error("draw_color_button(): given NULL pointer");
	if (SDL_SetRenderDrawColor(win->renderer, fill_color.r,
		fill_color.g, fill_color.b, fill_color.a))
		rt_error("draw_color_button(): SDL_SetRenderDrawColor() error");
	button = init_rect_size(rect->x + MARGIN, rect->y,
			rect->w - MARGIN * 2 - 150, rect->h);
	if (SDL_RenderFillRect(win->renderer, &button))
		rt_error("draw_color_button(): SDL_RenderFillRect() error");
	if (SDL_SetRenderDrawColor(win->renderer, color->border_color.r,
	color->border_color.g, color->border_color.b, color->border_color.a))
		rt_error("draw_color_button(): SDL_SetRenderDrawColor() error");
	if (SDL_RenderDrawRect(win->renderer, &button))
		rt_error("draw_color_button(): SDL_RenderDrawRect() error");
}
