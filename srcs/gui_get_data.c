/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_get_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 20:39:11 by alex              #+#    #+#             */
/*   Updated: 2020/10/30 20:54:48 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "libft.h"
#include "rt.h"

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
