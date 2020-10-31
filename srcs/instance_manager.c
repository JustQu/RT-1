/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instance_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 19:52:25 by dmelessa          #+#    #+#             */
/*   Updated: 2020/10/30 21:06:08 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "instance_manager.h"
#include "libft.h"
#include "utils.h"
#include "math.h"

#include <assert.h>

int			init_instance_manager(t_instance_manager *mngr)
{
	int	a;

	a = 1;
	*mngr = (t_instance_manager){ .ninstances = 0, .nobjects = 0,
		.ntriangles = 0, .nmatrices = 0,
		.instances_malloc_size = a * sizeof(t_instance),
		.objects_malloc_size = a * sizeof(t_obj),
		.triangles_malloc_size = a * sizeof(t_triangle),
		.matrices_malloc_size = a * sizeof(t_matrix),
		.instances_info_malloc_size = a * sizeof(t_object_info)};
	init_texture_manager(&mngr->texture_manager);
	mngr->instances = (t_instance *)ft_memalloc(mngr->instances_malloc_size);
	mngr->objects = (t_obj *)ft_memalloc(mngr->objects_malloc_size);
	mngr->triangles = (t_triangle *)ft_memalloc(mngr->triangles_malloc_size);
	mngr->matrices = (t_matrix *)ft_memalloc(mngr->matrices_malloc_size);
	mngr->instances_info = (t_object_info *)ft_memalloc(mngr->instances_info_malloc_size);
	assert(mngr->instances);
	assert(mngr->objects);
	assert(mngr->triangles);
	assert(mngr->matrices);
	assert(mngr->instances_info_malloc_size);
}

/**
** @brief Get inverse transformation matrix for object
** 1) scaling
** 2) rotation
** 3) translation
** @param object_info
** @return ** t_matrix
*/
t_matrix	create_transformation_matrix(t_object_info obj_info)
{
	t_matrix	m;
	cl_float3	test;

	m = IDENTITY_MATRIX;
	m = mul_matrix(m, get_inverse_scale_matrix(obj_info.scaling));
	m = mul_matrix(m, get_inverse_rotation_matrix(obj_info.rotation));
	m = mul_matrix(m, get_inverse_translation_matrix(obj_info.origin));
	return (m);
}

int		set_object_info(t_object_info *object_info,
								t_parsed_object parsed_object)
{
	object_info->type = parsed_object.type;
	object_info->origin = parsed_object.origin;
	object_info->rotation = parsed_object.rotation;
	object_info->scaling = parsed_object.scaling;
	object_info->direction = parsed_object.direction;
	object_info->vector1 = parsed_object.vector1;
	object_info->vector2 = parsed_object.vector2;
	object_info->r = parsed_object.r;
	object_info->r2 = parsed_object.r2;
	if (parsed_object.type == cone)
	{
		object_info->r2 = tanf(parsed_object.r2 * M_PI / 360.0f);
		object_info->r2 = object_info->r2 * object_info->r2 + 1;
	}
	object_info->bounding_box.min = parsed_object.vector1;
	object_info->bounding_box.max = parsed_object.vector2;
	object_info->minm = parsed_object.minm;
	object_info->maxm = parsed_object.maxm;
}

/**
** @brief Добавляем новый экземпляр объекта, на основне считанных данных
** @todo: Не создавать матрицу, если нет трансформации
** @param instance_mngr
** @param type
** @return ** int
*/
int		add_parsed_object(t_instance_manager *mngr, t_parsed_object parsed_object)
{
	t_instance		new_instance;
	t_object_info	object_info;
	t_matrix		transformation_matrix;

	if (mngr->instances_malloc_size
		< (mngr->ninstances + 1) * sizeof(t_instance))
	{
		mngr->instances = ft_realloc(mngr->instances,
			mngr->instances_malloc_size, mngr->instances_malloc_size * 2);
		mngr->instances_malloc_size *= 2;
		mngr->instances_info = ft_realloc(mngr->instances_info,
			mngr->instances_info_malloc_size,
			mngr->instances_info_malloc_size * 2);
		mngr->instances_info_malloc_size *= 2;
	}
	set_object_info(&object_info, parsed_object);
	transformation_matrix = create_transformation_matrix(object_info);
	new_instance.type = parsed_object.type;
	new_instance.material = parsed_object.material;
	new_instance.object_id = add_object(mngr, object_info);
	new_instance.matrix_id = add_matrix(mngr, transformation_matrix);
	mngr->instances[mngr->ninstances] = new_instance;
	mngr->instances_info[mngr->ninstances] = object_info;
	return (++mngr->ninstances - 1);
}

t_instance	get_instance(t_instance_manager *instance_manager, int instance_id)
{
	return instance_manager->instances[instance_id];
}

t_matrix	get_instance_matrix(t_instance_manager instance_mngr, int instance_id)
{
	return (instance_mngr.matrices[instance_mngr.instances[instance_id].matrix_id]);
}
