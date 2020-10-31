/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 23:40:30 by dmelessa          #+#    #+#             */
/*   Updated: 2020/10/30 23:44:26 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "light_manager.h"
#include "utils.h"

void	init_light_manager(t_light_manager *light_manager)
{
	light_manager->lights = malloc(sizeof(t_light));
	light_manager->nlights = 0;
	light_manager->light_malloc_size = sizeof(t_light);
}

int		add_parsed_light(t_light_manager *light_manager, t_parsed_light
						parsed_light)
{
	t_light	light;

	light.type = parsed_light.type;
	light.origin = parsed_light.origin;
	light.direction = parsed_light.direction;
	light.color = parsed_light.color;
	light.ls = parsed_light.ls;

	light_manager->nlights++;
	if (light_manager->nlights * sizeof(t_light) >=
		light_manager->light_malloc_size)
	{
		light_manager->lights = ft_realloc(light_manager->lights,
			light_manager->light_malloc_size,
			light_manager->nlights * sizeof(t_light) * 2);
		light_manager->light_malloc_size = light_manager->nlights *
			sizeof(t_light) * 2;
	}
	light_manager->lights[light_manager->nlights - 1] = light;
	return (light_manager->nlights - 1);
}
