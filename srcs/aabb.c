/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 19:24:19 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/13 12:53:12 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "matrix.h"
#include "instance_manager.h"
#include "utils.h"
#include "rt_err.h"
#include <stdlib.h>
#include <math.h>

t_matrix		get_transformation_matrix(t_instance_info info)
{
	t_matrix		m;

	m = IDENTITY_MATRIX;
	m = mul_matrix(m, get_translation_matrix(info.origin));
	m = mul_matrix(m, get_rotation_matrix(info.rotation));
	m = mul_matrix(m, get_scale_matrix(info.scaling));
	return (m);
}

t_bbox			transform_aabb(t_bbox aabb, t_matrix matrix)
{
	t_bbox	transformed_aabb;
	int		ij[2];
	float	a;
	float	b;

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

static int		compute_aabb_next1(t_instance_info obj, t_bbox *aabb)
{
	float a;

	if (aabb == NULL)
		rt_error("compute_aabb_next1(): given NULL pointer");
	if (obj.type == disk)
		*aabb = (t_bbox){(cl_float4) {{obj.r, obj.r, obj.r}}, (cl_float4) {{-obj.r,
			-obj.r, -obj.r}}};
	else if (obj.type == box)
		*aabb = (t_bbox){obj.v1, obj.v2};
	else if (obj.type == torus)
		*aabb = (t_bbox){(cl_float4) {{obj.r + obj.r2, obj.r + obj.r2,
			obj.r + obj.r2}}, (cl_float4) {{-obj.r - obj.r2, -obj.r - obj.r2,
			-obj.r - obj.r2}}};
	else if (obj.type == rectangle)
<<<<<<< HEAD
		*aabb = (t_bbox){(cl_float4) {{obj.r + obj.r2, obj.r + obj.r2,
			obj.r2 + obj.r2}}, (cl_float4) {{-obj.r + obj.r2, -obj.r + obj.r2,
			-obj.r + obj.r2}}};
	else if (obj.type == paraboloid)
	{
		a = float_max(float_max(obj.height, 3.0f), obj.r);
		*aabb = (t_bbox){(cl_float4) {{a, a, a}}, (cl_float4) {{-a, -a, -a}}};
=======
		*aabb = (t_bbox){(cl_float4){{obj.r + obj.r2, obj.r + obj.r2,
			obj.r2 + obj.r2}}, (cl_float4){{-obj.r + obj.r2, -obj.r + obj.r2,
			-obj.r + obj.r2}}};
	else if (obj.type == paraboloid)
	{
		a = float_max(float_max(obj.height, 3.0f), obj.r);
		*aabb = (t_bbox){(cl_float4){{a, a, a}}, (cl_float4){{-a, -a, -a}}};
>>>>>>> 581fa4ace2bbb21bea178619ec6657b28324b690
	}
	else
		return (-1);
	return (0);
}

t_bbox			compute_aabb(t_instance_info obj)
{
	t_bbox	aabb;
	float	a;

	if (obj.type == sphere)
<<<<<<< HEAD
		aabb = (t_bbox){(cl_float4) {{1.f, 1.f, 1.f}},
						(cl_float4) {{-1.f, -1.f, -1.f}}};
	else if (obj.type == cylinder)
		aabb = (t_bbox){(cl_float4) {{float_max(obj.r, obj.height),
			float_max(obj.r, obj.height), float_max(obj.r, obj.height)}},
			(cl_float4) {{-float_max(obj.r, obj.height),
			-float_max(obj.r, obj.height), -float_max(obj.r, obj.height)}}};
	else if (obj.type == plane)
		aabb = (t_bbox){(cl_float4) {{1000.0f, 0.0001f, 1000.0f}},
			(cl_float4) {{-1000.0f, 0.0f, -1000.0f}}};
	else if (obj.type == cone)
	{
		a = obj.r2 > 1.0f ? obj.height * obj.r2 : obj.height;
		aabb = (t_bbox){(cl_float4) {{a, a, a}}, (cl_float4) {{-a, -a, -a}}};
	}
	else if (obj.type == triangle)
		aabb = (t_bbox){(cl_float4) {{100.0f, 100.f, 100.0f}},
			(cl_float4) {{-100.0f, 100.f, -100.0f, 0.0f}}};
=======
		aabb = (t_bbox){(cl_float4){{1.f, 1.f, 1.f}},
						(cl_float4){{-1.f, -1.f, -1.f}}};
	else if (obj.type == cylinder)
		aabb = (t_bbox){(cl_float4){{float_max(obj.r, obj.height),
				float_max(obj.r, obj.height), float_max(obj.r, obj.height)}},
			(cl_float4){{-float_max(obj.r, obj.height),
				-float_max(obj.r, obj.height), -float_max(obj.r, obj.height)}}};
	else if (obj.type == plane)
		aabb = (t_bbox){(cl_float4){{1000.0f, 0.0001f, 1000.0f}},
						(cl_float4){{-1000.0f, 0.0f, -1000.0f}}};
	else if (obj.type == cone)
	{
		a = obj.r2 > 1.0f ? obj.height * obj.r2 : obj.height;
		aabb = (t_bbox){(cl_float4){{a, a, a}}, (cl_float4){{-a, -a, -a}}};
	}
	else if (obj.type == triangle)
		aabb = (t_bbox){(cl_float4){{100.0f, 100.f, 100.0f}},
						(cl_float4){{-100.0f, 100.f, -100.0f, 0.0f }}};
>>>>>>> 581fa4ace2bbb21bea178619ec6657b28324b690
	else if (compute_aabb_next1(obj, &aabb))
		rt_error("compute_aabb(): unknown obj type");
	aabb = transform_aabb(aabb, get_transformation_matrix(obj));
	return (aabb);
}
