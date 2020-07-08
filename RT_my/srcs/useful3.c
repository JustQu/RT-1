/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximka <maximka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 12:18:28 by user              #+#    #+#             */
/*   Updated: 2020/06/29 15:23:52 by maximka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double			rad(float degree)
{
	double		radian;

	radian = (double)(degree / 180 * PI);
	return (radian);
}

int				is_it_in_cone(t_cone *cone, t_vector *cam)
{
	if (pow((cam->x - cone->o.x), 2) / pow(cone->a, 2) +
	pow((cam->z - cone->o.z), 2) / pow(cone->b, 2) -
	pow((cam->y - cone->o.y), 2) / pow(cone->c, 2) < 1)
		return (1);
	return (0);
}

float			choose_t(float t1, float t2)
{
	if (t1 < t2 && t1 > 0)
		return (t1);
	return (t2);
}
