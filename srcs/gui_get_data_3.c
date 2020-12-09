/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_get_data_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 09:58:19 by alex              #+#    #+#             */
/*   Updated: 2020/12/06 07:55:26 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "libft.h"

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
