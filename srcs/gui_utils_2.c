/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:54:26 by alex              #+#    #+#             */
/*   Updated: 2020/10/28 19:55:17 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

void			draw_text(t_window *win, SDL_Rect *rect,
					char *str, t_colors *color)
{
	SDL_Texture	*text;
	SDL_Rect	ptr;
	int			w;
	int			h;

	text = render_text(str, "font/Title.ttf",
		color->text_color, FONT_TEXT, win->renderer);
	SDL_QueryTexture(text, NULL, NULL, &w, &h);
	ptr.x = rect->x + MARGIN;
	ptr.y = rect->y + rect->h / 2 - h / 2;
	ptr.w = w;
	ptr.h = h;
	render_rect(text, win->renderer, &ptr);
}
