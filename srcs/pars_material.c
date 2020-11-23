/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_material.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 21:14:07 by aapricot          #+#    #+#             */
/*   Updated: 2020/11/23 21:35:02 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "offset.h"
#include "parser.h"

t_selector		g_selector_mat[] = { {"type", offsetof(t_material, type), get_mat_type},
									{"ka", offsetof(t_material, ka), get_float},
									{"kd", offsetof(t_material, kd), get_float},
									{"kr", offsetof(t_material, kr), get_float},
									{"ls", offsetof(t_material, ls), get_float},
									{"ks", offsetof(t_material, ks), get_float},
									{"exp", offsetof(t_material, exp), get_vector},
									{"kt", offsetof(t_material, kt), get_float},
									{"reflective_color", offsetof(t_material, reflective_color), get_color},
									{"is_reflective", offsetof(t_material, is_reflective), get_uchar},
									{"is_transparent", offsetof(t_material, is_transparent), get_uchar} };

int				g_mat_selector_size = sizeof(g_selector_mat) / sizeof(t_selector);

void		pars_material(char *str, int offset, void *data)
{
	char			*a;
	char			*b;
	int				i;
	t_material		*material;

	material = (t_material *)((unsigned char *)data + offset);
	i = 0;
	while (*str != '\0')
	{
		a = get_key(&str);
		b = get_value(&str);
		while (*str == ';' || *str == '}')
			str++;
		while (i < g_mat_selector_size)
		{
			if (!ft_strcmp(g_selector_mat[i].name, a))
			{
				g_selector_mat[i].func(b, g_selector_mat[i].offset, material);	//can changed with fill function like function in pars_option
				break ;
			}
			i++;
		}
		i = 0;
		free(a);
		free(b);
	}
	// add_parsed_object(&material);
}
