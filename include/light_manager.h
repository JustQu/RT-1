/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_manager.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 01:40:51 by dmelessa          #+#    #+#             */
/*   Updated: 2020/11/21 21:06:46 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_MANAGER_H
# define LIGHT_MANAGER_H

# ifndef __OPENCL_C_VERSION__
#  include "rt_types.h"
#  include "light.h"
#  include "parser.h"
# endif

typedef struct	s_light_manager
{
	t_light		*lights;
	size_t		light_malloc_size;
	int			nlights;
	uint32_t	gap[2];
}				t_light_manager;

void	init_light_manager(t_light_manager *light_manger);
int		add_parsed_light(t_light_manager *light_manager, t_parsed_light light);
int		new_light(t_light_manager *light_manager, t_light_type type);

# endif
