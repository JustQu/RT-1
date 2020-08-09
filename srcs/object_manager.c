/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 13:22:40 by dmelessa          #+#    #+#             */
/*   Updated: 2020/08/09 18:59:20 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>

#include "libft.h"
#include "bool.h"
#include "object_manager.h"

static const t_triangle default_triangle;
static const t_obj default_obj;

/**
** @brief Инициализируем object_manager
** Выделяем память на 100 объектов и 100 треугольников.
**
** @param object_manager
** @return ** int
*/
int init_object_manager(t_object_manager *object_manager)
{
	size_t malloc_size;

	malloc_size = 100;
	object_manager->objects = malloc(sizeof(t_obj) * malloc_size);
	assert(object_manager->objects);
	ft_memset(object_manager->objects, 0, malloc_size * sizeof(t_obj));
	object_manager->triangles = malloc(sizeof(t_triangle) * malloc_size);
	assert(object_manager->triangles);
	ft_memset(object_manager->triangles, 0, sizeof(t_triangle) * malloc_size);
	object_manager->objects_malloc_size = sizeof(t_obj) * malloc_size;
	object_manager->triangles_malloc_size = sizeof(t_triangle) * malloc_size;
	object_manager->nobjects = 0;
	object_manager->ntriangles = 0;
	return (0);
}

int	add_triangle(t_object_manager *object_manager, t_object_info object_info)
{
	t_triangle	*new_mem;
	t_triangle	triangle;

	if (object_manager->triangles_malloc_size
		< (object_manager->ntriangles + 1) * sizeof(t_triangle))
	{
		new_mem = malloc(object_manager->triangles_malloc_size * 2);
		assert(new_mem);
		ft_memcpy(new_mem, object_manager->triangles, object_manager->ntriangles * sizeof(t_triangle));
		free(object_manager->triangles);
		object_manager->triangles = new_mem;
		object_manager->triangles_malloc_size *= 2;
	}
	triangle.material = object_info.material;
	triangle.vertex1 = object_info.origin;
	// triangle.vector1 = obbject_info.vertex2-object_info.vertex1
	triangle.vector1 = object_info.vector1;
	triangle.vector2 = object_info.vector2;
	// todo: triangle.normal =
	object_manager->triangles[object_manager->ntriangles] = triangle;
	return (++object_manager->ntriangles - 1);
}

int		add_obj(t_object_manager *object_manager, t_object_info object_info)
{
	t_obj	*new_mem;
	t_obj	object;

	if (object_manager->objects_malloc_size
		< (object_manager->nobjects + 1) * sizeof(t_obj))
	{
		new_mem = malloc(object_manager->objects_malloc_size * 2);
		assert(new_mem);
		ft_memcpy(new_mem, object_manager->objects, object_manager->nobjects * sizeof(t_obj));
		free(object_manager->objects);
		object_manager->objects = new_mem;
		object_manager->objects_malloc_size *= 2;
	}
	// object.material = object_info.material;
	object.minm = object_info.minm;
	object.maxm = object_info.maxm;

	/**
	** @deprecated
	*/
	object.origin = (cl_float4){0.0f, 0.0f, 0.0f, 0.0f};
	object.direction = object_info.direction;
	object.r = object_info.r;
	object.r2 = object_info.r2;
	object.shadows = TRUE;

	printf("\t\tOrigin:\t\t(%f, %f, %f, %f)\n", object.origin.x, object.origin.y, object.origin.z, object.origin.w);
	printf("\t\tDirection:\t(%f, %f, %f, %f)\n", object.direction.x, object.direction.y, object.direction.z, object.direction.w);
	printf("\t\tRadius: %f\n", object.r);

	object_manager->objects[object_manager->nobjects] = object;
	return (++object_manager->nobjects - 1);
}

/**
** @brief Добавить новый объект типа type
** Возвращает id объекта
** @param object_manager
** @param type
** @return ** int
*/
int add_object(t_object_manager *object_manager, t_object_info object_info)
{
	if (object_info.type == triangle)
	{
		return	add_triangle(object_manager, object_info);
	}
	else
	{
		return	add_obj(object_manager, object_info);
	}
	//mesh obj???
}
