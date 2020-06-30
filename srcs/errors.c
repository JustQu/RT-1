/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 23:41:49 by maximka           #+#    #+#             */
/*   Updated: 2020/06/29 18:50:53 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		incorrect_scene(t_rtv1 rtv1, char **line, char ***elem)
{
	t_light	*light;
	t_shape	*shp;

	shp = rtv1.shape;
	light = rtv1.light;
	ft_putstr("Incorrect scene!\n");
	ft_putstr("You can find example of correct scene in example\n");
	free_elem_line(line, elem);
	while (shp)
		shp = free_shape(shp);
	while (light)
		light = free_light(light);
	rtv1.cam ? free(rtv1.cam) : NULL;
	rtv1.dir ? free(rtv1.dir) : NULL;
	exit(0);
}

void		usage(void)
{
	ft_putstr("Usage : ./Rtv1 <any available scene>\n");
	exit(0);
}
