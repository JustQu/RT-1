#include "rt.h"

void	quit(char *s)
{
	printf("%s: %s\n", s, SDL_GetError());
	SDL_Quit();
	exit(1);
}

/**
** @brief
** init sdl window and image buffer
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
				SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING,
				window->width, window->height)))
	{
		SDL_DestroyWindow(window->ptr);
		quit("SDL_CreateTexture Error");
	}
	window->image = (uint32_t *)malloc(sizeof(uint32_t) *
				window->width * window->height);
	ft_memset(window->image, 0, sizeof(uint32_t) * window->width * window->height);
	if (!window->image)
		perror("window->image malloc");

	window->rgb_image = (t_color *)malloc(sizeof(t_color) * window->width * window->height);
	ft_memset(window->rgb_image, 0, sizeof(t_color) * window->width * window->height);
	return (0);
}
