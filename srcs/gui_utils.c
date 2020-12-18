/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 13:45:42 by user              #+#    #+#             */
/*   Updated: 2020/12/15 22:19:55 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "rt_err.h"

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
	SDL_Texture	*ren_tex;
	SDL_Surface	*surf;
	int			st;
	int			w;
	int			h;

	static int a = 0;

	if (!a)
	{
		IMG_Init(IMG_INIT_JPG);
		a = 1;
	}

	if (g_save_image)
	{
		surf = NULL;
		ren_tex = NULL;
		st = SDL_QueryTexture(win->texture, NULL, NULL, &w, &h);
		surf = SDL_CreateRGBSurfaceWithFormatFrom(image->pixels, w, h,
					SDL_BITSPERPIXEL(SDL_PIXELFORMAT_RGBA32), w *
						SDL_BYTESPERPIXEL(SDL_PIXELFORMAT_RGBA32),
					SDL_PIXELFORMAT_RGBA32);
		if (!surf)
			SDL_Log("Failed creating new surface: %s\n", SDL_GetError());
		st = SDL_SaveBMP(surf, "image.bmp");
		if (st != 0)
			SDL_Log("Failed saving image: %s\n", SDL_GetError());
		if (!(st = IMG_SaveJPG(surf, "test.jpg", 100)))
			exit(00);
		draw_save_image_text(win);
		SDL_FreeSurface(surf);
		SDL_DestroyTexture(ren_tex);
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
	if (SDL_RenderFillRect(win->renderer, rect))
		rt_error("render_tab_bar(): SDL_RenderFillRect() error");
	text = create_tab_subtitles(win, str, color);
	if (SDL_QueryTexture(text, NULL, NULL, &w, &h))
		rt_error("render_tab_bar(): SDL_QueryTexture() error");
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
