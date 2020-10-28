/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 13:45:42 by user              #+#    #+#             */
/*   Updated: 2020/10/28 20:27:38 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

SDL_Rect		init_rect_size(int x, int y, int w, int h)
{
	SDL_Rect	rect;

	rect.x = x;
	rect.y = y;
	rect.h = h;
	rect.w = w;
	return (rect);
}

SDL_Color		init_color(int r, int g, int b, int a)
{
	SDL_Color	color;

	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
	return (color);
}

void			g_save_image_func(t_window *win)
{
	SDL_Surface	surf;

	if (g_save_image)
	{
		// IMG_SavePNG(&surf, "image.pbg");
		printf("yes bitch \n");
		g_save_image = 0;
	}
}

SDL_Texture		*create_tab_subtitles(t_window *win, char *str,
					SDL_Color *color)
{
	SDL_Texture	*text;

	text = render_text(str, "font/Title.ttf",
	*color, FONT_SUBTITLE_SIZE, win->renderer);
	return (text);
}

void			render_tab_bar(t_window *win, SDL_Color *color,
					SDL_Rect *rect, char *str)
{
	SDL_Texture	*text;
	SDL_Rect	rect1;
	int			w;
	int			h;

	SDL_SetRenderDrawColor(win->renderer, 0, 0, 0, 255);
	SDL_RenderFillRect(win->renderer, rect);
	text = create_tab_subtitles(win, str, color);
	SDL_QueryTexture(text, NULL, NULL, &w, &h);
	if (w <= rect->w)
	{
		rect1.x = rect->x + (rect->w - w) / 2;
		rect1.y = rect->y + rect->h - h;
		rect1.w = w;
		rect1.h = h;
		render_rect(text, win->renderer, &rect1);
	}
	else
	{
		render_rect(text, win->renderer, rect);
	}
}
