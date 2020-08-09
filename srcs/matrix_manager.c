/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 18:15:15 by dmelessa          #+#    #+#             */
/*   Updated: 2020/08/06 19:37:35 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix_manager.h"

#include "libft.h"
#include <assert.h>

int			init_matrix_manager(t_matrix_manager *matrix_manager)
{
	size_t	malloc_size;

	malloc_size = 100;
	matrix_manager->malloc_size = malloc_size * sizeof(t_matrix);
	matrix_manager->matrices = malloc(sizeof(t_matrix) * malloc_size);
	assert(matrix_manager->matrices);
	matrix_manager->nmatrices = 0;
	return (0);
}

int			add_matrix(t_matrix_manager *matrix_manager, t_matrix matrix)
{
	t_matrix	*new_memory;

	if (matrix_manager->malloc_size < (matrix_manager->nmatrices + 1) * sizeof(t_matrix))
	{
		new_memory = malloc(sizeof(t_matrix) * matrix_manager->nmatrices * 2);
		assert(new_memory);
		ft_memcpy(new_memory, matrix_manager->matrices, matrix_manager->nmatrices);
		free(matrix_manager->matrices);
		matrix_manager->matrices = new_memory;
		matrix_manager->malloc_size = sizeof(t_matrix) * matrix_manager->nmatrices * 2;
	}
	matrix_manager->matrices[matrix_manager->nmatrices] = matrix;
	return (++matrix_manager->nmatrices - 1);
}

int			set_matrix(t_matrix_manager *matrix_manager, int matrix_id, t_matrix new_matrix)
{
	matrix_manager->matrices[matrix_id] = new_matrix;
	return (0);
}

t_matrix	get_matrix(t_matrix_manager *matrix_manager, int matrix_id)
{
	return matrix_manager->matrices[matrix_id];
}
