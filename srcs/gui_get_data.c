/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_get_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 20:39:11 by alex              #+#    #+#             */
/*   Updated: 2020/12/13 15:47:48 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "libft.h"
#include "rt.h"
#include "rt_error.h"

void			get_intensive_data(int ptr, char *string, char **str)
{
	str[0] = ft_strdup(string);
	rt_is_dead(system_err, system_malloc_error, !str[0], "gui_get_data 1");
	if (ptr == 0)
		str[1] = ft_strdup("ambient");
	else if (ptr == 1)
		str[1] = ft_strdup("ambient_occluder");
	else if (ptr == 2)
		str[1] = ft_strdup("directional");
	else if (ptr == 3)
		str[1] = ft_strdup("point");
	else if (ptr == 4)
		str[1] = ft_strdup("area");
	else if (ptr == 5)
		str[1] = ft_strdup("enviromental");
	rt_is_dead(system_err, system_malloc_error, !str[1], "gui_get_data 2");
	str[2] = NULL;
	str[3] = NULL;
}

void			get_texture_data(int ptr, char *string, char **str)
{
	str[0] = ft_strdup(string);
	rt_is_dead(system_err, system_malloc_error, !str[0], "gui_get_data 3");
	if (ptr == 0)
		str[1] = ft_strdup("solid");
	else if (ptr == 1)
		str[1] = ft_strdup("checker");
	else if (ptr == 2)
		str[1] = ft_strdup("checker2d");
	else if (ptr == 3)
		str[1] = ft_strdup("transparent_checker");
	else if (ptr == 4)
		str[1] = ft_strdup("reflective_checker");
	else if (ptr == 5)
		str[1] = ft_strdup("perlin");
	else if (ptr == 6)
		str[1] = ft_strdup("smooth_perlin");
	else if (ptr == 7)
		str[1] = ft_strdup("turbulence_perlin");
	else if (ptr == 8)
		str[1] = ft_strdup("wave_perlin");
	else if (ptr == 9)
		str[1] = ft_strdup("image");
	rt_is_dead(system_err, system_malloc_error, !str[1], "gui_get_data 4");
	str[2] = NULL;
	str[3] = NULL;
}

void			get_shape_data_2(int ptr, char **str)
{
	if (ptr == 6)
		str[1] = ft_strdup("triangle");
	else if (ptr == 7)
		str[1] = ft_strdup("box");
	else if (ptr == 8)
		str[1] = ft_strdup("disk");
	else if (ptr == 9)
		str[1] = ft_strdup("rectangle");
	else if (ptr == 10)
		str[1] = ft_strdup("generic_shere");
	else
		str[1] = ft_strdup("no shape");
	rt_is_dead(system_err, system_malloc_error, !str[1], "gui_get_data 5");
}

void			get_shape_data(int ptr, char *string, char **str)
{
	str[0] = ft_strdup(string);
	rt_is_dead(system_err, system_malloc_error, !str[0], "gui_get_data 6");
	if (ptr == 0)
		str[1] = ft_strdup("cone");
	else if (ptr == 2)
		str[1] = ft_strdup("paraboloid");
	else if (ptr == 3)
		str[1] = ft_strdup("plane");
	else if (ptr == 4)
		str[1] = ft_strdup("sphere");
	else if (ptr == 5)
		str[1] = ft_strdup("torus");
	rt_is_dead(system_err, system_malloc_error, !str[1], "gui_get_data 7");
	get_shape_data_2(ptr, str);
	str[2] = NULL;
	str[3] = NULL;
}

void			get_material_data(int ptr, char *string, char **str)
{
	str[0] = ft_strdup(string);
	rt_is_dead(system_err, system_malloc_error, !str[0], "gui_get_data 8");
	if (ptr == 0)
		str[1] = ft_strdup("matte");
	else if (ptr == 1)
		str[1] = ft_strdup("phong");
	else if (ptr == 2)
		str[1] = ft_strdup("emissive");
	else if (ptr == 3)
		str[1] = ft_strdup("reflective");
	else if (ptr == 4)
		str[1] = ft_strdup("metal");
	else if (ptr == 5)
		str[1] = ft_strdup("dielectric");
	else
		str[1] = ft_strdup("no material");
	rt_is_dead(system_err, system_malloc_error, !str[1], "gui_get_data 9");
	str[2] = NULL;
	str[3] = NULL;
}
