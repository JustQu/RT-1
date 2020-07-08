/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 14:43:29 by maximka           #+#    #+#             */
/*   Updated: 2020/06/29 17:13:35 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_color			take_color(t_shape *shp)
{
	if (shp->sph)
		return (shp->sph->col);
	if (shp->cone)
		return (shp->cone->col);
	if (shp->plane)
		return (shp->plane->col);
	else
		return (shp->cilin->col);
}

float			solution_of_plane(t_plane *plane, t_vector *cam,
	t_vector *p)
{
	float		t;

	t = -(plane->a * cam->x + plane->b * cam->y +
		plane->c * cam->z + plane->d) /
		(plane->a * p->x + plane->b * p->y + plane->c * p->z);
	if (t >= 0)
		return (t);
	return (1000000);
}

float			solution_of_cilin(t_cilin *cilin, t_vector *cam,
	t_vector *p)
{
	float		t1;
	float		t2;
	t_sol		*sol;

	sol = &cilin->sol;
	fill_sol_cilin(sol, cam, p, cilin);
	sol->a = pow(sol->m[0], 2) / pow(cilin->a, 2) +
		pow(sol->m[1], 2) / pow(cilin->b, 2);
	sol->b = 2 * ((sol->n[0] * sol->m[0] / pow(cilin->a, 2)) +
		(sol->n[1] * sol->m[1] / pow(cilin->b, 2)));
	sol->c = (pow(sol->n[0], 2) / pow(cilin->a, 2) +
		pow(sol->n[1], 2) / pow(cilin->b, 2) - 1);
	sol->d_cap = pow(sol->b, 2) - 4 * sol->a * sol->c;
	if (sol->d_cap < 0)
		return (1000000);
	t1 = (-sol->b + sqrt(sol->d_cap)) / (2 * sol->a);
	t2 = (-sol->b - sqrt(sol->d_cap)) / (2 * sol->a);
	if (t1 > t2 && t1 > 0 && t2 > 0)
		return (t2);
	if (t1 <= t2 && t1 > 0 && t2 > 0)
		return (t1);
	return (1000000);
}

float			solution_of_cone(t_cone *cone, t_vector *cam,
	t_vector *p)
{
	t_sol		*sol;
	float		t1;
	float		t2;

	sol = &cone->sol;
	fill_sol_cone(sol, cam, p, cone);
	sol->a = (pow(sol->m[0], 2) / pow(cone->a, 2) +
		pow(sol->m[1], 2) / pow(cone->b, 2) -
			pow(sol->m[2], 2) / pow(cone->c, 2));
	sol->b = 2 * ((sol->n[0] * sol->m[0]) / pow(cone->a, 2) +
		(sol->n[1] * sol->m[1]) / pow(cone->b, 2) -
			(sol->n[2] * sol->m[2]) / pow(cone->c, 2));
	sol->c = (pow(sol->n[0], 2) / pow(cone->a, 2) + pow(sol->n[1], 2) /
		pow(cone->b, 2) - pow(sol->n[2], 2) / pow(cone->c, 2));
	sol->d_cap = pow(sol->b, 2) - 4 * sol->a * sol->c;
	if (sol->d_cap < 0)
		return (1000000);
	t1 = (-sol->b + sqrt(sol->d_cap)) / (2 * sol->a);
	t2 = (-sol->b - sqrt(sol->d_cap)) / (2 * sol->a);
	if (!is_it_in_cone(cone, cam))
		return (choose_t(t1, t2));
	return (1000000);
}

float			solution_of_sphere(t_sphere *sph, t_vector *cam,
	t_vector *p)
{
	t_sol		*sol;
	float		t1;
	float		t2;

	sol = &sph->sol;
	sol->dx = cam->x - sph->c.x;
	sol->dy = cam->y - sph->c.y;
	sol->dz = cam->z - sph->c.z;
	sol->a = pow(p->x, 2) + pow(p->y, 2) + pow(p->z, 2);
	sol->b = 2 * (sol->dx * p->x + sol->dy * p->y + sol->dz * p->z);
	sol->c = (pow(sol->dx, 2) + pow(sol->dy, 2) +
			pow(sol->dz, 2) - pow(sph->radius, 2));
	sol->d_cap = pow(sol->b, 2) - 4 * sol->a * sol->c;
	if (sol->d_cap < 0)
		return (1000000);
	t1 = (-sol->b + sqrt(sol->d_cap)) / (2 * sol->a);
	t2 = (-sol->b - sqrt(sol->d_cap)) / (2 * sol->a);
	if (t1 > t2 && t1 > 0 && t2 > 0)
		return (t2);
	if (t1 <= t2 && t1 > 0 && t2 > 0)
		return (t1);
	return (1000000);
}
