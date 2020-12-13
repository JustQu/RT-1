/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_get_data_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 15:26:04 by alex              #+#    #+#             */
/*   Updated: 2020/12/04 22:25:36 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "libft.h"
#include "rt_err.h"
#include "safe_call.h"

void			get_void_data(char *string, char *str[4])
{
	if (string == NULL || str == NULL)
		rt_error("get_void_data(): given NULL pointer");
	safe_call_ptr((str[0] = ft_strdup(string)), "get_void_data: malloc error");
	str[1] = NULL;
	str[2] = NULL;
	str[3] = NULL;
}

void			get_camera_type_data(int ptr, char *string, char *str[4])
{
	if (string == NULL || str == NULL)
		rt_error("get_camera_type_data(): given NULL pointer");
	safe_call_ptr((str[0] = ft_strdup(string)), "malloc error");
	if (ptr == 0)
		safe_call_ptr((str[1] = ft_strdup("orthographic")), "malloc error");
	else if (ptr == 1)
		safe_call_ptr((str[1] = ft_strdup("perspective")), "malloc error");
	else if (ptr == 2)
		safe_call_ptr((str[1] = ft_strdup("thin_lens")), "malloc error");
	else if (ptr == 3)
		safe_call_ptr((str[1] = ft_strdup("fisheye")), "malloc error");
	else if (ptr == 4)
		safe_call_ptr((str[1] = ft_strdup("spherical")), "malloc error");
	else if (ptr == 5)
		safe_call_ptr((str[1] = ft_strdup("stereo")), "malloc error");
	else
		safe_call_ptr((str[1] = ft_strdup("material")), "malloc error");
	str[2] = NULL;
	str[3] = NULL;
}

void			get_str_data(char *str1, char *string, char *str[4])
{
	safe_call_ptr((str[0] = ft_strdup(string)), "malloc error");
	safe_call_ptr((str[1] = ft_strdup(str1)), "malloc error");
	str[2] = NULL;
	str[3] = NULL;
}

void			get_float_data(float ptr, char *string, char *str[4])
{
	safe_call_ptr((str[0] = ft_strdup(string)), "malloc error");
	safe_call_ptr((str[1] = itoa_float(ptr)), "malloc error");
	str[2] = NULL;
	str[3] = NULL;
}

void			get_float4_data(cl_float4 ptr, char *string, char *str[4])
{
	safe_call_ptr((str[0] = ft_strdup(string)), "malloc error");
	safe_call_ptr((str[1] = itoa_float(ptr.x)), "malloc error");
	safe_call_ptr((str[2] = itoa_float(ptr.y)), "malloc error");
	safe_call_ptr((str[3] = itoa_float(ptr.z)), "malloc error");
}
