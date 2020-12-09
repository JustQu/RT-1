/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 18:56:59 by aapricot          #+#    #+#             */
/*   Updated: 2020/12/02 20:34:10 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "offset.h"
#include "scene.h"
#include "resource_manager.h"

t_selector			g_selector_light[] = {
	{"origin", offsetof(t_parsed_light, origin), get_vector},
	{"direction", offsetof(t_parsed_light, direction), get_vector},
	{"color", offsetof(t_parsed_light, color), get_color},
	{"ls", offsetof(t_parsed_light, ls), get_float},
	{"type", offsetof(t_parsed_light, type), get_light_type},
};

int					g_light_selector_size = sizeof(g_selector_light) /
sizeof(t_selector);

void				validate_light(t_parsed_light *light, t_parsed_info asset,
								t_res_mngr *res_mngr)
{
	if (light == NULL || res_mngr == NULL)
		rt_error("validate_light(): given NULL pointer");
	asset.type = 1;
	asset.data.light.type = light->type;
	asset.data.light.color = light->color;
	asset.data.light.direction = light->direction;
	asset.data.light.ls = light->ls;
	asset.data.light.origin = light->origin;
	asset.data.light.pdf = light->pdf;
	add_parsed_asset(res_mngr, asset);
}

void				fill_light(char *a, char *b, t_parsed_light *light)
{
	int		i;

	if (a == NULL || b == NULL || light == NULL)
		rt_error("fill_light(): given NULL pointer");
	i = 0;
	while (i < g_light_selector_size)
	{
		if (!ft_strcmp(g_selector_light[i].name, a))
		{
			g_selector_light[i].func(b, g_selector_light[i].offset, light);
			break ;
		}
		i++;
	}
}

void				pars_light(char *str, t_parsed_info *asset,
								t_res_mngr *res_mngr)
{
	char			*a;
	char			*b;
	t_parsed_light	light;

	if (str == NULL || asset == NULL || res_mngr == NULL)
		rt_error("pars_light(): given NULL pointer");
	light = get_default_light();
	while (*str != '{' && *str != '\0')
		str++;
	if (*str != '\0')
		str++;
	while (*str != '\0')
	{
		a = get_key(&str);
		b = get_value(&str);
		while (*str == ';' || *str == '}')
			str++;
		fill_light(a, b, &light);
		free(a);
		free(b);
	}
	validate_light(&light, *asset, res_mngr);
}
