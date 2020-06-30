/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximka <maximka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 16:48:41 by maximka           #+#    #+#             */
/*   Updated: 2020/06/29 17:28:15 by maximka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		free_elem_line(char **line, char ***elem)
{
	if (line && *line)
	{
		free(*line);
		*line = NULL;
	}
	if (elem && *elem)
	{
		free_elem(*elem);
		*elem = NULL;
	}
}

t_shape		*free_shape(t_shape *shp)
{
	t_shape	*p;

	p = shp->next;
	shp->cilin ? free(shp->cilin) : NULL;
	shp->sph ? free(shp->sph) : NULL;
	shp->plane ? free(shp->plane) : NULL;
	shp->cone ? free(shp->cone) : NULL;
	shp ? free(shp) : NULL;
	return (p);
}

t_light		*free_light(t_light *light)
{
	t_light	*l;

	l = light->next;
	light ? free(light) : NULL;
	return (l);
}

void		free_all(t_rtv1 rtv1)
{
	t_light	*l;
	t_shape	*p;

	p = rtv1.shape;
	rtv1.cam ? free(rtv1.cam) : NULL;
	rtv1.dir ? free(rtv1.dir) : NULL;
	while (p)
		p = free_shape(p);
	l = rtv1.light;
	while (l)
		l = free_light(l);
	SDL_DestroyRenderer(rtv1.sdl.render);
	SDL_DestroyWindow(rtv1.sdl.win);
	SDL_Quit();
	exit(0);
}

void		free_elem(char **elem)
{
	int		i;

	i = 0;
	while (elem[i])
	{
		elem[i] ? free(elem[i]) : NULL;
		elem[i] = NULL;
		i++;
	}
	elem ? free(elem) : NULL;
}
