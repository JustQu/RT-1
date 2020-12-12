/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_utils_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 16:02:53 by alex              #+#    #+#             */
/*   Updated: 2020/12/09 16:21:32 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "rt_err.h"

void			draw_for_button(t_window *win, SDL_Rect *rect, t_colors *color)
{
	if (SDL_SetRenderDrawColor(win->renderer, color->inside_color.r,
	color->inside_color.g, color->inside_color.b, color->inside_color.a))
		rt_error("draw_button_rect(): SDL_SetRenderDrawColor() error");
	if (SDL_RenderFillRect(win->renderer, rect))
		rt_error("draw_button_rect(): SDL_RenderFillRect() error");
	if (SDL_SetRenderDrawColor(win->renderer, color->border_color.r,
	color->border_color.g, color->border_color.b, color->border_color.a))
		rt_error("draw_button_rect(): SDL_SetRenderDrawColor() error");
	if (SDL_RenderDrawRect(win->renderer, rect))
		rt_error("draw_button_rect(): SDL_RenderDrawRect() error");
}
