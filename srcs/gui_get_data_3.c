/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_get_data_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 09:58:19 by alex              #+#    #+#             */
/*   Updated: 2020/12/09 15:21:55 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "libft.h"
#include "rt_err.h"
#include "safe_call.h"

void			get_true_data(int ptr, char *string, char **str)
{
	if (str == NULL || string == NULL)
		rt_error("get_true_data(): given NULL pointer");
	safe_call_ptr((str[0] = ft_strdup(string)), "malloc error");
	if (ptr == 0)
		safe_call_ptr((str[1] = ft_strdup("false")), "malloc error");
	else if (ptr == 1)
		safe_call_ptr((str[1] = ft_strdup("true")), "malloc error");
	str[2] = NULL;
	str[3] = NULL;
}

void			get_ambient_il_data(int ptr, char *string, char **str)
{
	if (str == NULL || string == NULL)
		rt_error("get_ambient_il_data(): given NULL pointer");
	safe_call_ptr((str[0] = ft_strdup(string)), "malloc error");
	if (ptr == 0)
		safe_call_ptr((str[1] = ft_strdup("constant")), "malloc error");
	else if (ptr == 1)
		safe_call_ptr((str[1] = ft_strdup("occlusion")), "malloc error");
	str[2] = NULL;
	str[3] = NULL;
}

void			get_color_data(t_color color, char *string, char **str)
{
	if (str == NULL || string == NULL)
		rt_error("get_color_data(): given NULL pointer");
	safe_call_ptr((str[0] = ft_strdup(string)), "malloc error");
	safe_call_ptr((str[1] = itoa_float(color.r)), "malloc error");
	safe_call_ptr((str[2] = itoa_float(color.g)), "malloc error");
	safe_call_ptr((str[3] = itoa_float(color.b)), "malloc error");
}

void			get_rt_type_data(int ptr, char *string, char **str)
{
	str[0] = ft_strdup(string);
	if (ptr == 0)
		str[1] = ft_strdup("ray_caster");
	else if (ptr == 1)
		str[1] = ft_strdup("dir_light");
	else if (ptr == 2)
		str[1] = ft_strdup("path_tracer");
	str[2] = NULL;
	str[3] = NULL;
}
