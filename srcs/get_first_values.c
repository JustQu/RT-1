/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_first_values.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 00:10:21 by aapricot          #+#    #+#             */
/*   Updated: 2020/11/23 16:57:10 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "offset.h"

// void		set_color_int(t_color *color, int value)
// {
// 	color->r = ((value >> 16) & 0x000000ff) / 255.f;
// 	color->g = ((value >> 8) & 0x000000ff) / 255.0f;
// 	color->b = (value & 0x000000ff) / 255.0f;
// }

void		free_tab(char **tab)
{
	int		n;

	n = 0;
	while (NULL != tab[n])
	{
		free(tab[n]);
		tab[n] = NULL;
		n += 1;
	}
	free(tab);
}

int			len_word(char *str)
{
	int len;
	int	i;

	i = 0;
	len = 0;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]))
			len++;
		i++;
	}
	return (len);
}

float		ft_atofloat(char *str) //функция говно, нужна другая
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
	unsigned char	*v;

	v = (unsigned char *)data + offset;
	color = (t_color *)v;
	*color = (t_color){1.0f, 1.0f, 1.0f};
	rgb = NULL;
	// if (str[0] == '0' && str[1] == 'x')
	// 	set_color_int(color, ft_atoi_hex(str + 2));
	if (ft_isdigit(str[0]))
	{
		rgb = ft_strsplit(str, ',');
		if (rgb[0] == NULL)
		{
			free_tab(rgb);
			return ;
		}
		else
			color->r = ft_atofloat(rgb[0]);
		if (rgb[1] == NULL)
		{
			free_tab(rgb);
			return ;
		}
		else
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
	vec_ptr->x = 0.0f;
	vec_ptr->y = 0.0f;
	vec_ptr->z = 0.0f;
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

void		get_uchar(char *str, int offset, void *data)
{
	unsigned char	*v;
	cl_uchar		*c;

	v = (unsigned char *)data + offset;
	c = (cl_uchar *)v;
	if (!ft_strcmp(str, "true"))
		*c = 1;
	else if (!ft_strcmp(str, "false"))
		*c = 0;
}

void		get_int(char *str, int offset, void *data)
{
	unsigned char	*v;
	cl_int			*num;

	v = (unsigned char *)data + offset;
	num = (cl_int *)v;
	*num = ft_atoi(str);
}
