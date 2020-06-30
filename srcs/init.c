/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximka <maximka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 18:45:12 by maximka           #+#    #+#             */
/*   Updated: 2020/06/29 17:14:14 by maximka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_light			*init_point(char **elem)
{
	t_light		*light;

	light = (t_light*)malloc(sizeof(t_light));
	light->type = 0;
	light->center.x = ft_atoi_for_float(elem[1]);
	light->center.y = ft_atoi_for_float(elem[2]);
	light->center.z = ft_atoi_for_float(elem[3]);
	light->intensity = ft_atoi_for_float(elem[4]);
	light->next = NULL;
	return (light);
}

t_lvectors		vectors_init(t_shape *shape, t_light *light, t_vector *p,
			t_rtv1 rtv1)
{
	t_lvectors	vectors;

	vectors.p_cap.x = rtv1.cam->x + p->x * shape->t_closest;
	vectors.p_cap.y = rtv1.cam->y + p->y * shape->t_closest;
	vectors.p_cap.z = rtv1.cam->z + p->z * shape->t_closest;
	vectors.l.x = light->center.x - vectors.p_cap.x;
	vectors.l.y = light->center.y - vectors.p_cap.y;
	vectors.l.z = light->center.z - vectors.p_cap.z;
	vectors.n = normal_vector(vectors.p_cap, shape);
	return (vectors);
}

void			sdl_init(t_rtv1 *rtv1)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	rtv1->sdl.win = SDL_CreateWindow("RTv1", 100, 100, WIDTH,
					HEIGHT, SDL_WINDOW_SHOWN);
	rtv1->sdl.render = SDL_CreateRenderer(rtv1->sdl.win, -1,
					SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

void			init_rtv1(t_rtv1 *rtv1, char *name)
{
	int			fd;

	rtv1->shape = NULL;
	rtv1->light = NULL;
	rtv1->dir = NULL;
	rtv1->cam = NULL;
	if ((fd = open(name, O_RDONLY)) == -1)
		incorrect_scene(*rtv1, NULL, NULL);
	rtv1->shape = list_of_shapes(*rtv1, fd);
	rtv1->light = list_of_light(*rtv1, fd);
	rtv1->cam = define_camera(*rtv1, fd);
	rtv1->dir = define_dir(*rtv1, fd);
	close(fd);
	if (!rtv1->dir || !rtv1->cam)
		incorrect_scene(*rtv1, NULL, NULL);
}
