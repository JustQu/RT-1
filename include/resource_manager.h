/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resource_manager.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 20:25:22 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/16 13:08:43 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESOURCE_MANAGER_H
# define RESOURCE_MANAGER_H

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

void			add_parsed_asset(t_res_mngr *const mngr,
								t_parsed_info asset);

int				init_resource_manager(t_res_mngr *resource_manager,
										t_rt *rt);

t_instance_info		get_instance_info(t_res_mngr *const mngr, t_u32 id);
t_light				get_light_info(t_res_mngr *const mngr, t_u32 id);
void				scan_instance_01(t_res_mngr *const mngr, t_parsed_info asset);
void				scan_instance(t_res_mngr *const mngr, t_parsed_info asset);
void				add_parsed_asset(t_res_mngr *const mngr, t_parsed_info asset);
t_instance_info		get_instance_info(t_res_mngr *mngr, t_u32 id);
t_light				get_light_info(t_res_mngr *const mngr, t_u32 id);
t_matrix			create_inv_transformation_matrix(t_instance_info info);
int					add_instance(t_res_mngr *res_mngr,
							t_instance_manager *mngr, t_instance_info data);
float				compute_area(t_instance_info info);
void				add_emissive_instance(t_res_mngr *mngr, t_instance_info data);
int					init_resource_manager(t_res_mngr *resource_manager,
										t_rt *rt);
t_instance_info		get_object_info(t_res_mngr *mngr, t_instance instance,
								t_instance_extra extra);
t_instance_info		get_triangle_info(void);
t_instance_info		get_object_info(t_res_mngr *mngr, t_instance instance,
								   t_instance_extra extra);
t_instance_info		get_triangle_info(void);

#endif
