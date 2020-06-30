/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximka <maximka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 14:53:11 by user              #+#    #+#             */
/*   Updated: 2020/06/29 15:36:11 by maximka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_color			set_color(void)
{
	t_color		color;

	color.r = 0;
	color.g = 0;
	color.b = 0;
	color.a = 0;
	return (color);
}

t_vector		p_vector(t_rtv1 rtv1, int x, int y)
{
	t_vector	p;

	p.x = 0 + (x - WIDTH / 2) / (double)WIDTH;
	p.y = 0 + (y - HEIGHT / 2) / (double)HEIGHT;
	p.z = 1;
	rotate_x_axis(&p.y, &p.z, rtv1.angle_x);
	rotate_y_axis(&p.x, &p.z, rtv1.angle_y);
	rotate_z_axis(&p.x, &p.y, rtv1.angle_z);
	p.l = vec_len(p);
	norm_vec(&p);
	p.l = vec_len(p);
	return (p);
}

t_plight		ft_plight(t_plight light, char **elem)
{
	if (light.start == NULL)
	{
		light.start = init_point(elem);
		light.light = light.start;
	}
	else
	{
		light.light->next = init_point(elem);
		light.light = light.light->next;
	}
	return (light);
}
