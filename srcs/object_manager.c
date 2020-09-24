/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 13:22:40 by dmelessa          #+#    #+#             */
/*   Updated: 2020/09/23 16:21:56 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>

#include "libft.h"
#include "bool.h"
#include "instance_manager.h"
#include "utils.h"

static const t_triangle default_triangle;
static const t_obj default_obj;

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

	/**
	** @deprecated
	*/
	object.origin = (cl_float4){0.0f, 0.0f, 0.0f, 0.0f};
	object.r = object_info.r;
	object.r2 = object_info.r2;

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
int add_object(t_instance_manager *mngr, t_object_info object_info)
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
