/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_get_data_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 09:58:19 by alex              #+#    #+#             */
/*   Updated: 2020/11/28 10:40:47 by alex             ###   ########.fr       */
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
