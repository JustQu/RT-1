/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximka <maximka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/05 22:30:23 by maximka           #+#    #+#             */
/*   Updated: 2020/06/25 23:29:23 by maximka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

float			scal(t_vector a, t_vector b)
{
	float		scal;

	scal = (a.x * b.x + a.y * b.y + a.z * b.z);
	return (scal);
}

void			norm_vec(t_vector *a)
{
	a->x /= a->l;
	a->y /= a->l;
	a->z /= a->l;
}

float			vec_len(t_vector a)
{
	float		len;

	len = sqrt(pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2));
	return (len);
}
