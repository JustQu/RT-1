/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_progress_bar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 20:23:14 by user              #+#    #+#             */
/*   Updated: 2020/08/23 21:16:22 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "gui.h"
#include <time.h>

void	progress_bar(t_rt *rt, t_colors *color, t_all_rect *all_rect)
{
	clock_t start;
	float	res;
	all_rect->tab_main_button = all_rect->tab_main_button;

	start = clock();
	res = WIDTH_OFFSET + start / 10000;
	if (res <= WIDTH)
	{
		roundedBoxRGBA(rt->sdl.render, WIDTH_OFFSET, 0, WIDTH,
			7, 2, 217, 217, 217, 255);
		roundedBoxRGBA(rt->sdl.render, WIDTH_OFFSET, 0, res,
			7, 2, 106, 30, 239, 255);
	}
	else
	{
		roundedBoxRGBA(rt->sdl.render, WIDTH_OFFSET, 0, WIDTH,
			7, 2, 217, 217, 217, 255);
		roundedBoxRGBA(rt->sdl.render, WIDTH_OFFSET, 0,
			WIDTH, 7, 2, 0, 255, 0, 255);
		draw_title_ray_tracing(rt, &color->green_color);
	}
}
