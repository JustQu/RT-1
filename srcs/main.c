/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 13:10:39 by maximka           #+#    #+#             */
/*   Updated: 2020/08/20 10:44:53 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "gui.h"
#include <stdio.h>

void	init_rect(t_all_rect *rect)
{
	rect->color_picker_button.x = WIDTH_OFFSET + MARGIN;
	rect->color_picker_button.y = 400;
	rect->color_picker_button.w = rect->color_picker_button.x + 70;
	rect->color_picker_button.h = 400 + 30;

	rect->background.x = WIDTH_OFFSET;
	rect->background.y = 0;
	rect->background.w = WIDTH_MENU;
	rect->background.h = HEIGHT;

	rect->color_picker.x = WIDTH_OFFSET + MARGIN;
	rect->color_picker.y = 500;
	rect->color_picker.w = WIDTH_MENU - MARGIN * 2;
	rect->color_picker.h = 200;
}

void	init_colors(t_colors *color)
{
	color->preground.r = 255;
	color->preground.g = 255;
	color->preground.b = 255;
	color->preground.a = 0;

	color->title_text_color.r = 128;
	color->title_text_color.g = 128;
	color->title_text_color.b = 128;
	color->title_text_color.a = 0;

	color->border_color.r = 217;
	color->border_color.g = 217;
	color->border_color.b = 217;
	color->border_color.a = 0;

	color->subtitle_xyz_color.r = 36;
	color->subtitle_xyz_color.g = 36;
	color->subtitle_xyz_color.b = 36;
	color->subtitle_xyz_color.a = 0;

	color->xyz_text_color.r = 38;
	color->xyz_text_color.g = 38;
	color->xyz_text_color.b = 38;
	color->xyz_text_color.a = 0;

	color->background_color.r = 242;
	color->background_color.g = 242;
	color->background_color.b = 242;
	color->background_color.a = 0;
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
	rt.sdl.win = SDL_CreateWindow("Menu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	if (rt.sdl.win == NULL)
		printf("Error");
	rt.sdl.render = SDL_CreateRenderer(rt.sdl.win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (rt.sdl.render == NULL)
		printf("Error");
	// SDL_SetRenderDrawColor(rt.sdl.render, 255, 255, 255, 255);
	// SDL_RenderClear(rt.sdl.render);
	main_gui(&rt, &all_rect, &color);
	// SDL_RenderPresent(rt.sdl.render);
	while (1)
	{
		keyboard(&rt, &all_rect, &color);
		// while (SDL_PollEvent(&rt.sdl.event))
		// {
		// 	if (rt.sdl.event.type == SDL_QUIT || rt.sdl.event.key.keysym.sym == SDLK_ESCAPE)
		// 		exit(0);
		// }
	}
	printf("Ok\n");
    return (0);
}
