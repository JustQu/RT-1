/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qjulia_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 16:07:23 by user              #+#    #+#             */
/*   Updated: 2020/11/08 14:50:46 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "julia.h"

void	update_color(float t[4], float a[4], float b[4])
{
	*t += 0.01f;
	if (*t >= 1.0f)
	{
		*t = 0.0f;
		a[0] = b[0];
		a[1] = b[1];
		a[2] = b[2];
		a[3] = b[3];
		random_color(b);
	}
}

int		divide_up(int a, int b)
{
	return ((a % b) != 0) ? (a / b + 1) : (a / b);
}

void	interpolate(float m[4], float t, float a[4], float b[4])
{
	int i;

	i = 0;
	while (i < 4)
	{
		m[i] = (1.0f - t) * a[i] + t * b[i];
		i++;
	}
}

void	update_mu(float t[4], float a[4], float b[4])
{
	uint seed;

	*t += 0.01f;
	seed = (uint)mach_absolute_time();
	if (*t >= 1.0f)
	{
		*t = 0.0f;
		a[0] = b[0];
		a[1] = b[1];
		a[2] = b[2];
		a[3] = b[3];
		b[0] = 2.0f * rand_r(&seed) / (float)RAND_MAX - 1.0f;
		b[1] = 2.0f * rand_r(&seed) / (float)RAND_MAX - 1.0f;
		b[2] = 2.0f * rand_r(&seed) / (float)RAND_MAX - 1.0f;
		b[3] = 2.0f * rand_r(&seed) / (float)RAND_MAX - 1.0f;
	}
}

void	random_color(float v[4])
{
	uint seed;

	seed = (uint)mach_absolute_time();
	v[0] = 5.0f * rand_r(&seed) / (float)RAND_MAX - 1.0f;
	v[1] = 5.0f * rand_r(&seed) / (float)RAND_MAX - 1.0f;
	v[2] = 5.0f * rand_r(&seed) / (float)RAND_MAX - 1.0f;
	v[3] = 1.0f;
}
