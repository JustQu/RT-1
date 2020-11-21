/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 18:56:59 by aapricot          #+#    #+#             */
/*   Updated: 2020/11/16 22:18:31 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "offset.h"

t_selector		g_selector_light[] = { {"origin", offsetof(t_light, origin), get_vector},
									{"direction", offsetof(t_light, direction), get_vector},
									{"color", offsetof(t_light, color), get_color},
									{"ls", offsetof(t_light, ls), get_float},
									{"type", offsetof(t_light, type), get_light_type},
									{"object_id", offsetof(t_light, object_id), get_int} };

int				g_light_selector_size = sizeof(g_selector_light) / sizeof(t_selector);

// void			add_parsed_light(t_light *light)
// {
// 	printf("type = %d\n", light->type);
// 	printf("origin.x = %f\n", light->origin.x);
// 	printf("origin.x = %f\n", light->origin.y);
// 	printf("origin.x = %f\n", light->origin.z);
// 	printf("direction.x = %f\n", light->direction.x);
// 	printf("direction.y = %f\n", light->direction.y);
// 	printf("direction.z = %f\n", light->direction.z);
// }

void		pars_light(char *str)
{
	char			*a;
	char			*b;
	t_light			light;
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
				g_selector_light[i].func(b, g_selector_light[i].offset, &light);
				break ;
			}
			// printf("key = %s\ncheck = %s\n\n", a, g_selector_light[i].name);
			i++;
		}
		i = 0;
		free(a);
		free(b);
	}
	// add_parsed_light(&light);
}