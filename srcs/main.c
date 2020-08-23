/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 13:10:39 by maximka           #+#    #+#             */
/*   Updated: 2020/08/23 20:44:30 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "gui.h"
#include <stdio.h>

void	init_rect(t_all_rect *rect)
{
	rect->color_picker_button.x = WIDTH_OFFSET + MARGIN;
	rect->color_picker_button.y = (FONT_TITLE_SIZE + MARGIN_Y) * 9 + MARGIN_Y * 6 + HEIGHT_BUTTON;
	rect->color_picker_button.w = rect->color_picker_button.x + 70;
	rect->color_picker_button.h = rect->color_picker_button.y + HEIGHT_BUTTON;

	rect->background.x = WIDTH_OFFSET;
	rect->background.y = 0;
	rect->background.w = WIDTH_MENU;
	rect->background.h = HEIGHT;

	rect->color_picker.x = WIDTH_OFFSET + MARGIN;
	rect->color_picker.y = 500;
	rect->color_picker.w = WIDTH_MENU - MARGIN * 2;
	rect->color_picker.h = 200;

	rect->checkbox_button.x = WIDTH_OFFSET + MARGIN;
	rect->checkbox_button.y = 500;
	rect->checkbox_button.w = rect->checkbox_button.x + HEIGHT_BUTTON;
	rect->checkbox_button.h = rect->checkbox_button.y + HEIGHT_BUTTON;

	rect->tab_main_button.x = WIDTH_OFFSET + MARGIN;
	rect->tab_main_button.y = (FONT_TITLE_SIZE + MARGIN_Y) * 4 - MARGIN_Y - HEIGHT_BUTTON;
	rect->tab_main_button.w = rect->tab_main_button.x + WIDTH_MENU / 2;
	rect->tab_main_button.h = rect->tab_main_button.y + HEIGHT_BUTTON;

	rect->tab_render_button.x = rect->tab_main_button.w;
	rect->tab_render_button.y = (FONT_TITLE_SIZE + MARGIN_Y) * 4 - MARGIN_Y - HEIGHT_BUTTON;
	rect->tab_render_button.w = rect->tab_render_button.x + WIDTH_MENU / 2;
	rect->tab_render_button.h = rect->tab_render_button.y + HEIGHT_BUTTON;
}

void	init_colors(t_colors *color)
{
	color->preground.r = 255;
	color->preground.g = 255;
	color->preground.b = 255;
	color->preground.a = 0;

	color->title_text_color.r = 0;
	color->title_text_color.g = 0;
	color->title_text_color.b = 0;
	color->title_text_color.a = 0;

	color->border_color.r = 217;
	color->border_color.g = 217;
	color->border_color.b = 217;
	color->border_color.a = 0;

	color->subtitle_xyz_color.r = 36;
	color->subtitle_xyz_color.g = 36;
	color->subtitle_xyz_color.b = 36;
	color->subtitle_xyz_color.a = 0;

	color->xyz_text_color.r = 100;
	color->xyz_text_color.g = 100;
	color->xyz_text_color.b = 100;
	color->xyz_text_color.a = 0;

	color->background_color.r = 242;
	color->background_color.g = 242;
	color->background_color.b = 242;
	color->background_color.a = 0;

	color->tab_pressed_color.r = 106;
	color->tab_pressed_color.g = 30;
	color->tab_pressed_color.b = 239;
	color->tab_pressed_color.a = 0;

	color->green_color.r = 0;
	color->green_color.g = 255;
	color->green_color.b = 0;
	color->green_color.a = 0;
}

int     main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
	t_rt rt;
	t_all_rect all_rect;
	t_colors color;

	init_rect(&all_rect);
	init_colors(&color);
	rt.direction.x = 1.23;
	rt.direction.y = 1.02;
	rt.direction.z = 2.093432;
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		printf("Error");
	IMG_Init(IMG_INIT_PNG);
	rt.sdl.win = SDL_CreateWindow("Menu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	if (rt.sdl.win == NULL)
		printf("Error");
	rt.sdl.render = SDL_CreateRenderer(rt.sdl.win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (rt.sdl.render == NULL)
		printf("Error");
	// SDL_SetRenderDrawColor(rt.sdl.render, 255, 255, 255, 255);
	// SDL_RenderClear(rt.sdl.render);
	main_gui(&rt, &all_rect, &color);
	while (1)
	{
		keyboard(&rt, &all_rect, &color);
	}
	return (0);
}
