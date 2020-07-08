/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximka <maximka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 14:38:28 by maximka           #+#    #+#             */
/*   Updated: 2020/06/29 15:26:24 by maximka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		fill_sol_cone(t_sol *sol, t_vector *cam, t_vector *p,
	t_cone *cone)
{
	sol->n[0] = sol->k[0][0] * cam->x + sol->k[0][1] * cam->y
		+ sol->k[0][2] * cam->z + sol->k[0][3] - cone->o.x;
	sol->n[1] = sol->k[2][0] * cam->x + sol->k[2][1] * cam->y
		+ sol->k[2][2] * cam->z + sol->k[2][3] - cone->o.z;
	sol->n[2] = sol->k[1][0] * cam->x + sol->k[1][1] * cam->y
		+ sol->k[1][2] * cam->z + sol->k[1][3] - cone->o.y;
	sol->m[0] = sol->k[0][0] * p->x + sol->k[0][1] * p->y + sol->k[0][2] * p->z;
	sol->m[1] = sol->k[2][0] * p->x + sol->k[2][1] * p->y + sol->k[2][2] * p->z;
	sol->m[2] = sol->k[1][0] * p->x + sol->k[1][1] * p->y + sol->k[1][2] * p->z;
}

void		fill_sol_cilin(t_sol *sol, t_vector *cam, t_vector *p,
	t_cilin *cilin)
{
	sol->n[0] = sol->k[0][0] * cam->x + sol->k[0][1] * cam->y +
		sol->k[0][2] * cam->z + sol->k[0][3] - cilin->c.x;
	sol->n[1] = sol->k[2][0] * cam->x + sol->k[2][1] * cam->y +
		sol->k[2][2] * cam->z + sol->k[2][3] - cilin->c.z;
	sol->m[0] = sol->k[0][0] * p->x + sol->k[0][1] * p->y
		+ sol->k[0][2] * p->z;
	sol->m[1] = sol->k[2][0] * p->x + sol->k[2][1] * p->y
		+ sol->k[2][2] * p->z;
}
