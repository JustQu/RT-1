/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_option.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 18:55:24 by aapricot          #+#    #+#             */
/*   Updated: 2020/11/16 22:42:04 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "offset.h"

t_selector		g_selector_opt[] = { //{"ambient_occluder_sampler", NULL, pars_ambient_occluder_sampler}, //maybe does not need
									// {"ambient_occlusion", offsetof(t_rt_options, ambient_occlusion), get_int},
									{"background_color", offsetof(t_rt_options, background_color), get_color},
									{"depth", offsetof(t_rt_options, depth), get_int},
									{"shadows", offsetof(t_rt_options, shadows), get_int},
									{"area_lightning", offsetof(t_rt_options, area_lightning), get_int},
									{"spp", offsetof(t_rt_options, spp), get_float},
									{"aa_id", offsetof(t_rt_options, aa_id), get_int} };

int				g_opt_selector_size = sizeof(g_selector_opt) / sizeof(t_selector);

void			add_parsed_opt(t_rt_options *options)
{
	printf("shadows = %d\n", options->shadows);
	printf("depth = %d\n", options->depth);
}

void		pars_option(char *str)
{
	char			*a;
	char			*b;
	t_rt_options	options;
	int				i;

	i = 0;
	// options = get_default_options();
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
		while (i < g_opt_selector_size)
		{
			if (!ft_strcmp(g_selector_opt[i].name, a))
			{
				g_selector_opt[i].func(b, g_selector_opt[i].offset, &options);
				break ;
			}
			// printf("key = %s\ncheck = %s\n\n", a, g_selector_cam[i].name);
			i++;
		}
		i = 0;
		free(a);
		free(b);
	}
	add_parsed_opt(&options);
}