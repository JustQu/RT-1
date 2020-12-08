/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_light_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 21:48:15 by aapricot          #+#    #+#             */
/*   Updated: 2020/12/02 20:19:17 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "offset.h"
#include "parser.h"

int					get_light_type_value(char *str)
{
	if (str == NULL)
		rt_error("get_light_type_value(): given NULL pointer");
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

cl_int				get_coefficient(char *str)
{
	if (str == NULL)
		rt_error("get_coefficient(): given NULL pointer");
	if (!ft_strcmp(str, "no"))
		return (no);
	else if (!ft_strcmp(str, "constant"))
		return (constant);
	else if (!ft_strcmp(str, "occluder"))
		return (occluder);
	return (-1);
}

void				get_light_type(char *str, int offset, void *data)
{
	unsigned char	*v;
	t_light_type	*type;

	if (str == NULL || data == NULL)
		rt_error("get_light_type(): given NULL pointer");
	v = (unsigned char *)data + offset;
	type = (t_light_type *)v;
	*type = get_light_type_value(str);
}

void				get_ambient_illumination(char *str, int offset, void *data)
{
	unsigned char	*v;
	cl_int			*coefficient;

	if (str == NULL || data == NULL)
		rt_error("get_ambient_illumination(): given NULL pointer");
	v = (unsigned char *)data + offset;
	coefficient = (cl_int *)v;
	*coefficient = get_coefficient(str);
}
