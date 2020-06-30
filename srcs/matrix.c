/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximka <maximka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 15:45:15 by maximka           #+#    #+#             */
/*   Updated: 2020/06/29 13:41:32 by maximka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	define_mega_matrix(double k[4][4], t_vector *c, t_rotation *r)
{
	k[0][0] = cos(r->angle_y) * cos(r->angle_z);
	k[0][1] = -cos(r->angle_y) * sin(r->angle_z);
	k[0][2] = sin(r->angle_y);
	k[0][3] = -c->x * k[0][0] - c->y * k[0][1] - c->z * k[0][2] + c->x;
	k[1][0] = sin(r->angle_x) * sin(r->angle_y) * cos(r->angle_z) +
	cos(r->angle_x) * sin(r->angle_z);
	k[1][1] = -sin(r->angle_x) * sin(r->angle_x) * sin(r->angle_z) +
	cos(r->angle_x) * cos(r->angle_z);
	k[1][2] = -sin(r->angle_x) * cos(r->angle_y);
	k[1][3] = -c->x * k[1][0] - c->y * k[1][1] - c->z * k[1][2] + c->y;
	k[2][0] = -cos(r->angle_x) * sin(r->angle_y) * cos(r->angle_z) +
	sin(r->angle_x) * sin(r->angle_z);
	k[2][1] = cos(r->angle_x) * sin(r->angle_y) * sin(r->angle_z) +
	sin(r->angle_x) * cos(r->angle_z);
	k[2][2] = cos(r->angle_x) * cos(r->angle_y);
	k[2][3] = -c->x * k[2][0] - c->y * k[2][1] - c->z * k[2][2] + c->z;
	k[3][0] = 0;
	k[3][1] = 0;
	k[3][2] = 0;
	k[3][3] = 1;
}
