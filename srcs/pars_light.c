/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 18:56:59 by aapricot          #+#    #+#             */
/*   Updated: 2020/11/23 21:35:02 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "offset.h"
#include "scene.h"
#include "resource_manager.h"

t_selector		g_selector_light[] = { {"origin", offsetof(t_parsed_light, origin), get_vector},
									{"direction", offsetof(t_parsed_light, direction), get_vector},
									{"color", offsetof(t_parsed_light, color), get_color},
									{"ls", offsetof(t_parsed_light, ls), get_float},
									{"type", offsetof(t_parsed_light, type), get_light_type},
									// {"object_id", offsetof(t_parsed_light, object_id), get_int}
									};

int				g_light_selector_size = sizeof(g_selector_light) / sizeof(t_selector);

void			validate_light(t_parsed_light *light, t_parsed_info asset, t_res_mngr *res_mngr)
{
	asset.type = 1;
	asset.data.light.type = light->type;
	asset.data.light.color = light->color;
	asset.data.light.direction = light->direction;
	asset.data.light.ls = light->ls;
	asset.data.light.origin = light->origin;
	asset.data.light.pdf = light->pdf;
	printf("type = %d\n", light->type);
	printf("origin.x = %f\n", light->origin.x);
	printf("origin.x = %f\n", light->origin.y);
	printf("origin.x = %f\n", light->origin.z);
	printf("direction.x = %f\n", light->direction.x);
	printf("direction.y = %f\n", light->direction.y);
	printf("direction.z = %f\n", light->direction.z);
	add_parsed_asset(res_mngr, asset);
}

void		pars_light(char *str, t_parsed_info *asset, t_res_mngr *res_mngr)
{
	char			*a;
	char			*b;
	t_parsed_light			light;
	int				i;

	i = 0;
	light = get_default_light();
	while (*str != '{' && *str != '\0')
		str++;
	str++;
	while (*str != '\0')
	{
		a = get_key(&str);
		b = get_value(&str);
		// printf("%s\n%s\n====\n", a, b);
		while (*str == ';' || *str == '}')
			str++;
		while (i < g_light_selector_size)
		{
			if (!ft_strcmp(g_selector_light[i].name, a))
			{
				g_selector_light[i].func(b, g_selector_light[i].offset, &light);	//can get fill function from pars_option and change cicle
				break ;
			}
			// printf("key = %s\ncheck = %s\n\n", a, g_selector_light[i].name);
			i++;
		}
		i = 0;
		free(a);
		free(b);
	}
	validate_light(&light, *asset, res_mngr);
}