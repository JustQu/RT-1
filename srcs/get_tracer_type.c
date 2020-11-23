/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tracer_type.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 20:28:18 by aapricot          #+#    #+#             */
/*   Updated: 2020/11/23 20:32:34 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "offset.h"
#include "parser.h"

int					get_tracer_type_value(char *str)
{
	if (!ft_strcmp(str, "path_tracer"))
		return (path_tracer);
	else if (!ft_strcmp(str, "ray_caster"))
		return (ray_caster);
	else if (!ft_strcmp(str, "direct_lightning"))
		return (direct_lightning);
	return (-1);
}

void				get_tracer_type(char *str, int offset, void *data)
{
	unsigned char	*v;
	t_tracer_type	*type;

	v = (unsigned char *)data + offset;
	type = (t_tracer_type *)v;
	*type = get_tracer_type_value(str);
}