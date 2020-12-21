/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 13:45:42 by user              #+#    #+#             */
/*   Updated: 2020/12/20 23:17:15 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "rt_error.h"

static t_bool	g_is_init = FALSE;

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

void			draw_save_image_text(t_window *win)
{
	SDL_Texture	*text;
	SDL_Rect	rect;
	SDL_Color	color;
	int			w;
	int			h;

	color = init_color(255, 255, 255, 0);
	g_font_size = FONT_TITLE_SIZE;
	text = render_text("Saved image as image.bmp", "font/Title.ttf",
						color, win->renderer);
	SDL_QueryTexture(text, NULL, NULL, &w, &h);
	rect.x = win->width / 2 - w / 2;
	rect.y = MARGIN_Y;
	rect.w = w;
	rect.h = h;
	render_rect(text, win->renderer, &rect);
}

/*
** todo: pass image
*/

void			save_image_func(t_window *win, t_image *image)
{
	SDL_Surface	*surf;
	int			st;
	int			w;
	int			h;

	if (!g_is_init)
	{
		IMG_Init(IMG_INIT_JPG | IMG_INIT_JPG);
		g_is_init = 1;
	}
	if (g_save_image)
	{
		st = SDL_QueryTexture(win->texture, NULL, NULL, &w, &h);
		surf = SDL_CreateRGBSurfaceWithFormatFrom(image->pixels, w, h,
					SDL_BITSPERPIXEL(SDL_PIXELFORMAT_ABGR8888), w *
						SDL_BYTESPERPIXEL(SDL_PIXELFORMAT_ABGR8888),
					SDL_PIXELFORMAT_ABGR8888);
		if (st = IMG_SaveJPG(surf, "test.jpg", 1000))
			rt_warning(SDL_GetError());
		if (st = SDL_SaveBMP(surf, "image.bmp"))
			rt_warning(SDL_GetError());
		draw_save_image_text(win);
		SDL_FreeSurface(surf);
		g_save_image = 0;
	}
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
