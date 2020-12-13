/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 18:15:15 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/13 12:24:41 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include "instance_manager.h"
#include "utils.h"
#include "rt_error.h"
#include "libft.h"

int			add_matrix(t_instance_manager *mngr, t_matrix matrix)
{
	t_matrix	*new_memory;

	if (mngr->matrices_malloc_size
		< (mngr->nmatrices + 1) * sizeof(t_matrix))
	{
		mngr->matrices = (t_matrix *)ft_realloc(mngr->matrices,
			mngr->matrices_malloc_size, mngr->matrices_malloc_size * 2);
		rt_is_dead(system_err, system_malloc_error, !mngr->matrices, "");
		mngr->matrices_malloc_size *= 2;
	}
	mngr->matrices[mngr->nmatrices] = matrix;
	return (++mngr->nmatrices - 1);
}
