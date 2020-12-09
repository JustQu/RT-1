/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_material.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 21:14:07 by aapricot          #+#    #+#             */
/*   Updated: 2020/12/07 20:00:18 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "offset.h"
#include "parser.h"

t_selector		g_selector_mat[] = {
	{"type", offsetof(t_material, type), get_mat_type},
	{"ambient", offsetof(t_material, ka), get_float},
	{"diffuse", offsetof(t_material, kd), get_float},
	{"reflective", offsetof(t_material, kr), get_float},
	{"intensity", offsetof(t_material, ls), get_float},
	{"specular", offsetof(t_material, ks), get_float},
	{"roughness", offsetof(t_material, exp), get_vector},
	{"transmission", offsetof(t_material, kt), get_float},
	{"reflective_color", offsetof(t_material, reflective_color), get_color},
	{"is_reflective", offsetof(t_material, is_reflective), get_uchar},
	{"is_transparent", offsetof(t_material, is_transparent), get_uchar}
};

int				g_mat_selector_size = sizeof(g_selector_mat) /
sizeof(t_selector);

void			fill_material(char *a, char *b, t_material *material)
{
	int			i;

	if (a == NULL || b == NULL || material == NULL)
		rt_error("fill_material(): given NULL pointer");
	i = 0;
	while (i < g_mat_selector_size)
	{
		if (!ft_strcmp(g_selector_mat[i].name, a))
		{
			g_selector_mat[i].func(b, g_selector_mat[i].offset, material);
			break ;
		}
		i++;
	}
}

void			pars_material(char *str, int offset, void *data)
{
	char		*a;
	char		*b;
	t_material	*material;

	if (str == NULL || data == NULL)
		rt_error("pars_material(): given NULL pointer");
	safe_call_ptr((material = (t_material *)((unsigned char *)data + offset)),
		"pars_material(): malloc error");
	while (*str != '\0')
	{
		a = get_key(&str);
		b = get_value(&str);
		while ((*str == ';' || *str == '}') && *str != '\0')
			str++;
		fill_material(a, b, material);
		free(a);
		free(b);
	}
}
