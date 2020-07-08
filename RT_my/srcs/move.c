/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 20:26:20 by user              #+#    #+#             */
/*   Updated: 2020/07/08 19:24:06 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"


static int		is_it_correct_key(t_rtv1 rtv1)
{
	if (rtv1.sdl.event.key.keysym.sym == SDLK_d)
		return (1);
	if (rtv1.sdl.event.key.keysym.sym == SDLK_w)
		return (1);
	if (rtv1.sdl.event.key.keysym.sym == SDLK_a)
		return (1);
	if (rtv1.sdl.event.key.keysym.sym == SDLK_s)
		return (1);
	if (rtv1.sdl.event.key.keysym.sym == SDLK_1)
		return (1);
	if (rtv1.sdl.event.key.keysym.sym == SDLK_2)
		return (1);
	if (rtv1.sdl.event.key.keysym.sym == SDLK_3)
		return (1);
	return (0);
}

static void		what_is_the_key(t_rtv1 *rtv1)
{
	if (rtv1->sdl.event.key.keysym.sym == SDLK_d)
		rtv1->cam->x += 0.1;
	if (rtv1->sdl.event.key.keysym.sym == SDLK_a)
		rtv1->cam->x -= 0.1;
	if (rtv1->sdl.event.key.keysym.sym == SDLK_w)
		rtv1->cam->z += 0.1;
	if (rtv1->sdl.event.key.keysym.sym == SDLK_s)
		rtv1->cam->z -= 0.1;
}

void			keyboard(t_rtv1 rtv1)
{
	int is_hidden;

	is_hidden = 0;
	while (1)
	{
		while (SDL_PollEvent(&rtv1.sdl.event))
		{
			if (rtv1.sdl.event.type == SDL_QUIT)
				free_all(rtv1);
			if (rtv1.sdl.event.type == SDL_KEYDOWN &&
				rtv1.sdl.event.key.keysym.sym == SDLK_ESCAPE)
				free_all(rtv1);
			if (rtv1.sdl.event.type == SDL_MOUSEBUTTONDOWN && is_hidden == 0)
			{
				if ((rtv1.sdl.event.motion.x >= WIDTH - 200 && rtv1.sdl.event.motion.x <= WIDTH) &&
					rtv1.sdl.event.motion.y >= 0 && rtv1.sdl.event.motion.y <= 50)
				{
					draw_menu(&rtv1, is_hidden);
					is_hidden = 1;
				}
			}
			else if (rtv1.sdl.event.type == SDL_MOUSEBUTTONDOWN && is_hidden == 1)
			{
				draw(rtv1);
				draw_button(&rtv1);
				is_hidden = 0;
			}
			if (rtv1.sdl.event.type == SDL_KEYDOWN && is_it_correct_key(rtv1))
			{
				if (rtv1.sdl.event.key.keysym.sym == SDLK_1)
					rtv1.angle_x += 0.1;
				if (rtv1.sdl.event.key.keysym.sym == SDLK_2)
					rtv1.angle_y += 0.1;
				if (rtv1.sdl.event.key.keysym.sym == SDLK_3)
					rtv1.angle_z += 0.1;
				what_is_the_key(&rtv1);
				draw(rtv1);

			}
			SDL_RenderPresent(rtv1.sdl.render);
		}
	}
}
