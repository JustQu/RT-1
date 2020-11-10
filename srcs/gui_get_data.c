/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_get_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 20:39:11 by alex              #+#    #+#             */
/*   Updated: 2020/11/10 15:11:40 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "libft.h"
#include "rt.h"

void			get_void_data(char *string, char **str)
{
	str[0] = ft_strdup(string);
	str[1] = NULL;
	str[2] = NULL;
	str[3] = NULL;
}

void			get_intensive_data(int ptr, char *string, char **str)
{
	str[0] = ft_strdup(string);
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
	str[2] = NULL;
	str[3] = NULL;
}

void			get_texture_data(int ptr, char *string, char **str)
{
	str[0] = ft_strdup(string);
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
	str[2] = NULL;
	str[3] = NULL;
}

void			get_shape_data(int ptr, char *string, char **str)
{
	str[0] = ft_strdup(string);
	if (ptr == 0)
		str[1] = ft_strdup("cone");
	else if (ptr == 1)
		str[1] = ft_strdup("cylinder");
	else if (ptr == 2)
		str[1] = ft_strdup("paraboloid");
	else if (ptr == 3)
		str[1] = ft_strdup("plane");
	else if (ptr == 4)
		str[1] = ft_strdup("sphere");
	else if (ptr == 5)
		str[1] = ft_strdup("torus");
	else if (ptr == 6)
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
	str[2] = NULL;
	str[3] = NULL;
}

void			get_material_data(int ptr, char *string, char **str)
{
	str[0] = ft_strdup(string);
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
	str[2] = NULL;
	str[3] = NULL;
}

void			get_camera_type_data(int ptr, char *string, char **str)
{
	str[0] = ft_strdup(string);
	if (ptr == 0)
		str[1] = ft_strdup("orthographic");
	else if (ptr == 1)
		str[1] = ft_strdup("perspective");
	else if (ptr == 2)
		str[1] = ft_strdup("thin_lens");
	else if (ptr == 3)
		str[1] = ft_strdup("fisheye");
	else if (ptr == 4)
		str[1] = ft_strdup("spherical");
	else if (ptr == 5)
		str[1] = ft_strdup("stereo");
	else
		str[1] = ft_strdup("material");
	str[2] = NULL;
	str[3] = NULL;
}

void			get_str_data(char *str1, char *string, char **str)
{
	str[0] = ft_strdup(string);
	str[1] = ft_strdup(str1);
	str[2] = NULL;
	str[3] = NULL;
}

void			get_float_data(float ptr, char *string, char **str)
{
	str[0] = ft_strdup(string);
	str[1] = itoa_float(ptr);
	str[2] = NULL;
	str[3] = NULL;
}

void			get_float4_data(cl_float4 ptr, char *string, char **str)
{
	str[0] = ft_strdup(string);
	str[1] = itoa_float(ptr.x);
	str[2] = itoa_float(ptr.y);
	str[3] = itoa_float(ptr.z);
}