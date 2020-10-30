/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resource_manager.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 20:25:22 by dmelessa          #+#    #+#             */
/*   Updated: 2020/10/28 20:30:49 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESOURCE_MANAGER
# define RESOURCE_MANAGER

# include "rt_types.h"
# include "scene.h"
# include "rt_options.h"
# include "sampler_manager.h"
# include "parser.h"

typedef struct s_resource_manager	t_res_mngr;

struct	s_resource_manager
{
	t_scene				*scene;
	t_sampler_manager	*sampler_manager;
	t_rt_options		*rt_options;
};

void	add_parsed(t_res_mngr *const resource_manager,
					t_parsed_info info);

# endif
