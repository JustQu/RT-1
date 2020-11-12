/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 19:31:43 by alex              #+#    #+#             */
/*   Updated: 2020/11/12 14:35:42 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "gui.h"
#include "window.h"
#include <stdio.h>

void			render_rect(SDL_Texture *texture,
					SDL_Renderer *renderer, SDL_Rect *rect)
{
	SDL_Rect	dst;

	dst.x = rect->x;
	dst.y = rect->y;
	dst.w = rect->w;
	dst.h = rect->h;
	SDL_RenderCopy(renderer, texture, NULL, &dst);
}

SDL_Texture		*load_texture(char *str, SDL_Renderer *renderer)
{
	SDL_Texture	*texture;
	SDL_Surface	*surf;

	surf = IMG_Load(str);
	if (!surf)
	{
		printf("You don't have the power");
		exit(0);
	}
	texture = SDL_CreateTextureFromSurface(renderer, surf);
	return (texture);
}

void			render_texture(SDL_Texture *tex,
					SDL_Renderer *ren, int x, int y)
{
	SDL_Rect	rect;
	int			w;
	int			h;

	SDL_QueryTexture(tex, NULL, NULL, &w, &h);
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	render_rect(tex, ren, &rect);
}

void			draw_fill_rect(t_window *win,
					SDL_Rect *background, SDL_Color *color)
{
	SDL_Rect	rect;

	SDL_SetRenderDrawColor(win->renderer, color->r, color->g,
							color->b, color->a);
	rect.x = background->x;
	rect.y = background->y;
	rect.w = background->w;
	rect.h = background->h;
	SDL_RenderFillRect(win->renderer, &rect);
}

void			gui(t_window *win, t_rt *rt,
					t_all_rect *all_rect, t_colors *color)
{
	SDL_Texture	*img;
	int			err;
	int			w;
	int			h;

	err = 0;
	TTF_Init();
	SDL_SetRenderDrawColor(win->renderer, 240, 240, 240, 255);
	draw_fill_rect(win, &all_rect->background, &color->background_color);
	SDL_SetRenderDrawColor(win->renderer, 43, 43, 45, 0);
	SDL_RenderDrawLine(win->renderer, all_rect->background.x - 1,
	all_rect->background.y, all_rect->background.x - 1,
	all_rect->background.x - 1 + all_rect->background.h);
	draw_title_ray_tracing(win, &color->text_color);
	gui_tab_bar(win, rt, all_rect, color);
}
