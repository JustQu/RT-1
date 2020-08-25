/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_gui.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 10:51:59 by alex              #+#    #+#             */
/*   Updated: 2020/08/25 19:33:45 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "gui.h"

#include <stdio.h>

void	render_rect(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y, int w, int h)
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = w;
	dst.h = h;
	SDL_RenderCopy(renderer, texture, NULL, &dst);
}

SDL_Texture*		load_texture(char *str, SDL_Renderer *renderer)
{
	SDL_Texture *texture;

	texture = IMG_LoadTexture(renderer, str);
	if (!texture)
	{
		printf("You don't have the power");
	}
	return texture;
}

void render_texture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y)
{
	int w, h;
	SDL_QueryTexture(tex, NULL, NULL, &w, &h);
	render_rect(tex, ren, x, y, w, h);
}

SDL_Texture*		render_text(char *message, char *fontFile,
		SDL_Color color, int fontSize, SDL_Renderer *renderer)
{
		TTF_Font *font;
		SDL_Surface *surf;


		font = TTF_OpenFont(fontFile, fontSize);
		if (font == NULL)
				printf("not font");
		surf = TTF_RenderText_Blended(font, message, color);
		if (surf == NULL){
				return NULL;
		}
		SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);
		if (texture == NULL){
				return NULL;
		}
		SDL_FreeSurface(surf);
		TTF_CloseFont(font);
		return texture;
}

void	draw_fill_rect(t_rt *rt, SDL_Rect *background, SDL_Color *color)
{
	SDL_Rect rect;

	SDL_SetRenderDrawColor(rt->sdl.render, color->r, color->g,
							color->b, color->a);
	rect.x = background->x;
	rect.y = background->y;
	rect.w = background->w;
	rect.h = background->h;
    SDL_RenderFillRect(rt->sdl.render, &rect);
}

void	draw_render_tab(t_rt *rt, t_all_rect *all_rect, t_colors *color)
{
	draw_button(rt, &all_rect->color_picker_button, "Color", color);
	draw_button(rt, &all_rect->checkbox_button, 0, color);
	draw_gradient(rt->sdl.render, &all_rect->color_picker, color->preground, color->title_text_color);
}

void	draw_main_tab(t_rt *rt, t_all_rect *all_rect, t_colors *color)
{
	all_rect->tab_main_button = all_rect->tab_main_button;
	draw_xyz(rt, (FONT_TITLE_SIZE + MARGIN_Y) * 5, &rt->direction, color);
	draw_xyz(rt, (FONT_TITLE_SIZE + MARGIN_Y) * 7 + MARGIN_Y, &rt->center, color);
	draw_xyz(rt, (FONT_TITLE_SIZE + MARGIN_Y) * 9 + MARGIN_Y * 2, &rt->rotate, color);
	draw_titles(rt, &color->title_text_color);
	hlineRGBA(rt->sdl.render, WIDTH_OFFSET + MARGIN, WIDTH - MARGIN, (FONT_TITLE_SIZE + MARGIN_Y) * 9 + MARGIN_Y * 4 + HEIGHT_BUTTON, 217, 217, 217, 255);
}

void	draw_title_ray_tracing(t_rt *rt, SDL_Color *color)
{
	SDL_Texture *rt_text;
	int w;
	int h;

	rt_text = render_text("Ray Tracing", "font/Title_font_CAT.ttf",
	*color, FONT_TITLE_SIZE * 2, rt->sdl.render);
	SDL_QueryTexture(rt_text, NULL, NULL, &w, &h);
	render_texture(rt_text, rt->sdl.render, WIDTH_OFFSET + WIDTH_MENU / 2 - w / 2, MARGIN_Y * 2);
}

int		main_gui(t_rt *rt, t_all_rect *all_rect, t_colors *color)
{

	TTF_Init();

	SDL_SetRenderDrawColor(rt->sdl.render, 255, 255, 255, 255);
	SDL_RenderClear(rt->sdl.render);

	/* background */
	draw_fill_rect(rt, &all_rect->background, &color->background_color);
	vlineRGBA(rt->sdl.render, WIDTH_OFFSET, 0, HEIGHT, color->border_color.r, color->border_color.g, color->border_color.b, 255);
	roundedRectangleRGBA(rt->sdl.render, WIDTH_OFFSET, 0, WIDTH, HEIGHT, 5, color->border_color.r, color->border_color.g, color->border_color.b, 255);
	draw_title_ray_tracing(rt, &color->title_text_color);
	gui_tab_bar(rt, all_rect, color);
	hlineRGBA(rt->sdl.render, WIDTH_OFFSET + MARGIN, WIDTH - MARGIN, (FONT_TITLE_SIZE + MARGIN_Y) * 4 - MARGIN_Y, 217, 217, 217, 255);

	return (0);
}
