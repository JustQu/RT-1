// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   perlin.c                                           :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2020/10/03 00:31:48 by dmelessa          #+#    #+#             */
// /*   Updated: 2020/10/03 14:38:20 by dmelessa         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// float	drand48();

#include "rt_types.h"
#include "utils.h"
#include "perlin.h"
#include "vector.h"

#include <stdlib.h>
#include <math.h>

// float	ranfloat = perlin_generate();
// int		*perm_x;
// int		*perm_y;
// int		*perm_z;

// float	pelin_noise(cl_float ranfloat, cl_float3 p)
// {
// 	float u = p.x - floor(p.x);
// 	float v = p.y - floor(p.y);
// 	float w = p.z - floor(p.z);
// 	int i = ((int)(4 * p.x)) & 255;
// 	int j = ((int)(4 * p.y)) & 255;
// 	int k = ((int)(4 * p.z)) & 255;
// 	return (ranfloat[perm_x[i] ^ perm_y[j] * perm_z[k]]);
// }

cl_float4	*perlin_generate()
{
	cl_float4	*p = malloc(sizeof(*p) * PERLIN_SIZE);
	for (int i = 0; i < PERLIN_SIZE; i++)
	{
		p[i].w = rand_float();
		p[i].x = -1 + 2 * rand_float();
		p[i].y = -1 + 2 * rand_float();
		p[i].z = -1 + 2 * rand_float();
		// p[i] = norm4(p[i]);
	}
	return p;
}

void	permute(int *p, int n)
{
	for (int i = n - 1; i > 0; i--)
	{
		int target = (int)(rand_float() * (i + 1));
		int	tmp = p[i];
		p[i] = p[target];
		p[target] = tmp;
	}
}

int	*perlin_generate_perm()
{
	int *p = malloc(sizeof(int) * PERLIN_SIZE);

	for (int i = 0; i < PERLIN_SIZE; i++)
	{
		p[i] = i;
	}
	permute(p, PERLIN_SIZE);
	return p;
}