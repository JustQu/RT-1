/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 19:24:19 by dmelessa          #+#    #+#             */
/*   Updated: 2020/11/14 20:18:52 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "matrix.h"
#include "instance_manager.h"
#include "utils.h"

#include <stdlib.h>


float	ft_max(float a, float b)
{
	return a > b ? a : b;
}

float	ft_min(float a, float b)
{
	return a > b ? b : a;
}

t_matrix	get_transformation_matrix(t_instance_info info)
{
	t_matrix		m;

	m = IDENTITY_MATRIX;
	m = mul_matrix(m, get_translation_matrix(info.origin));
	m = mul_matrix(m, get_rotation_matrix(info.rotation));
	m = mul_matrix(m, get_scale_matrix(info.scaling));
	return (m);
}

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
	while (ij[0] < 3)
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
	return (transformed_aabb);
}


//TODO: norminette, triangle aabb
t_bbox compute_aabb(t_instance_info obj)
{
	t_bbox			aabb;
	t_instance		instance;
	float			a;

	if (obj.type == sphere)
	{
		aabb.max = (cl_float4){.x = 1.0f, .y = 1.0f, .z = 1.0f, .w = 0.0f};
		aabb.min = (cl_float4){.x = -1.0f, .y = -1.0f, .z = -1.0f, .w = 0.0f};
	}
	else if (obj.type == cylinder)
	{
		aabb.max = (cl_float4){ .x = float_max(obj.r, obj.height),
								.y = float_max(obj.r, obj.height),
								.z = float_max(obj.r, obj.height),
								.w = 0.0f };
		aabb.min = (cl_float4){ .x = -float_max(obj.r, obj.height),
								.y = -float_max(obj.r, obj.height),
								.z = -float_max(obj.r, obj.height),
								.w = 0.0f };
	}
	else if (obj.type == plane)
	{
		aabb.max = (cl_float4){ .x = 100.0f, .y = 100.0f, .z = 100.0f,
								.w = 0.0f };
		aabb.min = (cl_float4){ .x = -100.0f, .y = -100.0f, .z = -100.0f,
								.w = 0.0f };
	}
	else if (obj.type == cone)
	{
		a = obj.height;
		if (obj.r2 > 1.0f)
			a = obj.height * obj.r2;
		aabb.max = (cl_float4){ .x = a, .y = a, .z = a, .w = 0.0f };
		aabb.min = (cl_float4){ .x = -a, .y = -a, .z = -a, .w = 0.0f };
	}
	else if (obj.type == triangle)
	{
		aabb.max = (cl_float4){.x = 100.0f,
							   .y = 100.f,
							   .z = 100.0f,
							   .w = 0.0f};
		aabb.min = (cl_float4){.x = -100.0f,
							   .y = -100.f,
							   .z = -100.0f,
							   .w = 0.0f};
	}
	else if (obj.type == disk)
	{
		aabb.max = (cl_float4){ .x = obj.r, .y = obj.r, .z = obj.r, .w = 0.0f };
		aabb.min = (cl_float4){ .x = -obj.r, .y = -obj.r,
								.z = -obj.r, .w = 0.0f };
	}
	else if (obj.type == box)
	{
		aabb.max = obj.v1;
		aabb.min = obj.v2;
	}
	else if (obj.type == torus)
	{
		aabb.max = (cl_float4){.x = obj.r + obj.r2, .y = obj.r + obj.r2, .z = obj.r + obj.r2, .w = 0.0f};
		aabb.min = (cl_float4){.x = -obj.r - obj.r2, .y = -obj.r - obj.r2, .z = -obj.r - obj.r2, .w = 0.0f};
	}
	else if (obj.type == rectangle)
	{
		aabb.min = (cl_float4){ .x = 0.0f, .y = 0.0f, .z = -0.1f, .w = 0.0f };
		aabb.max = (cl_float4){ .x = obj.r + obj.r2, .y = obj.r + obj.r2,
								.z = obj.r + obj.r2, .w = 0.0f};
	}
	else if (obj.type == paraboloid)
	{
		a = float_max(obj.height, 3.0f);
		a = float_max(a, obj.r);
		aabb.max = (cl_float4){.x = a, .y = a, .z = a, .w = 0.0f};
		aabb.min = (cl_float4){.x = -a, .y = -a, .z = -a, .w = 0.0f};
	}
	else if (obj.type == mobius)
	{
		a = obj.r + obj.r2;
		aabb.max = (cl_float4){.x = a, .y = a, .z = a, .w = 0.0f};
		aabb.min = (cl_float4){.x = -a, .y = -a, .z = -a, .w = 0.0f};
	}
	aabb = transform_aabb(aabb, get_transformation_matrix(obj));
	return (aabb);
}
