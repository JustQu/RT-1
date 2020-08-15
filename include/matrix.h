/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 12:47:05 by dmelessa          #+#    #+#             */
/*   Updated: 2020/08/13 18:54:19 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include "types.h"

typedef cl_float16				t_matrix;
typedef struct s_matrix_manager	t_matrix_manager;

#define IDENTITY_MATRIX (t_matrix){1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1}
#define ZERO_MATRIX (t_matrix){0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}

struct					s_matrix_manager
{
	t_matrix			*matrices;
	unsigned int		nmatrices;
	size_t				malloc_size;
};

void		print_matrix(t_matrix matrix);

t_matrix	mul_matrix(t_matrix A, t_matrix B);

t_matrix	get_x_rotation_matrix(float angle);
t_matrix	get_y_rotation_matrix(float angle);
t_matrix	get_z_rotation_matrix(float angle);
t_matrix	get_inverse_rotation_matrix(cl_float3 rotation);
t_matrix	get_inverse_x_rotation_matrix(float angle);
t_matrix	get_inverse_y_rotation_matrix(float angle);
t_matrix	get_inverse_z_rotation_matrix(float angle);
t_matrix	get_scale_matrix(float a, float b, float c);
t_matrix	get_inverse_scale_matrix(cl_float3 scaling);
t_matrix	get_translate_matrix(float x, float y, float z);
t_matrix	get_inverse_translation_matrix(cl_float3 translation);

#endif
