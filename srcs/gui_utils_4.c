/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_utils_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 16:02:53 by alex              #+#    #+#             */
/*   Updated: 2020/12/13 03:30:20 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

void			draw_for_button(t_window *win, SDL_Rect *rect, t_colors *color)
{
	SDL_SetRenderDrawColor(win->renderer, color->inside_color.r,
		color->inside_color.g, color->inside_color.b, color->inside_color.a);
	SDL_RenderFillRect(win->renderer, rect);
	SDL_SetRenderDrawColor(win->renderer, color->border_color.r,
		color->border_color.g, color->border_color.b, color->border_color.a);
	SDL_RenderDrawRect(win->renderer, rect);
}
