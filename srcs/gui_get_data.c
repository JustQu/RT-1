/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_get_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 20:39:11 by alex              #+#    #+#             */
/*   Updated: 2020/11/28 10:00:05 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "libft.h"
#include "rt.h"

void			get_intensive_data(int ptr, char *string, char **str)
{
	str[0] = ft_strdup(string);
	if (ptr == 0)
		safe_call_ptr((str[1] = ft_strdup("ambient")), "malloc error");
	else if (ptr == 1)
		safe_call_ptr((str[1] = ft_strdup("ambient_occluder")), "malloc error");
	else if (ptr == 2)
		safe_call_ptr((str[1] = ft_strdup("directional")), "malloc error");
	else if (ptr == 3)
		safe_call_ptr((str[1] = ft_strdup("point")), "malloc error");
	else if (ptr == 4)
		safe_call_ptr((str[1] = ft_strdup("area")), "malloc error");
	else if (ptr == 5)
		safe_call_ptr((str[1] = ft_strdup("enviromental")), "malloc error");
	str[2] = NULL;
	str[3] = NULL;
}

void			get_texture_data(int ptr, char *string, char **str)
{
	str[0] = ft_strdup(string);
	if (ptr == 0)
		safe_call_ptr((str[1] = ft_strdup("solid")), "malloc error");
	else if (ptr == 1)
		safe_call_ptr((str[1] = ft_strdup("checker")), "malloc error");
	else if (ptr == 2)
		safe_call_ptr((str[1] = ft_strdup("checker2d")), "malloc error");
	else if (ptr == 3)
		safe_call_ptr((str[1] = ft_strdup("transparent_checker")), "malloc error");
	else if (ptr == 4)
		safe_call_ptr((str[1] = ft_strdup("reflective_checker")), "malloc error");
	else if (ptr == 5)
		safe_call_ptr((str[1] = ft_strdup("perlin")), "malloc error");
	else if (ptr == 6)
		safe_call_ptr((str[1] = ft_strdup("smooth_perlin")), "malloc error");
	else if (ptr == 7)
		safe_call_ptr((str[1] = ft_strdup("turbulence_perlin")), "malloc error");
	else if (ptr == 8)
		safe_call_ptr((str[1] = ft_strdup("wave_perlin")), "malloc error");
	else if (ptr == 9)
		safe_call_ptr((str[1] = ft_strdup("image")), "malloc error");
	str[2] = NULL;
	str[3] = NULL;
}

void			get_shape_data_2(int ptr, char **str)
{
	if (ptr == 6)
		safe_call_ptr((str[1] = ft_strdup("triangle")), "malloc error");
	else if (ptr == 7)
		safe_call_ptr((str[1] = ft_strdup("box")), "malloc error");
	else if (ptr == 8)
		safe_call_ptr((str[1] = ft_strdup("disk")), "malloc error");
	else if (ptr == 9)
		safe_call_ptr((str[1] = ft_strdup("rectangle")), "malloc error");
	else if (ptr == 10)
		safe_call_ptr((str[1] = ft_strdup("generic_shere")), "malloc error");
	else
		safe_call_ptr((str[1] = ft_strdup("no shape")), "malloc error");
}

void			get_shape_data(int ptr, char *string, char **str)
{
	str[0] = ft_strdup(string);
	if (ptr == 0)
		safe_call_ptr((str[1] = ft_strdup("cone")), "malloc error");
	else if (ptr == 2)
		safe_call_ptr((str[1] = ft_strdup("paraboloid")), "malloc error");
	else if (ptr == 3)
		safe_call_ptr((str[1] = ft_strdup("plane")), "malloc error");
	else if (ptr == 4)
		safe_call_ptr((str[1] = ft_strdup("sphere")), "malloc error");
	else if (ptr == 5)
		safe_call_ptr((str[1] = ft_strdup("torus")), "malloc error");
	get_shape_data_2(ptr, str);
	str[2] = NULL;
	str[3] = NULL;
}

void			get_material_data(int ptr, char *string, char **str)
{
	str[0] = ft_strdup(string);
	if (ptr == 0)
		safe_call_ptr((str[1] = ft_strdup("matte")), "malloc error");
	else if (ptr == 1)
		safe_call_ptr((str[1] = ft_strdup("phong")), "malloc error");
	else if (ptr == 2)
		safe_call_ptr((str[1] = ft_strdup("emissive")), "malloc error");
	else if (ptr == 3)
		safe_call_ptr((str[1] = ft_strdup("reflective")), "malloc error");
	else if (ptr == 4)
		safe_call_ptr((str[1] = ft_strdup("metal")), "malloc error");
	else if (ptr == 5)
		safe_call_ptr((str[1] = ft_strdup("dielectric")), "malloc error");
	else
		safe_call_ptr((str[1] = ft_strdup("no material")), "malloc error");
	str[2] = NULL;
	str[3] = NULL;
}