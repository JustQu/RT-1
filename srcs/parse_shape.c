/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shape.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximka <maximka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 15:50:26 by user              #+#    #+#             */
/*   Updated: 2020/06/26 15:33:57 by maximka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_pshape		ft_psphere(t_pshape shape, char **elem)
{
	if (shape.start == NULL)
	{
		shape.start = init_sphere(elem);
		shape.shape = shape.start;
	}
	else
	{
		shape.shape->next = init_sphere(elem);
		shape.shape = shape.shape->next;
	}
	return (shape);
}

t_pshape		ft_pcilin(t_pshape shape, char **elem)
{
	if (shape.start == NULL)
	{
		shape.start = init_cilin(elem);
		shape.shape = shape.start;
	}
	else
	{
		shape.shape->next = init_cilin(elem);
		shape.shape = shape.shape->next;
	}
	return (shape);
}

t_pshape		ft_pcone(t_pshape shape, char **elem)
{
	if (shape.start == NULL)
	{
		shape.start = init_cone(elem);
		shape.shape = shape.start;
	}
	else
	{
		shape.shape->next = init_cone(elem);
		shape.shape = shape.shape->next;
	}
	return (shape);
}

t_pshape		ft_pplane(t_pshape shape, char **elem)
{
	if (shape.start == NULL)
	{
		shape.start = init_plane(elem);
		shape.shape = shape.start;
	}
	else
	{
		shape.shape->next = init_plane(elem);
		shape.shape = shape.shape->next;
	}
	return (shape);
}
