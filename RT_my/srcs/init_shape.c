/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shape.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 15:53:18 by user              #+#    #+#             */
/*   Updated: 2020/06/29 17:05:55 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

float			ft_atoi_for_float(char *str)
{
	int			i;
	float		n;

	n = ft_atoi(str);
	i = 0;
	while (str[i] && str[i] != '.')
		i++;
	if (!str[i])
		return (n);
	i++;
	n += ft_atoi(&str[i]) / pow(10, ft_strlen(&str[i]));
	if (n < 1 && *str == '-')
		n *= -1;
	return (n);
}

t_shape			*init_cilin(char **elem)
{
	t_shape		*shape;

	shape = (t_shape*)malloc(sizeof(t_shape));
	shape->cilin = (t_cilin*)malloc(sizeof(t_cilin));
	shape->cilin->c.x = ft_atoi_for_float(elem[1]);
	shape->cilin->c.y = ft_atoi_for_float(elem[2]);
	shape->cilin->c.z = ft_atoi_for_float(elem[3]);
	shape->cilin->col.r = ft_atoi(elem[4]);
	shape->cilin->col.g = ft_atoi(elem[5]);
	shape->cilin->col.b = ft_atoi(elem[6]);
	shape->cilin->a = ft_atoi_for_float(elem[7]);
	shape->cilin->b = ft_atoi_for_float(elem[8]);
	shape->specular = ft_atoi_for_float(elem[9]);
	shape->cilin->r.angle_x = rad(ft_atoi_for_float(elem[10]));
	shape->cilin->r.angle_y = rad(ft_atoi_for_float(elem[11]));
	shape->cilin->r.angle_z = rad(ft_atoi_for_float(elem[12]));
	shape->sph = NULL;
	shape->plane = NULL;
	shape->cone = NULL;
	shape->next = NULL;
	define_mega_matrix(shape->cilin->sol.k, &shape->cilin->c, &shape->cilin->r);
	return (shape);
}

t_shape			*init_cone(char **elem)
{
	t_shape		*shape;

	shape = (t_shape*)malloc(sizeof(t_shape));
	shape->cone = (t_cone*)malloc(sizeof(t_cone));
	shape->cone->o.x = ft_atoi_for_float(elem[1]);
	shape->cone->o.y = ft_atoi_for_float(elem[2]);
	shape->cone->o.z = ft_atoi_for_float(elem[3]);
	shape->cone->col.r = ft_atoi(elem[4]);
	shape->cone->col.g = ft_atoi(elem[5]);
	shape->cone->col.b = ft_atoi(elem[6]);
	shape->cone->a = ft_atoi_for_float(elem[7]);
	shape->cone->b = ft_atoi_for_float(elem[8]);
	shape->cone->c = ft_atoi_for_float(elem[9]);
	shape->specular = ft_atoi_for_float(elem[10]);
	shape->cone->r.angle_x = rad(ft_atoi_for_float(elem[11]));
	shape->cone->r.angle_y = rad(ft_atoi_for_float(elem[12]));
	shape->cone->r.angle_z = rad(ft_atoi_for_float(elem[13]));
	shape->sph = NULL;
	shape->plane = NULL;
	shape->cilin = NULL;
	shape->next = NULL;
	define_mega_matrix(shape->cone->sol.k, &shape->cone->o, &shape->cone->r);
	return (shape);
}

t_shape			*init_sphere(char **elem)
{
	t_shape		*shape;

	shape = (t_shape*)malloc(sizeof(t_shape));
	shape->sph = (t_sphere*)malloc(sizeof(t_sphere));
	shape->sph->c.x = ft_atoi_for_float(elem[1]);
	shape->sph->c.y = ft_atoi_for_float(elem[2]);
	shape->sph->c.z = ft_atoi_for_float(elem[3]);
	shape->sph->col.r = ft_atoi(elem[4]);
	shape->sph->col.g = ft_atoi(elem[5]);
	shape->sph->col.b = ft_atoi(elem[6]);
	shape->sph->radius = ft_atoi_for_float(elem[7]);
	shape->specular = ft_atoi_for_float(elem[8]);
	shape->sph->r.angle_x = rad(ft_atoi_for_float(elem[9]));
	shape->sph->r.angle_y = rad(ft_atoi_for_float(elem[10]));
	shape->sph->r.angle_z = rad(ft_atoi_for_float(elem[11]));
	shape->cilin = NULL;
	shape->plane = NULL;
	shape->cone = NULL;
	shape->next = NULL;
	define_mega_matrix(shape->sph->sol.k, &shape->sph->c, &shape->sph->r);
	return (shape);
}

t_shape			*init_plane(char **elem)
{
	t_shape		*shape;

	shape = (t_shape*)malloc(sizeof(t_shape));
	shape->plane = (t_plane*)malloc(sizeof(t_plane));
	shape->plane->a = ft_atoi_for_float(elem[1]);
	shape->plane->b = ft_atoi_for_float(elem[2]);
	shape->plane->c = ft_atoi_for_float(elem[3]);
	shape->plane->d = ft_atoi_for_float(elem[4]);
	shape->plane->col.r = ft_atoi(elem[5]);
	shape->plane->col.g = ft_atoi(elem[6]);
	shape->plane->col.b = ft_atoi(elem[7]);
	shape->specular = ft_atoi_for_float(elem[8]);
	shape->plane->r.angle_x = rad(ft_atoi_for_float(elem[9]));
	shape->plane->r.angle_y = rad(ft_atoi_for_float(elem[10]));
	shape->plane->r.angle_z = rad(ft_atoi_for_float(elem[11]));
	shape->cilin = NULL;
	shape->sph = NULL;
	shape->cone = NULL;
	shape->next = NULL;
	return (shape);
}
