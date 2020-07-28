/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 12:47:05 by dmelessa          #+#    #+#             */
/*   Updated: 2020/07/28 15:47:41 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

#include "types.h"

typedef cl_float16	t_matrix;

typedef struct s_matrix_manager	t_matrix_manager;
struct	s_matrix_manager
{
	t_matrix		*matrices;
	unsigned int	nmatrices;
	size_t			malloc_size;
};

void	add_matrix(t_matrix_manager *manager, t_matrix matrix);
void	get_matrix(t_matrix_manager *manager, unsigned int matrix_id);
void	delete_matrix(t_matrix_manager *manager, unsigned int matrix_id);

#endif
