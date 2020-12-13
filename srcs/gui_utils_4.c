/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_utils_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 16:02:53 by alex              #+#    #+#             */
/*   Updated: 2020/12/13 08:33:52 by alex             ###   ########.fr       */
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

void			gui_init_title(t_window *win,
					t_all_rect *all_rect, t_colors *color)
{
	if (win == NULL || all_rect == NULL || color == NULL)
		rt_error("gui(): given NULL pointer");
	if (TTF_Init())
		rt_error("gui(): TTF_Init() error");
	if (win->height >= 300 && win->width >= 200)
		draw_title_ray_tracing(win, &color->text_color);
}
