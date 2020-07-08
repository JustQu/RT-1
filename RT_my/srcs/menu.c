/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 08:42:21 by user              #+#    #+#             */
/*   Updated: 2020/07/08 19:23:32 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <SDL2/SDL_render.h>
#include <stdio.h>

void	draw_button(t_rtv1 *rtv1)
{
	SDL_Color		color;

	color.a = 255;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	SDL_Texture *rt = render_text("RT", "font/font.ttf",
	color, 50, rtv1->sdl.render);
	render_texture(rt, rtv1->sdl.render, WIDTH - 125, 0);
}

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

void	draw_background(t_rtv1 *rtv1)
{

	SDL_Texture		*background;

	background = load_texture("images/background.png", rtv1->sdl.render);
	render_rect(background, rtv1->sdl.render, WIDTH - 200, 0, 200, HEIGHT);
}

SDL_Texture*		render_text(char *message, char *fontFile,
		SDL_Color color, int fontSize, SDL_Renderer *renderer)
{
		TTF_Font *font;
		SDL_Surface *surf;

		font = TTF_OpenFont(fontFile, fontSize);
		if (font == NULL)
				return NULL;
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

void	draw_text(t_rtv1 *rtv1)
{
	SDL_Color color;

	color.a = 255;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	SDL_Texture *rt = render_text("RT", "font/font.ttf",
	color, 50, rtv1->sdl.render);
	render_texture(rt, rtv1->sdl.render, WIDTH - 125, 0);
	SDL_Texture *camera = render_text("Camera", "font/font.ttf",
	color, 25, rtv1->sdl.render);
	// SDL_Texture *coordinate = render_text("Coordinate", "font/font.ttf",
	// 	color, 25, rtv1->sdl.render);
	SDL_Texture *fps = render_text("FPS", "font/font.ttf",
	color, 25, rtv1->sdl.render);
	render_texture(camera, rtv1->sdl.render, WIDTH - 150, 200);
	// render_texture(coordinate, rtv1->sdl.render, WIDTH - 175, 100);
	render_texture(fps, rtv1->sdl.render, WIDTH - 175, 55);
}

void	draw_menu(t_rtv1 *rtv1, int is_hidden)
{
	SDL_Texture		*down;
	SDL_Texture		*left;
	SDL_Texture		*right;
	SDL_Texture		*up;

	if (!is_hidden)
	{
		draw_background(rtv1);
		draw_text(rtv1);
		up = load_texture("images/up.png", rtv1->sdl.render);
		render_rect(up, rtv1->sdl.render, WIDTH - 100, HEIGHT - 400, 50, 50);
		down = load_texture("images/down.png", rtv1->sdl.render);
		render_rect(down, rtv1->sdl.render, WIDTH - 100, HEIGHT - 350, 50, 50);
		left = load_texture("images/left.png", rtv1->sdl.render);
		render_rect(left, rtv1->sdl.render, WIDTH - 125, HEIGHT - 375, 50, 50);
		right = load_texture("images/right.png", rtv1->sdl.render);
		render_rect(right, rtv1->sdl.render, WIDTH - 75, HEIGHT - 375, 50, 50);
	}
}
