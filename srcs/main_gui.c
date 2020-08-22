/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_gui.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 10:51:59 by alex              #+#    #+#             */
/*   Updated: 2020/08/22 18:56:42 by alex             ###   ########.fr       */
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

int		main_gui(t_rt *rt, t_all_rect *all_rect, t_colors *color)
{
	SDL_Color	text_color;

	TTF_Init();

	text_color.r = 38;
	text_color.g = 38;
	text_color.b = 38;
	text_color.a = 0;

	draw_fill_rect(rt, &all_rect->background, &color->background_color);
	draw_xyz(rt, (FONT_TITLE_SIZE + MARGIN_Y) * 5, &rt->direction, color);
	draw_xyz(rt, (FONT_TITLE_SIZE + MARGIN_Y) * 7 + MARGIN_Y, &rt->center, color);
	draw_xyz(rt, (FONT_TITLE_SIZE + MARGIN_Y) * 9 + MARGIN_Y * 2, &rt->rotate, color);
	roundedRectangleRGBA(rt->sdl.render, WIDTH_OFFSET, 0, WIDTH, HEIGHT, 5, color->border_color.r, color->border_color.g, color->border_color.b, 255);
	vlineRGBA(rt->sdl.render, WIDTH_OFFSET, 0, HEIGHT, color->border_color.r, color->border_color.g, color->border_color.b, 255);
	// draw_gradient(rt->sdl.render, &all_rect->color_picker, color->preground, color->title_text_color);
	draw_titles(rt, &text_color);
	draw_button(rt, &all_rect->color_picker_button, "Color", color); /* colorpicker button */
	draw_button(rt, &all_rect->checkbox_button, 0, color);
	hlineRGBA(rt->sdl.render, WIDTH_OFFSET + MARGIN,WIDTH - MARGIN, (FONT_TITLE_SIZE + MARGIN_Y) * 9 + MARGIN_Y * 4 + HEIGHT_BUTTON, 217, 217, 217, 255);
	hlineRGBA(rt->sdl.render, WIDTH_OFFSET + MARGIN,WIDTH - MARGIN, (FONT_TITLE_SIZE + MARGIN_Y) * 4 - MARGIN_Y, 217, 217, 217, 255);
	return (0);
}
