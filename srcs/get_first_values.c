/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_first_values.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 00:10:21 by aapricot          #+#    #+#             */
/*   Updated: 2020/12/02 20:58:14 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "offset.h"
#include "parser.h"

float		ft_atofloat(char *str)
{
	char	**arr;
	float	res;
	int		i;
	int		k;

	i = 1;
	res = 0.0;
	arr = ft_strsplit(str, '.');
	if (arr[0] == NULL)
		return (res);
	if (arr[0][0] == '-' && arr[0][1] == '0')
		i = -1;
	res += ft_atoi(arr[0]);
	if (arr[1] != NULL)
	{
		k = ft_atoi(arr[1]);
		if (res < 0)
			res -= (float)(k / pow(10, len_word(arr[1])));
		else
			res += (float)(k / pow(10, len_word(arr[1])));
	}
	res *= i;
	free_tab(arr);
	return (res);
}

void		get_color(char *str, int offset, void *data)
{
	t_color			*color;
	char			**rgb;

	color = (t_color *)((unsigned char *)data + offset);
	*color = (t_color){1.0f, 1.0f, 1.0f};
	rgb = NULL;
	if (ft_isdigit(str[0]))
	{
		rgb = ft_strsplit(str, ',');
		if (rgb[0] == NULL)
		{
			free_tab(rgb);
			return ;
		}
		color->r = ft_atofloat(rgb[0]);
		if (rgb[1] == NULL)
		{
			free_tab(rgb);
			return ;
		}
		color->g = ft_atofloat(rgb[1]);
		if (rgb[2] != NULL)
			color->b = ft_atofloat(rgb[2]);
		free_tab(rgb);
	}
}

void		get_vector(char *str, int offset, void *data)
{
	unsigned char	*v;
	cl_float4		*vec_ptr;
	char			**split;

	v = (unsigned char *)data + offset;
	vec_ptr = (cl_float4 *)v;
	*vec_ptr = (cl_float4){0.0f, 0.0f, 0.0f, 0.0f};
	split = ft_strsplit(str, ',');
	if (split[0] == NULL)
	{
		free_tab(split);
		return ;
	}
	else
		vec_ptr->x = ft_atofloat(split[0]);
	if (split[1] == NULL)
	{
		free_tab(split);
		return ;
	}
	else
		vec_ptr->y = ft_atofloat(split[1]);
	if (split[2] != NULL)
		vec_ptr->z = ft_atofloat(split[2]);
	free_tab(split);
}

void		get_float(char *str, int offset, void *data)
{
	unsigned char	*v;
	cl_float		*ptr;

	v = (unsigned char *)data + offset;
	ptr = (cl_float *)v;
	*ptr = ft_atofloat(str);
}
