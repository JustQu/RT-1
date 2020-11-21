/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 13:45:42 by user              #+#    #+#             */
/*   Updated: 2020/10/21 15:35:08 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

SDL_Rect	init_rect_size(int x, int y, int w, int h)
{
	SDL_Rect rect;

	rect.x = x;
	rect.y = y;
	rect.h = h;
	rect.w = w;
	return (rect);
}

SDL_Color	init_color(int r, int g, int b, int a)
{
	SDL_Color color;

	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
	return (color);
}

void		save_image_func(t_window *win)
{
	SDL_Surface surf;

	if (save_image)
	{
		// IMG_SavePNG(&surf, "image.pbg");
		printf("yes bitch \n");
		save_image = 0;
	}

}
