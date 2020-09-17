/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 13:10:39 by maximka           #+#    #+#             */
/*   Updated: 2020/09/15 18:12:05 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "gui.h"
#include "julia.h"
#include <stdio.h>

SDL_Rect	init_rect_size(int x, int y, int w, int h)
{
	SDL_Rect rect;

	rect.x = x;
	rect.y = y;
	rect.h = h;
	rect.w = w;
	return (rect);
}

void	init_rect(t_all_rect *rect)
{
	 rect->color_picker_button = init_rect_size(WIDTH_OFFSET + MARGIN,
		(FONT_TITLE_SIZE + MARGIN_Y) * 9 + MARGIN_Y * 6 + HEIGHT_BUTTON,
		rect->color_picker_button.x + 70,
		rect->color_picker_button.y + HEIGHT_BUTTON);

	rect->background = init_rect_size(WIDTH_OFFSET, 0, WIDTH_MENU, HEIGHT);

	rect->color_picker = init_rect_size(WIDTH_OFFSET + MARGIN, 500, WIDTH_MENU - MARGIN * 2, 200);

	rect->checkbox_button_shadow = init_rect_size(WIDTH_OFFSET + WIDTH_MENU / 2 - HEIGHT_BUTTON - MARGIN,
										(FONT_TITLE_SIZE + MARGIN_Y) * 4 + MARGIN_Y,
										WIDTH_OFFSET + WIDTH_MENU / 2 - HEIGHT_BUTTON - MARGIN + HEIGHT_BUTTON,
										(FONT_TITLE_SIZE + MARGIN_Y) * 4 + MARGIN_Y + HEIGHT_BUTTON);

	rect->checkbox_button_ambient = init_rect_size(WIDTH - MARGIN - HEIGHT_BUTTON,
		(FONT_TITLE_SIZE + MARGIN_Y) * 4 + MARGIN_Y, WIDTH - MARGIN - HEIGHT_BUTTON + HEIGHT_BUTTON,
		(FONT_TITLE_SIZE + MARGIN_Y) * 4 + MARGIN_Y + HEIGHT_BUTTON);

	rect->specular_button_10 = init_rect_size(WIDTH - MARGIN - HEIGHT_BUTTON, ((FONT_TITLE_SIZE + MARGIN_Y) * 4 + MARGIN_Y) * 2 + MARGIN_Y * 6,
		WIDTH - MARGIN - HEIGHT_BUTTON + HEIGHT_BUTTON, ((FONT_TITLE_SIZE + MARGIN_Y) * 4 + MARGIN_Y) * 2 + MARGIN_Y * 6 + HEIGHT_BUTTON);

	rect->tab_main_button = init_rect_size(WIDTH_OFFSET + MARGIN, (FONT_TITLE_SIZE + MARGIN_Y) * 4 - MARGIN_Y - HEIGHT_BUTTON,
		WIDTH_OFFSET + MARGIN + WIDTH_MENU / 2, (FONT_TITLE_SIZE + MARGIN_Y) * 4 - MARGIN_Y - HEIGHT_BUTTON + HEIGHT_BUTTON);

	rect->tab_render_button = init_rect_size(rect->tab_main_button.w, (FONT_TITLE_SIZE + MARGIN_Y) * 4 - MARGIN_Y - HEIGHT_BUTTON,
		rect->tab_main_button.w + WIDTH_MENU / 2, (FONT_TITLE_SIZE + MARGIN_Y) * 4 - MARGIN_Y - HEIGHT_BUTTON + HEIGHT_BUTTON);

	rect->fractol_button = init_rect_size(WIDTH_OFFSET + MARGIN, (FONT_TITLE_SIZE + MARGIN_Y) * 9 + MARGIN_Y * 4 + HEIGHT_BUTTON * 2,
		WIDTH - MARGIN, (FONT_TITLE_SIZE + MARGIN_Y) * 9 + MARGIN_Y * 4 + HEIGHT_BUTTON * 3);
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

	//init rt
	rt.direction.x = 1.23;
	rt.direction.y = 1.02;
	rt.direction.z = 2.093432;
	rt.center.x = 0.23;
	rt.center.y = 1.22;
	rt.center.z = 5.393432;
	rt.rotate.x = 30;
	rt.rotate.y = 45;
	rt.rotate.z = 90;
	rt.is_pressed.shadow = 1;
	rt.is_pressed.and_more = 0;
	rt.is_pressed.specular = 0;
	rt.is_pressed.ambient = 1;
	rt.is_pressed.render_tab = 0;
	rt.is_pressed.main_tab = 0;


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
		SDL_RenderPresent(rt.sdl.render);
	}
	SDL_Quit();
	return (0);
}
