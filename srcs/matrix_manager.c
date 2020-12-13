/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 18:15:15 by dmelessa          #+#    #+#             */
/*   Updated: 2020/11/14 01:59:27 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include "instance_manager.h"
#include "utils.h"
#include "rt_err.h"
#include "libft.h"

int			add_matrix(t_instance_manager *mngr, t_matrix matrix)
{
	t_matrix	*new_memory;

	if (mngr == NULL)
		rt_error("add_matrix()L given NULL pointer");
	if (mngr->matrices_malloc_size
		< (mngr->nmatrices + 1) * sizeof(t_matrix))
	{
		mngr->matrices = (t_matrix *)ft_realloc(mngr->matrices,
			mngr->matrices_malloc_size, mngr->matrices_malloc_size * 2);
		mngr->matrices_malloc_size *= 2;
		if (mngr->matrices == NULL)
			rt_error("add_matrix: malloc error");
	}
	mngr->matrices[mngr->nmatrices] = matrix;
	return (++mngr->nmatrices - 1);
}
