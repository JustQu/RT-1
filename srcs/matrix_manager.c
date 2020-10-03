/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 18:15:15 by dmelessa          #+#    #+#             */
/*   Updated: 2020/09/30 00:54:40 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include "instance_manager.h"
#include "utils.h"

#include "libft.h"
#include <assert.h>

int			add_matrix(t_instance_manager *mngr, t_matrix matrix)
{
	t_matrix	*new_memory;

	if (mngr->matrices_malloc_size
		< (mngr->nmatrices + 1) * sizeof(t_matrix))
	{
		mngr->matrices = (t_matrix *)ft_realloc(mngr->matrices,
			mngr->matrices_malloc_size, mngr->matrices_malloc_size * 2);
		mngr->matrices_malloc_size *= 2;
		assert(mngr->matrices);
	}
	mngr->matrices[mngr->nmatrices] = matrix;
	return (++mngr->nmatrices - 1);
}

int			set_matrix(t_instance_manager *mngr, int matrix_id, t_matrix new_matrix)
{
	mngr->matrices[matrix_id] = new_matrix;
	return (0);
}

t_matrix	get_matrix(t_instance_manager *mngr, int matrix_id)
{
	return mngr->matrices[matrix_id];
}

t_matrix	get_transformation_matrix(t_instance_manager mngr, int instance_id)
{
	t_object_info	object_info;
	t_matrix		m;

	object_info = mngr.instances_info[instance_id];
	m = IDENTITY_MATRIX;
	m = mul_matrix(m, get_translation_matrix(object_info.origin));
	m = mul_matrix(m, get_rotation_matrix(object_info.rotation));
	m = mul_matrix(m, get_scale_matrix(object_info.scaling));
	return (m);
}
