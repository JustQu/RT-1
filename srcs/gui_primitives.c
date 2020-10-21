/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_primitives.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 15:35:22 by user              #+#    #+#             */
/*   Updated: 2020/10/10 15:40:37 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "window.h"

/**
** @brief draw horizontal line
**
** @param x1 - start hline
** @param x2 - end hline (x1 + x2)
** @param y
** @return ** void
*/
void	draw_hline(t_window *win, int x1, int x2, int y, SDL_Color *color)
{
	SDL_SetRenderDrawColor(win->renderer, color->r, color->g, color->b, color->a);
	SDL_RenderDrawLine(win->renderer, x1, y,
			x1 + x2, y);
}

/**
** @brief draw vertical line
**
** @param x
** @param y1 - start hline
** @param y2 - end hline (y1 + y2)
** @return ** void
*/
void	draw_vline(t_window *win, int x, int y1, int y2, SDL_Color *color)
{
	SDL_SetRenderDrawColor(win->renderer, color->r, color->g, color->b, color->a);
	SDL_RenderDrawLine(win->renderer, x, y1,
			x, y1 + y2);
}
