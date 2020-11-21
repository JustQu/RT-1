/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_light_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 21:48:15 by aapricot          #+#    #+#             */
/*   Updated: 2020/11/05 20:06:38 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "offset.h"
#include "parser.h"

int					get_light_type_value(char *str)
{
	if (!ft_strcmp(str, "ambient"))
		return (ambient);
	else if (!ft_strcmp(str, "ambient_occluder"))
		return (ambient_occluder);
	else if (!ft_strcmp(str, "directional"))
		return (directional);
	else if (!ft_strcmp(str, "point"))
		return (point);
	else if (!ft_strcmp(str, "area"))
		return (area);
	else if (!ft_strcmp(str, "enviromental"))
		return (enviromental);
	return (-1);
}

void				get_light_type(char *str, int offset, void *data)
{
	unsigned char	*v;
	t_light_type	*type;

	v = (unsigned char *)data + offset;
	type = (t_light_type *)v;
	*type = get_light_type_value(str);
}