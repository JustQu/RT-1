/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 19:44:32 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/11 20:03:43 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include "rt_options.h"
#include "libft.h"

void	quit(char *s)
{
	printf("%s: %s\n", s, SDL_GetError());
	SDL_Quit();
	exit(1);
}

/*
** @brief
** init sdl window and image buffer
** todo(dmelessa): поменять окно, чтобы оно принимало параметры ширины и высоты.
** @param window
** @return ** int
*/

int		init_window(t_window *window)
{
	window->width = DEFAULT_WIDTH;
	window->height = DEFAULT_HEIGHT;
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		quit("SDL_Init Error");
	if (!(window->ptr = SDL_CreateWindow("<3", SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED, window->width, window->height,
				SDL_WINDOW_RESIZABLE)))
		quit("SDL_CreateWindow Error");
	if (!(window->renderer = SDL_CreateRenderer(window->ptr, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)))
	{
		SDL_DestroyWindow(window->ptr);
		quit("SDL_CreateRenderer Error");
	}
	if (!(window->texture = SDL_CreateTexture(window->renderer,
		SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING,
		IMG_WIDTH, IMG_HEIGHT)))
	{
		SDL_DestroyWindow(window->ptr);
		quit("SDL_CreateTexture Error");
	}
	window->image = (uint32_t *)malloc(sizeof(uint32_t) *
				IMG_WIDTH * IMG_HEIGHT);
	ft_memset(window->image, 0, sizeof(uint32_t) * IMG_WIDTH * IMG_HEIGHT);
	if (!window->image)
		perror("window->image malloc");
	window->rgb_image = (t_color *)malloc(sizeof(t_color) *
											IMG_WIDTH * IMG_HEIGHT);
	ft_memset(window->rgb_image, 0, sizeof(t_color) * IMG_WIDTH * IMG_HEIGHT);
	return (0);
}
