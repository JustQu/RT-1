/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_01.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 15:22:03 by jvoor             #+#    #+#             */
/*   Updated: 2020/12/17 15:22:04 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include <math.h>

/*
** @brief Get rotation matrix around x axis by angle a
**
** 1	0		0		0
** 0	cos(a)	-sin(a)	0
** 0	sin(a)	cos(a)	0
** 0	0		0		1
**
** @param angle
** @return ** t_matrix
*/

t_matrix	get_x_rotation_matrix(cl_float angle)
{
	t_matrix	matrix;

	matrix = g_default_matrix;
	matrix.s[5] = cos(angle * M_PI / 180.0f);
	matrix.s[6] = -sin(angle * M_PI / 180.0f);
	matrix.s[9] = sin(angle * M_PI / 180.0f);
	matrix.s[10] = cos(angle * M_PI / 180.0f);
	return (matrix);
}

/*
** @brief Get rotation matrix around y axis by angle a
**
** cos(a)	0	sin(a)	0
** 0		1	0		0
** -sin(a)	0	cos(a)	0
** 0		0	0		1
**
** @param angle
** @return ** t_matrix
*/

t_matrix	get_y_rotation_matrix(cl_float angle)
{
	t_matrix	matrix;

	matrix = g_default_matrix;
	matrix.s[0] = cos(angle * M_PI / 180.0f);
	matrix.s[2] = sin(angle * M_PI / 180.0f);
	matrix.s[8] = -sin(angle * M_PI / 180.0f);
	matrix.s[10] = cos(angle * M_PI / 180.0f);
	return (matrix);
}

/*
** @brief Get rotation matrix around z axis by angle a
**
** cos(a)	-sin(a)	0	0
** sin(a)	cos(a)	0	0
** 0		0		1	0
** 0		0	0		1
**
** @param angle
** @return ** t_matrix
*/

t_matrix	get_z_rotation_matrix(cl_float angle)
{
	t_matrix	matrix;

	matrix = g_default_matrix;
	matrix.s[0] = cos(angle * M_PI / 180.0f);
	matrix.s[1] = -sin(angle * M_PI / 180.0f);
	matrix.s[4] = sin(angle * M_PI / 180.0f);
	matrix.s[5] = cos(angle * M_PI / 180.0f);
	return (matrix);
}

/*
** @brief Get rotation matrix around all axis
**
** @param rotate store angles of rotations around axis
** @return ** t_matrix
*/

t_matrix	rotate_matrix(cl_float4 rotate)
{
	t_matrix	matrix;

	matrix = g_default_matrix;
	matrix = mul_matrix(matrix, get_x_rotation_matrix(rotate.s[0]));
	matrix = mul_matrix(matrix, get_y_rotation_matrix(rotate.s[1]));
	matrix = mul_matrix(matrix, get_z_rotation_matrix(rotate.s[2]));
	return (matrix);
}

/*
** @brief Get the inverse x rotation matrix object
**
** @param angle
** @return ** t_matrix
*/

t_matrix	get_inverse_x_rotation_matrix(float angle)
{
	float	sina;
	float	cosa;

	cosa = cos(angle * M_PI / 180.0f);
	sina = sin(angle * M_PI / 180.0f);
	return (t_matrix){
			.s0 = 1.0f, .s1 = 0.0f, .s2 = 0.0f, .s3 = 0.0f,
			.s4 = 0.0f, .s5 = cosa, .s6 = sina, .s7 = 0.0f,
			.s8 = 0.0f, .s9 = -sina, .sA = cosa, .sB = 0.0f,
			.sC = 0.0f, .sD = 0.0f, .sE = 0.0f, .sF = 1.0f};
}
