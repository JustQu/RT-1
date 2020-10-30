/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resource_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 16:55:21 by dmelessa          #+#    #+#             */
/*   Updated: 2020/10/28 20:27:42 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "resource_manager.h"

void	add_parsed(t_res_mngr *const mngr, t_parsed_info asset)
{
	t_parsed_light	l;
	int				i;
	int				j;

	if (asset.type == object)
	{
		asset.data.object.material.texture_id = add_texture(
									&mngr->scene->instance_mngr.texture_manager,
									asset.data.object.texture);
		i = add_parsed_object(&mngr->scene->instance_mngr, asset.data.object);
		if (asset.data.object.material.type == emissive
			&& asset.data.object.type == rectangle)
		{
			l.ls = asset.data.object.material.ls;
			l.color = asset.data.object.texture.data.solid.color;
			l.type = area;
			j = add_parsed_light(&mngr->scene->light_manager, l);
			mngr->scene->light_manager.lights[j].object_id = i;
			mngr->scene->light_manager.lights[j].matrix =
				get_transformation_matrix(mngr->scene->instance_mngr, i);
		}
	}
	else if (asset.type == light)
	{
		add_parsed_light(&mngr->scene->light_manager, asset.data.light);
	}
	else if (asset.type == material)
	{

	}
	else if (asset.type == texture)
	{
	}
}