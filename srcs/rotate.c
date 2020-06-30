/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximka <maximka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 14:29:13 by user              #+#    #+#             */
/*   Updated: 2020/06/27 15:45:07 by maximka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	rotate_x_axis(float *y, float *z, double angle_x)
{
	float y_original;

	y_original = *y;
	*y = y_original * cos(angle_x) + *z * sin(angle_x);
	*z = *z * cos(angle_x) - y_original * sin(angle_x);
}

void	rotate_y_axis(float *x, float *z, double angle_y)
{
	float x_original;

	x_original = *x;
	*x = x_original * cos(angle_y) + *z * sin(angle_y);
	*z = *z * cos(angle_y) - x_original * sin(angle_y);
}

void	rotate_z_axis(float *x, float *y, float z)
{
	float	x_original;
	float	y_original;

	x_original = *x;
	y_original = *y;
	*x = x_original * cos(z) - (y_original) * sin(z);
	*y = x_original * sin(z) + (y_original) * cos(z);
}
