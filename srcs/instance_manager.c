/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instance_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 19:52:25 by dmelessa          #+#    #+#             */
/*   Updated: 2020/08/13 18:44:24 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "instance_manager.h"
#include "libft.h"

#include <assert.h>

/**
** @brief allocate memory with size = `new_size`
** and copy `current_size` bytes data from `mem` memory
** @todo: move to libft
** @param mem
** @param current_size
** @param new_size
** @return ** void*
*/
void		*ft_realloc(void *mem, size_t current_size, size_t new_size)
{
	void	*new_mem;

	new_mem = malloc(new_size);
	if (new_mem == NULL)
		return (NULL);
	ft_memcpy(new_mem, mem, current_size);
	free(mem);
	return (new_mem);
}

int			init_instance_manager(t_instance_manager *mngr)
{
	int	a;

	a = 100;
	*mngr = (t_instance_manager){ .ninstances = 0, .nobjects = 0,
		.ntriangles = 0, .nmatrices = 0,
		.instances_malloc_size = a * sizeof(t_instance),
		.objects_malloc_size = a * sizeof(t_obj),
		.triangles_malloc_size = a * sizeof(t_triangle),
		.matrices_malloc_size = a * sizeof(t_matrix)};
	// init_object_manager(&instance_manager->object_manager);
	// init_matrix_manager(&mngr->matrix_manager);
	mngr->instances = (t_instance *)ft_memalloc(mngr->instances_malloc_size);
	mngr->objects = (t_obj *)ft_memalloc(mngr->objects_malloc_size);
	mngr->triangles = (t_triangle *)ft_memalloc(mngr->triangles_malloc_size);
	mngr->matrices = (t_matrix *)ft_memalloc(mngr->matrices_malloc_size);
	assert(mngr->instances);
	assert(mngr->objects);
	assert(mngr->triangles);
	assert(mngr->matrices);
}

/**
** @brief Get the transformation matrix for object
** 1) scaling
** 2) rotation
** 3) translation
** @param object_info
** @return ** t_matrix
*/
t_matrix	get_transformation_matrix(t_object_info obj_info)
{
	t_matrix	m;
	cl_float3	test;

	m = IDENTITY_MATRIX;
	m = mul_matrix(m, get_inverse_scale_matrix(obj_info.scaling));
	m = mul_matrix(m, get_inverse_rotation_matrix(obj_info.rotation));
	m = mul_matrix(m, get_inverse_translation_matrix(obj_info.origin));
	return (m);
}

/**
** @brief Добавляем новый экземпляр объекта, на основне считанных данных
** @todo: Не создавать матрицу, если нет трансформации
** @param instance_manager
** @param type
** @return ** int
*/
int			add_instance(t_instance_manager *mngr, t_object_info object_info)
{
	t_instance	*new_memory;
	t_instance	new_instance;
	t_matrix	transformation_matrix;

	if (mngr->instances_malloc_size
		< (mngr->ninstances + 1) * sizeof(t_instance))
	{
		mngr->instances = ft_realloc(mngr->instances,
			mngr->instances_malloc_size, mngr->instances_malloc_size * 2);
		mngr->instances_malloc_size *= 2;
	}
	//todo: do not create matrix if there is no tranformations
	transformation_matrix = get_transformation_matrix(object_info);
	new_instance.type = object_info.type;
	new_instance.material = object_info.material;
	new_instance.object_id = add_object(mngr, object_info);
	new_instance.matrix_id = add_matrix(mngr, transformation_matrix);
	mngr->instances[mngr->ninstances] = new_instance;
	return (++mngr->ninstances - 1);
}

t_instance	get_instance(t_instance_manager *instance_manager, int instance_id)
{
	return instance_manager->instances[instance_id];
}
