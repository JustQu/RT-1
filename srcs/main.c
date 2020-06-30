/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximka <maximka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/04 20:20:04 by maximka           #+#    #+#             */
/*   Updated: 2020/06/29 17:28:22 by maximka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void		light_on_shape(t_color *color, float i)
{
	color->r *= i;
	color->g *= i;
	color->b *= i;
	if (color->r > 255)
		color->r = 255;
	if (color->r < 0)
		color->r = 0;
	if (color->g > 255)
		color->g = 255;
	if (color->g < 0)
		color->g = 0;
	if (color->b > 255)
		color->b = 255;
	if (color->b < 0)
		color->b = 0;
}

void			ft_light(t_rtv1 rtv1, t_shape *closest_shape,
				t_color *color, t_vector p)
{
	t_light		*light;
	float		i;

	i = 0;
	light = rtv1.light;
	while (light)
	{
		i += add_light(light, closest_shape, &p, rtv1);
		light = light->next;
	}
	light_on_shape(color, i);
}

static t_color	get_color(t_rtv1 rtv1, int x, int y)
{
	t_tclose	close;
	t_vector	p;
	t_color		color;

	p = p_vector(rtv1, x, y);
	close = init_close(rtv1);
	while (close.shape)
	{
		close.t = solution(close.shape, *rtv1.cam, p);
		if (close.t > 0.001 && close.t < 1000000 &&
			(close.t < close.t_closest || close.t_closest == 0))
		{
			close.closest_shape = close.shape;
			close.t_closest = close.t;
			close.closest_shape->t_closest = close.t;
			color = take_color(close.shape);
		}
		else if (close.t_closest == 0)
		{
			color = set_color();
		}
		close.shape = close.shape->next;
	}
	ft_light(rtv1, close.closest_shape, &color, p);
	return (color);
}

int				draw(t_rtv1 rtv1)
{
	t_color		color;
	int			x;
	int			y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			color = get_color(rtv1, x, y);
			SDL_SetRenderDrawColor(rtv1.sdl.render, color.r,
								color.g, color.b, color.a);
			SDL_RenderDrawPoint(rtv1.sdl.render, x, y);
			x++;
		}
		y++;
	}
	return (0);
}

int				main(int argc, char **argv)
{
	t_rtv1		rtv1;

	if (argc != 2)
		usage();
	init_rtv1(&rtv1, argv[1]);
	average_light(rtv1.light);
	rtv1.angle_x = rad(rtv1.dir->x);
	rtv1.angle_y = rad(rtv1.dir->y);
	rtv1.angle_z = rad(rtv1.dir->z);
	sdl_init(&rtv1);
	draw(rtv1);
	SDL_RenderPresent(rtv1.sdl.render);
	keyboard(rtv1);
	free_all(rtv1);
	return (0);
}
