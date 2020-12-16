/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resourse_manager_utils01.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 13:18:15 by jvoor             #+#    #+#             */
/*   Updated: 2020/12/16 13:18:19 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "resource_manager.h"
#include "instance_manager.h"
#include "sampler_manager.h"
#include "vector.h"
#include "utils.h"
#include "rt_error.h"
#include "math.h"

int				init_resource_manager(t_res_mngr *resource_manager,
										 t_rt *rt)
{
	resource_manager->scene = &rt->scene;
	resource_manager->sampler_manager = &rt->sampler_manager;
	resource_manager->rt_options = &rt->options;
	return (SUCCESS);
}

t_instance_info	get_object_info(t_res_mngr *mngr, t_instance instance,
								   t_instance_extra extra)
{
	t_instance_info		info;
	t_obj				obj;

	info.type = instance.type;
	obj = mngr->scene->instance_mngr.objects[instance.object_id];
	info.material = instance.material;
	info.origin = extra.origin;
	info.height = obj.maxm;
	info.rotation = extra.rotation;
	info.scaling = extra.scaling;
	info.r = obj.r;
	info.r2 = obj.r2;
	info.texture = mngr->scene->instance_mngr.texture_manager.textures
	[instance.material.texture_id];
	info.v1 = obj.direction;
	info.v2 = obj.dir2;
	info.e = obj.angle;
	info.boolean = obj.shadows;
	return (info);
}
