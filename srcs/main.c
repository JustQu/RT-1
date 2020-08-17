/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 13:10:39 by maximka           #+#    #+#             */
/*   Updated: 2020/08/17 12:13:36 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <stdio.h>

int     main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
	SDL_Window *win;
	SDL_Renderer *render;
	SDL_Event event;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		printf("Error");
	win = SDL_CreateWindow("Menu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	if (win == NULL)
		printf("Error");
	render = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (render == NULL)
		printf("Error");
	struct nk_context *ctx;
	struct nk_colorf bg;
	

	SDL_RenderPresent(render);
	while (1)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
				exit(0);
		}
	}
	printf("Ok\n");
    return (0);
}
