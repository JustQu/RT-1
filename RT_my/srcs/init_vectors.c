/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vectors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximka <maximka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 13:50:29 by user              #+#    #+#             */
/*   Updated: 2020/06/29 13:40:27 by maximka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_tclose		init_close(t_rtv1 rtv1)
{
	t_tclose	close;

	close.shape = rtv1.shape;
	close.closest_shape = NULL;
	close.t_closest = 0;
	return (close);
}

static void		calculate_cilin(t_vector *n, t_sol *sol,
					t_shape *shape, t_vector p)
{
	n->x = sol->k[0][0] * (sol->k[0][0] * p.x + sol->k[0][1] * p.y +
	sol->k[0][2] * p.z + sol->k[0][3] - shape->cilin->c.x) /
	pow(shape->cilin->a, 2) + sol->k[2][0] * (sol->k[2][0] * p.x +
	sol->k[2][1] * p.y + sol->k[2][2] * p.z + sol->k[2][3] -
	shape->cilin->c.z) / pow(shape->cilin->b, 2);
	n->y = sol->k[0][1] * (sol->k[0][0] * p.x + sol->k[0][1] * p.y +
	sol->k[0][2] * p.z + sol->k[0][3] - shape->cilin->c.x) /
	pow(shape->cilin->a, 2) + sol->k[2][1] * (sol->k[2][0] * p.x +
	sol->k[2][1] * p.y + sol->k[2][2] * p.z + sol->k[2][3] -
	shape->cilin->c.z) / pow(shape->cilin->b, 2);
	n->z = sol->k[0][2] * (sol->k[0][0] * p.x + sol->k[0][1] * p.y +
	sol->k[0][2] * p.z + sol->k[0][3] - shape->cilin->c.x) /
	pow(shape->cilin->a, 2) + sol->k[2][2] * (sol->k[2][0] * p.x +
	sol->k[2][1] * p.y + sol->k[2][2] * p.z + sol->k[2][3] -
	shape->cilin->c.z) / pow(shape->cilin->b, 2);
}

static void		calculate_cone(t_vector *n, t_sol *sol,
				t_shape *shape, t_vector p)
{
	n->x = sol->k[0][0] * (sol->k[0][0] * p.x + sol->k[0][1] * p.y +
	sol->k[0][2] * p.z + sol->k[0][3] - shape->cone->o.x) /
	pow(shape->cone->a, 2) + sol->k[2][0] * (sol->k[2][0] * p.x +
	sol->k[2][1] * p.y + sol->k[2][2] * p.z + sol->k[2][3] -
	shape->cone->o.z) / pow(shape->cone->b, 2) - sol->k[1][0] *
	(sol->k[1][0] * p.x + sol->k[1][1] * p.y + sol->k[1][2] * p.z +
	sol->k[1][3] - shape->cone->o.y) / pow(shape->cone->c, 2);
	n->z = sol->k[0][2] * (sol->k[0][0] * p.x + sol->k[0][1] * p.y +
	sol->k[0][2] * p.z + sol->k[0][3] - shape->cone->o.x) /
	pow(shape->cone->a, 2) + sol->k[2][2] * (sol->k[2][0] * p.x +
	sol->k[2][1] * p.y + sol->k[2][2] * p.z + sol->k[2][3] -
	shape->cone->o.z) / pow(shape->cone->b, 2) - sol->k[1][2] *
	(sol->k[1][0] * p.x + sol->k[1][1] * p.y + sol->k[1][2] * p.z +
	sol->k[1][3] - shape->cone->o.y) / pow(shape->cone->c, 2);
	n->y = sol->k[0][1] * (sol->k[0][0] * p.x + sol->k[0][1] * p.y +
	sol->k[0][2] * p.z + sol->k[0][3] - shape->cone->o.x) /
	pow(shape->cone->a, 2) + sol->k[2][1] * (sol->k[2][0] * p.x +
	sol->k[2][1] * p.y + sol->k[2][2] * p.z + sol->k[2][3] -
	shape->cone->o.z) / pow(shape->cone->b, 2) - sol->k[1][1] *
	(sol->k[1][0] * p.x + sol->k[1][1] * p.y + sol->k[1][2] * p.z +
	sol->k[1][3] - shape->cone->o.y) / pow(shape->cone->c, 2);
}

t_vector		normal_vector_second(t_vector p, t_shape *shape)
{
	t_vector	n;
	t_sol		*sol;

	if (shape->cone)
	{
		sol = &shape->cone->sol;
		calculate_cone(&n, sol, shape, p);
	}
	if (shape->plane)
	{
		n.x = -shape->plane->a;
		n.y = -shape->plane->b;
		n.z = -shape->plane->c;
	}
	return (n);
}

t_vector		normal_vector(t_vector p, t_shape *shape)
{
	t_vector	n;
	t_sol		*sol;

	if (shape->sph)
	{
		n.x = p.x - shape->sph->c.x;
		n.y = p.y - shape->sph->c.y;
		n.z = p.z - shape->sph->c.z;
	}
	if (shape->cilin)
	{
		sol = &shape->cilin->sol;
		calculate_cilin(&n, sol, shape, p);
	}
	if (shape->plane || shape->cone)
		n = normal_vector_second(p, shape);
	return (n);
}
