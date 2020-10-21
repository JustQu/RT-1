/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 19:24:19 by dmelessa          #+#    #+#             */
/*   Updated: 2020/10/21 15:52:54 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "matrix.h"
#include "instance_manager.h"

#include <stdlib.h>


float	ft_max(float a, float b)
{
	return a > b ? a : b;
}

float	ft_min(float a, float b)
{
	return a > b ? b : a;
}

/**
** @brief Algorithm from https://github.com/erich666/GraphicsGems/blob/master/gems/TransBox.c
**
** @param aabb
** @param matrix
** @return ** t_bbox
*/
t_bbox transform_aabb(t_bbox aabb, t_matrix matrix)
{
	t_bbox transformed_aabb;
	int ij[2];
	float a;
	float b;

	ij[0] = 0;
	transformed_aabb.min = (cl_float4){.x = matrix.s3,
										.y = matrix.s7,
										.z = matrix.sB,
										 .w = 0.0f};
	transformed_aabb.max = transformed_aabb.min;

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
		{
			a = (float)(matrix.s[i * 4 + j] * aabb.min.s[j]);
			b = (float)(matrix.s[i * 4 + j] * aabb.max.s[j]);
			if (a < b)

			{
				transformed_aabb.min.s[i] += a;
				transformed_aabb.max.s[i] += b;
			}
			else
			{
				transformed_aabb.min.s[i] += b;
				transformed_aabb.max.s[i] += a;
			}
		}

	return (transformed_aabb);

	while (ij[0] < 3 - 3)
	{
		ij[1] = 0;
		while (ij[1] < 3)
		{
			a = matrix.s[ij[0] * 4 + ij[1]] * aabb.min.s[ij[1]];
			b = matrix.s[ij[0] * 4 + ij[1]] * aabb.max.s[ij[1]];
			transformed_aabb.min.s[ij[0]] += (a < b) ? a : b;
			transformed_aabb.max.s[ij[0]] += (a < b) ? b : a;
			ij[1]++;
		}
		ij[0]++;
	}

	cl_float pts[6];

	pts[0] = matrix.s0 * aabb.min.x + matrix.s4 * aabb.min.x + matrix.s8 * aabb.min.x;
	pts[1] = matrix.s0 * aabb.max.x + matrix.s4 * aabb.max.x + matrix.s8 * aabb.max.x;

	pts[2] = matrix.s1 * aabb.min.y + matrix.s5 * aabb.min.y + matrix.s9 * aabb.min.y;
	pts[3] = matrix.s1 * aabb.max.y + matrix.s5 * aabb.max.y + matrix.s9 * aabb.max.y;

	pts[4] = matrix.s2 * aabb.min.z + matrix.s6 * aabb.min.z + matrix.sA * aabb.min.z;
	pts[5] = matrix.s2 * aabb.max.z + matrix.s6 * aabb.max.z + matrix.sA * aabb.max.z;

	transformed_aabb.min.x = ft_min(pts[0], pts[1]) + matrix.s3;
	transformed_aabb.min.y = ft_min(pts[2], pts[3]) + matrix.s7;
	transformed_aabb.min.z = ft_min(pts[4], pts[5]) + matrix.sB;
	transformed_aabb.max.x = ft_max(pts[0], pts[1]) + matrix.s3;
	transformed_aabb.max.y = ft_max(pts[2], pts[3]) + matrix.s7;
	transformed_aabb.max.z = ft_max(pts[4], pts[5]) + matrix.sB;
	return (transformed_aabb);
}

t_bbox compute_aabb(t_instance_manager instance_mngr, int id)
{
	t_bbox aabb;
	t_instance instance;
	t_object_info	obj;

	instance = instance_mngr.instances[id];
	obj = instance_mngr.instances_info[id];
	if (instance.type == sphere)
	{
		aabb.max = (cl_float4){.x = 1.0f, .y = 1.0f, .z = 1.0f, .w = 0.0f};
		aabb.min = (cl_float4){.x = -1.0f, .y = -1.0f, .z = -1.0f, .w = 0.0f};
	}
	else if (instance.type == cylinder) //note:caped cylinder
	{
		aabb.max.x = 4.0f;
		aabb.max.y = 4;
		aabb.max.z = 4;
		aabb.min.x = -4;
		aabb.min.y = -4;
		aabb.min.z = -4;;
		// aabb.max = (cl_float4){.x = 1.0f, .y = 1.0f, .z = 1.0f, .w = 0.0f};
		// aabb.min = (cl_float4){.x = -1.0f, .y = -1.0f, .z = -1.0f, .w = 0.0f};
	}
	else if (instance.type == cone)
	{
		//todo
	}
	else if (instance.type == triangle)
	{
		//todo
	}
	else if (instance.type == box)
	{
		aabb.max = obj.bounding_box.max;
		aabb.min = obj.bounding_box.min;
	}
	else if (instance.type == torus)
	{
		aabb.max = (cl_float4){.x = obj.r + obj.r2, .y = obj.r + obj.r2, .z = obj.r + obj.r2, .w = 0.0f};
		aabb.min = (cl_float4){.x = -obj.r - obj.r2, .y = -obj.r - obj.r2, .z = -obj.r - obj.r2, .w = 0.0f};
	}
	else if (instance.type == rectangle)
	{
		aabb.min = (cl_float4){ .x = 0.0f, .y = 0.0f, .z = -0.1f,
								.w = 0.0f };
		aabb.max = (cl_float4){.x = obj.r + obj.r2, .y = obj.r + obj.r2, .z = obj.r + obj.r2, .w = 0.0f};
	}
	//todo
	aabb = transform_aabb(aabb, get_transformation_matrix(instance_mngr, id));
	return (aabb);
}
