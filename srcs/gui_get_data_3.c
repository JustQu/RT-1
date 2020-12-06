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
	str[0] = ft_strdup(string);
	if (ptr == 0)
		str[1] = ft_strdup("false");
	else if (ptr == 1)
		str[1] = ft_strdup("true");
	str[2] = NULL;
	str[3] = NULL;
}

void			get_ambient_il_data(int ptr, char *string, char **str)
{
	str[0] = ft_strdup(string);
	if (ptr == 0)
		str[1] = ft_strdup("constant");
	else if (ptr == 1)
		str[1] = ft_strdup("occlusion");
	str[2] = NULL;
	str[3] = NULL;
}

void			get_color_data(t_color color, char *string, char **str)
{
	str[0] = ft_strdup(string);
	str[1] = itoa_float(color.r);
	str[2] = itoa_float(color.g);
	str[3] = itoa_float(color.b);
}
