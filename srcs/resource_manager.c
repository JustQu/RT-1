/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resource_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 16:55:21 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/13 12:34:04 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "resource_manager.h"
#include "instance_manager.h"
#include "sampler_manager.h"
#include "vector.h"
#include "utils.h"

#include "math.h"

#define DEG2RAD M_PI / 360.0f

/*
** @brief Create inverse transformation matrix for object
** 1) scaling
** 2) rotation
** 3) translation
** @param object_info
** @return ** t_matrix
*/

t_matrix		create_inv_transformation_matrix(t_instance_info info)
{
	t_matrix	m;

	m = IDENTITY_MATRIX;
	m = mul_matrix(m, get_inverse_scale_matrix(info.scaling));
	m = mul_matrix(m, get_inverse_rotation_matrix(info.rotation));
	m = mul_matrix(m, get_inverse_translation_matrix(info.origin));
	return (m);
}

int				add_instance(t_res_mngr *res_mngr,
							t_instance_manager *mngr, t_instance_info data)
{
	t_instance	new;

	if (mngr->instances_malloc_size <
		(mngr->ninstances + 1) * sizeof(*mngr->instances))
	{
		mngr->instances = ft_realloc(mngr->instances,
									mngr->instances_malloc_size,
									mngr->instances_malloc_size * 2);
		mngr->instances_malloc_size *= 2;
		mngr->extra = ft_realloc(mngr->extra, mngr->extra_size,
								mngr->extra_size * 2);
		mngr->extra_size *= 2;
	}
	new.type = data.type;
	new.material = data.material;
	new.object_id = add_object(mngr, data);
	new.matrix_id = add_matrix(mngr, create_inv_transformation_matrix(data));
	new.material.texture_id = add_texture(
			&res_mngr->scene->instance_mngr.texture_manager, data.texture);
	mngr->instances[mngr->ninstances] = new;
	mngr->extra[mngr->ninstances].aabb = compute_aabb(data);
	mngr->extra[mngr->ninstances].origin = data.origin;
	mngr->extra[mngr->ninstances].rotation = data.rotation;
	mngr->extra[mngr->ninstances].scaling = data.scaling;
	return (++mngr->ninstances - 1);
}

float			compute_area(t_instance_info info)
{
	float	s;

	s = 0.0f;
	if (info.type == rectangle)
	{
		s = info.r * info.r2 * info.scaling.x * info.scaling.y;
	}
	return (s);
}

void			add_emissive_instance(t_res_mngr *mngr, t_instance_info data)
{
	int				i;
	int				j;
	t_parsed_light	l;

	if (data.material.type == emissive
		&& data.type == rectangle)
	{
		i = add_instance(mngr, &mngr->scene->instance_mngr, mngr->info);
		set_sampler(&mngr->scene->instance_mngr, i,
					new_sampler(mngr->sampler_manager, nrooks,
								1024, DEFAULT_SAMPLES));
		l.ls = data.material.ls;
		l.color = data.texture.data.solid.color;
		l.type = area;
		l.pdf = 1.0f / compute_area(data);
		j = add_parsed_light(&mngr->scene->light_manager, l);
		mngr->scene->light_manager.lights[j].object_id = i;
		mngr->scene->light_manager.lights[j].matrix =
			get_transformation_matrix(mngr->info);
	}
	else
	{
		data.material.type = matte;
		add_instance(mngr, &mngr->scene->instance_mngr, mngr->info);
	}
}

int				init_resource_manager(t_res_mngr *resource_manager, t_rt *rt)
{
	resource_manager->scene = &rt->scene;
	resource_manager->sampler_manager = &rt->sampler_manager;
	resource_manager->rt_options = &rt->options;
	return (SUCCESS);
}

void			scan_instance(t_res_mngr *const mngr, t_parsed_info asset)
{
	mngr->info.type = asset.data.object.type;
	mngr->info.origin = asset.data.object.origin;
	mngr->info.rotation = asset.data.object.rotation;
	mngr->info.scaling = asset.data.object.scaling;
	mngr->info.material = asset.data.object.material;
	mngr->info.texture = asset.data.object.texture;
	mngr->info.height = asset.data.object.maxm;
	mngr->info.r = asset.data.object.r;
	mngr->info.boolean = asset.data.object.boolean;
	if (mngr->info.type == sphere)
	{
		mngr->info.scaling.x *= mngr->info.r;
		mngr->info.scaling.y *= mngr->info.r;
		mngr->info.scaling.z *= mngr->info.r;
		mngr->info.r = 1.0f;
	}
	if (mngr->info.type == cylinder)
	{
		mngr->info.scaling.x *= mngr->info.r;
		mngr->info.scaling.y *= mngr->info.r;
		mngr->info.r = 1.0f;
	}
	mngr->info.r2 = asset.data.object.r2;
	if (mngr->info.type == cone)
		mngr->info.r2 = pow(tanf(asset.data.object.r2 * DEG2RAD), 2) + 1.0f;
	mngr->info.v1 = asset.data.object.vector1;
	mngr->info.v2 = asset.data.object.vector2;
	if (mngr->info.type == rectangle)
	//normalize vectors if it is rectangle
	{
		mngr->info.v1 = (mngr->info.v1);
		mngr->info.v2 = (mngr->info.v2);
	}
}

/*
** @brief Get the instance info object
** @todo: check array boundaries
** @param mngr
** @param id
** @return **** t_instance_info
*/

t_instance_info	get_instance_info(t_res_mngr *mngr, int id)
{
	t_instance_info	info;

	info.type = mngr->scene->instance_mngr.instances[id].type;
	return (info);
}

void			add_parsed_asset(t_res_mngr *const mngr, t_parsed_info asset)
{
	if (asset.type == object)
	{
		scan_instance(mngr, asset);
		if (mngr->info.material.type == emissive)
		{
			add_emissive_instance(mngr, mngr->info);
		}
		else
		{
			add_instance(mngr, &mngr->scene->instance_mngr, mngr->info);
		}
	}
	else if (asset.type == light)
	{
		add_parsed_light(&mngr->scene->light_manager, asset.data.light);
	}
}
