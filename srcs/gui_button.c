/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_button.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 10:52:14 by alex              #+#    #+#             */
/*   Updated: 2020/08/28 15:23:33 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "rt.h"

void	draw_ispressed_checkbox(t_rt *rt, SDL_Rect *rect, char *str,
															t_colors *color)
{
	SDL_Texture *text;
	int w;
	int h;

	roundedBoxRGBA(rt->sdl.render, rect->x, rect->y, rect->w, rect->h,
		2, color->tab_pressed_color.r, color->tab_pressed_color.g,
		color->tab_pressed_color.b, 255);
	roundedRectangleRGBA(rt->sdl.render, rect->x - 1, rect->y - 1,
		rect->w + 1, rect->h + 1, 5, 217, 217, 217, 255);
	if (str != 0)
	{
		text = render_text(str, "font/Title.ttf",
		color->tab_pressed_color, FONT_SUBTITLE_SIZE, rt->sdl.render);
		SDL_QueryTexture(text, NULL, NULL, &w, &h);
		render_texture(text, rt->sdl.render, rect->x - w - MARGIN,
			rect->y + h / 2);
	}
}

void	draw_checkbox(t_rt *rt, SDL_Rect *rect, char *str, t_colors *color)
{
	SDL_Texture *text;
	int w;
	int h;

	roundedBoxRGBA(rt->sdl.render, rect->x, rect->y, rect->w, rect->h,
		5, color->preground.r, color->preground.g, color->preground.b, 255);
	roundedRectangleRGBA(rt->sdl.render, rect->x - 1, rect->y - 1,
		rect->w + 1, rect->h + 1, 5, 217, 217, 217, 255);
	if (str != 0)
	{
		text = render_text(str, "font/Title.ttf",
		color->xyz_text_color, FONT_SUBTITLE_SIZE, rt->sdl.render);
		SDL_QueryTexture(text, NULL, NULL, &w, &h);
		render_texture(text, rt->sdl.render, rect->x - w - MARGIN,
			rect->y + h / 2);
	}
}

void	draw_button(t_rt *rt, SDL_Rect *rect, char *str, t_colors *color)
{
	SDL_Texture *text;
	int w;
	int h;

	roundedBoxRGBA(rt->sdl.render, rect->x, rect->y, rect->w, rect->h,
		5, color->preground.r, color->preground.g, color->preground.b, 255);
	roundedRectangleRGBA(rt->sdl.render, rect->x - 1, rect->y - 1,
		rect->w + 1, rect->h + 1, 5, 217, 217, 217, 255);
	if (str != 0)
	{
		text = render_text(str, "font/Title.ttf",
		color->xyz_text_color, FONT_SUBTITLE_SIZE, rt->sdl.render);
		SDL_QueryTexture(text, NULL, NULL, &w, &h);
		render_texture(text, rt->sdl.render, rect->x + w / 2,
			rect->y + HEIGHT_BUTTON + MARGIN_Y);
	}
}
