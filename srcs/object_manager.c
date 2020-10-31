/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 13:22:40 by dmelessa          #+#    #+#             */
/*   Updated: 2020/10/30 19:31:42 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>

#include "libft.h"
#include "bool.h"
#include "instance_manager.h"
#include "utils.h"

static const t_triangle	default_triangle;
static const t_obj		default_obj;

int	add_triangle(t_instance_manager *mngr, t_object_info triangle_info)
{
	t_triangle	triangle;

	if (mngr->triangles_malloc_size
		< (mngr->ntriangles + 1) * sizeof(t_triangle))
	{
		mngr->triangles = (t_triangle *)ft_realloc(mngr->triangles,
			mngr->triangles_malloc_size, mngr->triangles_malloc_size * 2);
		mngr->triangles_malloc_size *= 2;
		assert(mngr->triangles);
	}
	// triangle.material = object_info.material;
	triangle.vertex1 = triangle_info.origin;
	// triangle.vector1 = obbject_info.vertex2-triangle_info.vertex1
	triangle.vector1 = triangle_info.vector1;
	triangle.vector2 = triangle_info.vector2;
	// todo: triangle.normal =
	mngr->triangles[mngr->ntriangles] = triangle;
	return (++mngr->ntriangles - 1);
}

//TODO(dmelessa): check if the object already in array
int		add_obj(t_instance_manager *mngr, t_object_info object_info)
{
	t_obj	object;

	if (mngr->objects_malloc_size < (mngr->nobjects + 1) * sizeof(t_obj))
	{
		mngr->objects = (t_obj *)ft_realloc(mngr->objects,
			mngr->objects_malloc_size, mngr->objects_malloc_size * 2);
		mngr->objects_malloc_size *= 2;
		assert(mngr->objects);
	}
	object.minm = object_info.minm;
	object.maxm = object_info.maxm;
	object.shadows = TRUE;

	object.origin = (cl_float4){0.0f, 0.0f, 0.0f, 0.0f};
	object.r = object_info.r;
	object.r2 = object_info.r2;
	object.bounding_box = object_info.bounding_box;
	object.direction = object_info.vector1;
	object.dir2 = object_info.vector2;

	/* for rectangle */
	object.normal = (cl_float4){ .x = 0.0f, .y = 0.0f, .z = 1.0f, .w = 0.0f};

	mngr->objects[mngr->nobjects] = object;
	return (++mngr->nobjects - 1);
}

/**
** @brief Добавить новый объект типа type
** Возвращает id объекта
** @param instance_manager
** @param object_info
** @return ** int
*/
int		add_object(t_instance_manager *mngr, t_object_info object_info)
{
	if (object_info.type == triangle)
	{
		return	add_triangle(mngr, object_info);
	}
	else
	{
		return	add_obj(mngr, object_info);
	}
	//mesh obj???
}

void
set_sampler(t_instance_manager *instance_manager,
			int id,
			int sampler_id)
{
	instance_manager->objects[instance_manager->instances[id].object_id].sampler_id = sampler_id;
}
