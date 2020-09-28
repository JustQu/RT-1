/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 12:47:05 by dmelessa          #+#    #+#             */
/*   Updated: 2020/09/26 15:15:34 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include "rt_types.h"

typedef cl_float16				t_matrix;

#define IDENTITY_MATRIX (t_matrix){1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1}
#define ZERO_MATRIX (t_matrix){0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}

void		print_matrix(t_matrix matrix);

t_matrix	mul_matrix(t_matrix A, t_matrix B);

t_matrix	get_x_rotation_matrix(float angle);
t_matrix	get_y_rotation_matrix(float angle);
t_matrix	get_z_rotation_matrix(float angle);
t_matrix	get_inverse_x_rotation_matrix(float angle);
t_matrix	get_inverse_y_rotation_matrix(float angle);
t_matrix	get_inverse_z_rotation_matrix(float angle);

t_matrix	get_scale_matrix(cl_float3 scaling);
t_matrix	get_rotation_matrix(cl_float3 rotation);
t_matrix	get_translation_matrix(cl_float3 translation);

t_matrix	get_inverse_scale_matrix(cl_float3 scaling);
t_matrix	get_inverse_rotation_matrix(cl_float3 rotation);
t_matrix	get_inverse_translation_matrix(cl_float3 translation);

#endif
