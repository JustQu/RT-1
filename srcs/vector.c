/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 00:14:36 by dmelessa          #+#    #+#             */
/*   Updated: 2020/08/13 01:14:16 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "math.h"

/**
** @brief Normalize vector
**
** @param vec
** @return ** cl_float4
*/
cl_float4	norm4(cl_float4 vec)
{
	float	magnitude;

	magnitude = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	vec.x = vec.x / magnitude;
	vec.y = vec.y / magnitude;
	vec.z = vec.z / magnitude;
	return (vec);
}

/**
** @brief cross product of two vectors
**
** @param a
** @param b
** @return ** cl_float4
*/
cl_float4	cross_product(cl_float4 a, cl_float4 b)
{
	cl_float4 c;

	c.x = a.y * b.z - a.z * b.y;
	c.y = -a.x * b.z + a.z * b.x;
	c.z = a.x * b.y - a.y * b.x;
	return (c);
}
