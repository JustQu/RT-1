/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximka <maximka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 20:23:56 by maximka           #+#    #+#             */
/*   Updated: 2020/06/29 15:34:57 by maximka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double			solution(t_shape *shape1, t_vector p, t_vector l)
{
	double		t;

	if (shape1->sph)
		t = solution_of_sphere(shape1->sph, &p, &l);
	if (shape1->cone)
		t = solution_of_cone(shape1->cone, &p, &l);
	if (shape1->cilin)
		t = solution_of_cilin(shape1->cilin, &p, &l);
	if (shape1->plane)
		t = solution_of_plane(shape1->plane, &p, &l);
	return (t);
}

static int		shadow_warrior(t_vector p, t_vector l, t_rtv1 rtv1)
{
	t_shape		*shadow_shape;
	t_shape		*shape1;
	double		t;
	double		t_closest;

	shadow_shape = NULL;
	shape1 = rtv1.shape;
	t_closest = 0;
	while (shape1)
	{
		t = solution(shape1, p, l);
		if (t > 0.0001 && t < 0.99 && (t < t_closest || t_closest == 0))
		{
			shadow_shape = shape1;
			t_closest = t;
		}
		shape1 = shape1->next;
	}
	if (shadow_shape != NULL)
		return (0);
	return (1);
}

static float	specular(t_lvectors vectors,
				t_shape *shape, float i, t_vector *p)
{
	float		res;

	res = 0;
	if (shape->specular > 0)
	{
		vectors.r.x = 2 * vectors.n.x *
				scal(vectors.n, vectors.l) - vectors.l.x;
		vectors.r.y = 2 * vectors.n.y *
				scal(vectors.n, vectors.l) - vectors.l.y;
		vectors.r.z = 2 * vectors.n.z *
				scal(vectors.n, vectors.l) - vectors.l.z;
		vectors.v.x = -(p->x);
		vectors.v.y = -(p->y);
		vectors.v.z = -(p->z);
		res = i * pow(scal(vectors.r, vectors.v) /
		vec_len(vectors.r) / vec_len(vectors.v), shape->specular);
	}
	return (res);
}

float			light_shape(t_light *light,
				t_shape *shape, t_vector *p, t_rtv1 rtv1)
{
	float		i;
	float		n_dot_l;
	t_lvectors	vectors;

	i = 0;
	vectors = vectors_init(shape, light, p, rtv1);
	if (!shadow_warrior(vectors.p_cap, vectors.l, rtv1))
		return (0);
	n_dot_l = scal(vectors.l, vectors.n);
	if (n_dot_l > 0)
		i += light->intensity *
			(n_dot_l / vec_len(vectors.n) / vec_len(vectors.l));
	else
		return (0);
	i += specular(vectors, shape, i, p);
	return (i);
}

float			add_light(t_light *light,
			t_shape *shape, t_vector *p, t_rtv1 rtv1)
{
	float		i;

	i = 0.0;
	if (!shape)
		return (i);
	else
	{
		i = light_shape(light, shape, p, rtv1);
	}
	return (i);
}
