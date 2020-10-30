/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 13:45:42 by user              #+#    #+#             */
/*   Updated: 2020/10/30 22:20:47 by alex             ###   ########.fr       */
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

void			save_image_func(t_window *win)
{
	if (g_save_image)
	{
		SDL_Texture *ren_tex;
		SDL_Surface *surf;
		int st;
		int w;
		int h;
		int format;
		void *pixels;

		pixels  = NULL;
		surf    = NULL;
		ren_tex = NULL;
		format  = SDL_PIXELFORMAT_RGBA32;

		/* Get information about texture we want to save */
		st = SDL_QueryTexture(win->texture, NULL, NULL, &w, &h);
		if (st != 0) {
			SDL_Log("Failed querying texture: %s\n", SDL_GetError());
		}

		// ren_tex = SDL_CreateTexture(win->renderer, format, SDL_TEXTUREACCESS_TARGET, w, h);
		// if (!ren_tex) {
		// 	SDL_Log("Failed creating render texture: %s\n", SDL_GetError());
		// }

		/*
		* Initialize our canvas, then copy texture to a target whose pixel data we
		* can access
		*/
		// st = SDL_SetRenderTarget(win->renderer, ren_tex);
		// if (st != 0) {
		// 	SDL_Log("Failed setting render target: %s\n", SDL_GetError());
		// }

		// SDL_SetRenderDrawColor(win->renderer, 0x00, 0xFF, 0x00, 0x00);
		// SDL_RenderClear(win->renderer);

		// st = SDL_RenderCopy(win->renderer, win->texture, NULL, NULL);
		// if (st != 0) {
		// 	SDL_Log("Failed copying texture data: %s\n", SDL_GetError());
		// }

		/* Create buffer to hold texture data and load it */
		pixels = malloc(w * h * SDL_BYTESPERPIXEL(format));
		if (!pixels) {
			SDL_Log("Failed allocating memory\n");

		}

		st = SDL_RenderReadPixels(win->renderer, NULL, format, pixels, w * SDL_BYTESPERPIXEL(format));
		if (st != 0) {
			SDL_Log("Failed reading pixel data: %s\n", SDL_GetError());

		}

		/* Copy pixel data over to surface */
		surf = SDL_CreateRGBSurfaceWithFormatFrom(pixels, w, h, SDL_BITSPERPIXEL(format), w * SDL_BYTESPERPIXEL(format), format);
		if (!surf) {
			SDL_Log("Failed creating new surface: %s\n", SDL_GetError());
		}
		/* Save result to an image */
		st = IMG_SavePNG(surf, "image.png");
		if (st != 0) {
			SDL_Log("Failed saving image: %s\n", SDL_GetError());

		}

		SDL_Log("Saved texture as BMP to \"%s\"\n", "image.png");
		SDL_FreeSurface(surf);
		free(pixels);
		SDL_DestroyTexture(ren_tex);
			g_save_image = 0;
		}
}

SDL_Texture		*create_tab_subtitles(t_window *win, char *str,
					SDL_Color *color)
{
	SDL_Texture	*text;

	g_font_size = FONT_SUBTITLE_SIZE;
	text = render_text(str, "font/Title.ttf",
	*color, win->renderer);
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
