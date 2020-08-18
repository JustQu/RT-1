/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 13:10:39 by maximka           #+#    #+#             */
/*   Updated: 2020/08/18 17:25:42 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "gui.h"
#include <stdio.h>

int     main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
	t_rt rt;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		printf("Error");
	rt.sdl.win = SDL_CreateWindow("Menu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	if (rt.sdl.win == NULL)
		printf("Error");
	rt.sdl.render = SDL_CreateRenderer(rt.sdl.win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (rt.sdl.render == NULL)
		printf("Error");
	main_gui(&rt);
	SDL_RenderPresent(rt.sdl.render);
	while (1)
	{
		while (SDL_PollEvent(&rt.sdl.event))
		{
			if (rt.sdl.event.type == SDL_QUIT || rt.sdl.event.key.keysym.sym == SDLK_ESCAPE)
				exit(0);
		}
	}
	printf("Ok\n");
    return (0);
}
