/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resource_manager.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 20:25:22 by dmelessa          #+#    #+#             */
/*   Updated: 2020/11/16 22:32:13 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESOURCE_MANAGER
# define RESOURCE_MANAGER

# include "rt_types.h"
# include "rt_options.h"
# include "sampler_manager.h"
# include "parser.h"
# include "scene.h"
# include "rt.h"

typedef struct s_resource_manager	t_res_mngr;

struct	s_resource_manager
{
	t_instance_info		info;
	t_scene				*scene;
	t_sampler_manager	*sampler_manager;
	t_rt_options		*rt_options;
};

void	add_parsed_asset(t_res_mngr *const mngr,
						t_parsed_info asset);

int		init_resource_manager(t_res_mngr *resource_manager,
							t_rt *rt);
// void			pars_object(t_res_mngr *resource_manager, t_parsed_info *asset, char *str, int log);


# endif
