/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 19:44:32 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/21 17:52:16 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include "image.h"
#include "libft.h"
#include "rt_error.h"

/*
** @brief
** init sdl window and image buffer
** todo(dmelessa): поменять окно, чтобы оно принимало параметры ширины и высоты.
** @param window
** @return ** int
*/

int		init_window(t_window *const window, t_u32 w, t_u32 h)
{
	SDL_DisplayMode	dm;

	SDL_GetDesktopDisplayMode(0, &dm);
	if (w == 0 || h == 0)
	{
		h = DEFAULT_HEIGHT;
		w = DEFAULT_WIDTH;
	}
	window->height = (t_s32)h > dm.h ? dm.h : h;
	window->width = (t_s32)w > dm.w ? dm.w : w;
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		rt_is_dead(sdl_err, sdl_init_error, -1, "");
	if (SDL_CreateWindowAndRenderer(window->width, window->height,
			SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED, &window->ptr, &window->renderer) == -1)
		rt_is_dead(sdl_err, sdl_create_window_error, -1, "");
	if (!(window->ptr) || !(window->renderer))
		rt_is_dead(sdl_err, sdl_create_window_error, -1, "");
	SDL_SetWindowPosition(window->ptr, SDL_WINDOWPOS_CENTERED,
							SDL_WINDOWPOS_CENTERED);
	SDL_SetWindowTitle(window->ptr, "RT");
	window->texture = SDL_CreateTexture(window->renderer,
					SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, w, h);
	rt_is_dead(sdl_err, sdl_create_window_error, !window->texture, "");
	return (SUCCESS);
}
