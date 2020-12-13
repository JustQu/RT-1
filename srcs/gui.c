/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 19:31:43 by alex              #+#    #+#             */
/*   Updated: 2020/12/13 13:33:04 by aapricot         ###   ########.fr       */
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

	if (texture == NULL || renderer == NULL || rect == NULL)
		rt_error("render_rect(): given NULL pointer");
	dst.x = rect->x;
	dst.y = rect->y;
	dst.w = rect->w;
	dst.h = rect->h;
	if (SDL_RenderCopy(renderer, texture, NULL, &dst))
		rt_error("render_rect(): SDL_RenderCopy error");
}

SDL_Texture		*load_texture(char *str, SDL_Renderer *renderer)
{
	SDL_Texture	*texture;
	SDL_Surface	*surf;

	if (str == NULL || renderer == NULL)
		rt_error("load_texture(): given NULL pointer");
	surf = IMG_Load(str);
	if (surf == 0)
		rt_error("load_texture(): You don't have the power");
	texture = SDL_CreateTextureFromSurface(renderer, surf);
	if (texture == NULL)
		rt_error("load_texture(): SDL_CreateTextureFromSurface error");
	return (texture);
}

void			render_texture(SDL_Texture *tex,
					SDL_Renderer *ren, int x, int y)
{
	SDL_Rect	rect;
	int			w;
	int			h;

	if (tex == NULL || ren == NULL)
		rt_error("render_texture(): given NULL pointer");
	if (SDL_QueryTexture(tex, NULL, NULL, &w, &h))
		rt_error("render_texture(): SDL_QueryTexture() error");
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

	if (win == NULL || background == NULL || color == NULL)
		rt_error("draw_fill_rect(): given NULL pointer");
	if (SDL_SetRenderDrawColor(win->renderer, color->r, color->g,
							color->b, color->a))
		rt_error("draw_fill_rect(): SDL_SetRenderDrawColor() error");
	rect.x = background->x;
	rect.y = background->y;
	rect.w = background->w;
	rect.h = background->h;
	if (SDL_RenderFillRect(win->renderer, &rect))
		rt_error("draw_fill_rect(): SDL_RenderFillRect() error");
}

void			gui(t_window *win, t_rt *rt,
					t_all_rect *all_rect, t_colors *color)
{
	// SDL_Texture	*img;
	// int			w;
	// int			h;

	gui_init_title(win, all_rect, color);
	if (g_show_gui)
	{
		if (win->width / 4 >= 210)
		{
			if (SDL_SetRenderDrawColor(win->renderer, 240, 240, 240, 255))
				rt_error("gui(): SDL_SetRenderDrawColor() error");
			draw_fill_rect(win, &all_rect->background,
				&color->background_color);
			if (SDL_SetRenderDrawColor(win->renderer, 43, 43, 45, 0))
				rt_error("gui(): SDL_SetRenderDrawColor() error");
			if (SDL_RenderDrawLine(win->renderer, all_rect->background.x - 1,
			all_rect->background.y, all_rect->background.x - 1,
			all_rect->background.x - 1 + all_rect->background.h))
				rt_error("gui(): SDL_RenderDrawLine() error");
			if (win->height >= 300)
				draw_title_ray_tracing(win, &color->text_color);
			gui_tab_bar(win, rt, all_rect, color);
		}
	}
}
