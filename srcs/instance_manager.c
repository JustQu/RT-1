/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instance_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 19:52:25 by dmelessa          #+#    #+#             */
/*   Updated: 2020/08/09 22:35:42 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "instance_manager.h"
#include "libft.h"

#include <assert.h>

int			init_instance_manager(t_instance_manager *instance_manager)
{
	init_object_manager(&instance_manager->object_manager);
	init_matrix_manager(&instance_manager->matrix_manager);

	instance_manager->instances = malloc(sizeof(t_instance) * 100);
	assert(instance_manager->instances);
	ft_memset(instance_manager->instances, 0, sizeof(t_instance) * 100);
	instance_manager->malloc_size = sizeof(t_instance) * 100;
	instance_manager->ninstances = 0;
}

int			realloc_instance_manager(t_instance_manager *instance_manager,
									size_t size)
{
	t_instance	*new_mem;

	new_mem = malloc(size);
	assert(new_mem);
	ft_memcpy(new_mem, instance_manager->instances,
			instance_manager->ninstances * sizeof(t_instance));
	free(instance_manager->instances);
	instance_manager->instances = new_mem;
	instance_manager->malloc_size = size;
	return 0;
}

/**
** @brief Get the transformation matrix for object
** 1) scaling
** 2) rotation
** 3) translation
** @param object_info
** @return ** t_matrix
*/
t_matrix	get_transformation_matrix(t_object_info object_info)
{
	t_matrix	matrix;

	matrix = IDENTITY_MATRIX;
	matrix = mul_matrix(matrix,
						get_inverse_scale_matrix(object_info.scaling));
	matrix = mul_matrix(matrix,
						get_inverse_rotation_matrix(object_info.rotation));
	matrix = mul_matrix(matrix,
						get_inverse_translation_matrix(object_info.origin));
	return (matrix);
}

/**
** @brief Добавляем новый экземпляр объекта, на основне считанных данных
** @todo: Не создавать матрицу, если нет трансформации
** @param instance_manager
** @param type
** @return ** int
*/
int			add_instance(t_instance_manager *instance_manager,
						t_object_info object_info)
{
	t_instance	*new_memory;
	t_instance	new_instance;
	t_matrix	transformation_matrix;

	if (instance_manager->malloc_size
		< (instance_manager->ninstances + 1) * sizeof(t_instance))
	{
		realloc_instance_manager(instance_manager,
								instance_manager->malloc_size * 2);
	}
	//todo: do not create matrix if there is no tranformations
	transformation_matrix = get_transformation_matrix(object_info);
	new_instance.type = object_info.type;
	new_instance.material = object_info.material;
	new_instance.object_id = add_object(&instance_manager->object_manager,
										object_info);
	new_instance.matrix_id = add_matrix(&instance_manager->matrix_manager,
										transformation_matrix);
	instance_manager->instances[instance_manager->ninstances] = new_instance;
	return (++instance_manager->ninstances - 1);
}

t_instance	get_instance(t_instance_manager *instance_manager, int instance_id)
{
	return instance_manager->instances[instance_id];
}

void	change_instance(t_instance_manager *instance_manager, int instance_id,
						t_matrix matrix)
{
	t_instance	instance;
	t_matrix	new_matrix;

	instance = get_instance(instance_manager, instance_id);
	// if (instance.matrix_id == -1)
	// {
	// 	instance_manager->instances[instance_id].matrix_id =
	// 		add_matrix(instance_manager, matrix);
	// }
	// else
	// {
	// 	new_matrix = get_matrix(&instance_manager->matrix_manager,
	// 						instance.matrix_id);
	// 	new_matrix = mul_matrix(new_matrix, matrix);
	// 	instance_manager->matrix_manager.matrices[instance.matrix_id] =
	// 		 new_matrix;
	// }
}
