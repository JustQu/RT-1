/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 16:23:02 by dmelessa          #+#    #+#             */
/*   Updated: 2020/08/13 20:00:34 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include "math.h"

/**
** @brief Print matrix in stdout
**
** @param matrix
** @return ** void
*/
void print_matrix(t_matrix matrix)
{
	int i;

	i = 0;
	while (i < 16)
	{
		printf("%f ", matrix.s[i]);
		if (i == 3 || i == 7 || i == 11 || i == 15)
			printf("\n");
		i++;
	}
}

/**
** @brief Identity matrix
**
*/
static const t_matrix g_default_matrix = {
	.s0 = 1.0f, .s1 = 0.0f, .s2 = 0.0f, .s3 = 0.0f,
	.s4 = 0.0f, .s5 = 1.0f, .s6 = 0.0f, .s7 = 0.0f,
	.s8 = 0.0f, .s9 = 0.0f, .sA = 1.0f, .sB = 0.0f,
	.sC = 0.0f, .sD = 0.0f, .sE = 0.0f, .sF = 1.0f
};

/**
** @brief Multiplication of two matrices
**
** @param A
** @param B
** @return ** t_matrix
*/
t_matrix mul_matrix(t_matrix A, t_matrix B)
{
	t_matrix C;
	int i;
	int j;

	i = 0;
	while (i < 16)
	{
		C.s[i] = A.s[i / 4 * 4] * B.s[i % 4]
				+ A.s[i / 4 * 4 + 1] * B.s[i % 4 + 4]
				+ A.s[i / 4 * 4 + 2] * B.s[i % 4 + 8]
				+ A.s[i / 4 * 4 + 3] * B.s[i % 4 + 12];
		++i;
	}
	return (C);
}

/**
** @brief create scale matrix from vector
**
** vector.x		0			0			0
** 0			vector.y	0			0
** 0			0			vector.z	0
** 0			0			0			1
**
** @param scale
** @return ** t_matrix
*/
t_matrix scale_matrix(cl_float4 scale)
{
	t_matrix matrix;

	matrix = g_default_matrix;
	matrix.s[0] = scale.s[0];
	matrix.s[5] = scale.s[1];
	matrix.s[10] = scale.s[2];
	return (matrix);
}

/**
** @brief Create translation matrix from vector
**
** 1	0	0	vector.x
** 0	1	0	vector.y
** 0	0	1	vector.z
** 0	0	0	1
**
** @param origin
** @return ** t_matrix
*/
t_matrix move_matrix(cl_float4 origin)
{
	t_matrix matrix;

	matrix = g_default_matrix;
	matrix.s[3] = origin.s[0];
	matrix.s[7] = origin.s[1];
	matrix.s[11] = origin.s[2];
	return (matrix);
}

/**
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
t_matrix x_rotate(cl_float angle)
{
	t_matrix matrix;

	matrix = g_default_matrix;
	matrix.s[5] = cos(angle);
	matrix.s[6] = -sin(angle);
	matrix.s[9] = sin(angle);
	matrix.s[10] = cos(angle);
	return (matrix);
}

/**
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
t_matrix y_rotate(cl_float angle)
{
	t_matrix matrix;

	matrix = g_default_matrix;
	matrix.s[0] = cos(angle);
	matrix.s[2] = sin(angle);
	matrix.s[8] = -sin(angle);
	matrix.s[10] = cos(angle);
	return (matrix);
}

/**
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
t_matrix z_rotate(cl_float angle)
{
	t_matrix matrix;

	matrix = g_default_matrix;
	matrix.s[0] = cos(angle);
	matrix.s[1] = -sin(angle);
	matrix.s[4] = sin(angle);
	matrix.s[5] = cos(angle);
	return (matrix);
}

/**
** @brief Get rotation matrix around all axis
**
** @param rotate store angles of rotations around axis
** @return ** t_matrix
*/
t_matrix rotate_matrix(cl_float4 rotate)
{
	t_matrix matrix;

	matrix = g_default_matrix;
	matrix = mul_matrix(matrix, x_rotate(rotate.s[0]));
	matrix = mul_matrix(matrix, y_rotate(rotate.s[1]));
	matrix = mul_matrix(matrix, z_rotate(rotate.s[2]));
	return (matrix);
}

/**
** @brief Get the inverse x rotation matrix object
**
** @param angle
** @return ** t_matrix
*/
t_matrix get_inverse_x_rotation_matrix(float angle)
{
	float sina;
	float cosa;

	cosa = cos(angle * M_PI / 180.0f);
	sina = sin(angle * M_PI / 180.0f);
	return (t_matrix){
		.s0 = 1.0f, .s1 = 0.0f, .s2 = 0.0f, .s3 = 0.0f,
		.s4 = 0.0f, .s5 = cosa, .s6 = sina, .s7 = 0.0f,
		.s8 = 0.0f, .s9 = -sina, .sA = cosa, .sB = 0.0f,
		.sC = 0.0f, .sD = 0.0f, .sE = 0.0f, .sF = 1.0f};
}

/**
** @brief Get the inverse y rotation matrix object
**
** @param angle
** @return ** t_matrix
*/
t_matrix get_inverse_y_rotation_matrix(float angle)
{
	float sina;
	float cosa;

	cosa = cos(angle * M_PI / 180.0f);
	sina = sin(angle * M_PI / 180.0f);
	return (t_matrix){
		.s0 = cosa, .s1 = 0.0f, .s2 = -sina, .s3 = 0.0f,
		.s4 = 0.0f, .s5 = 1.0f, .s6 = 0.0f, .s7 = 0.0f,
		.s8 = sina, .s9 = 0.0f, .sA = cosa, .sB = 0.0f,
		.sC = 0.0f, .sD = 0.0f, .sE = 0.0f, .sF = 1.0f};
}

/**
** @brief Get the inverse z rotation matrix object
**
** @param angle
** @return ** t_matrix
*/
t_matrix get_inverse_z_rotation_matrix(float angle)
{
	float sina;
	float cosa;

	cosa = cos(angle * M_PI / 180.0f);
	sina = sin(angle * M_PI / 180.0f);
	return (t_matrix){
		.s0 = cosa, .s1 = sina, .s2 = 0.0f, .s3 = 0.0f,
		.s4 = -sina, .s5 = cosa, .s6 = 0.0f, .s7 = 0.0f,
		.s8 = 0.0f, .s9 = 0.0f, .sA = 1.0f, .sB = 0.0f,
		.sC = 0.0f, .sD = 0.0f, .sE = 0.0f, .sF = 1.0f};
}

/**
** @brief Get the inverse rotation matrix object
**
** @param v
** @return ** t_matrix
*/
t_matrix	get_inverse_rotation_matrix(cl_float3 v)
{
	t_matrix	matrix;

	matrix = get_inverse_x_rotation_matrix(v.x);
	matrix = mul_matrix(matrix, get_inverse_y_rotation_matrix(v.y));
	matrix = mul_matrix(matrix, get_inverse_z_rotation_matrix(v.z));
	return (matrix);
}

/**
** @brief Get the inverse translation matrix object
**
** @param v
** @return ** t_matrix
*/
t_matrix get_inverse_translation_matrix(cl_float3 v)
{
	t_matrix matrix;

	matrix = g_default_matrix;
	matrix.s3 = -v.x;
	matrix.s7 = -v.y;
	matrix.sB = -v.z;
	return (matrix);
}

/**
** @brief Get the inverse scale matrix object
**
** @param v
** @return ** t_matrix
*/
t_matrix get_inverse_scale_matrix(cl_float3 v)
{
	return (t_matrix){
		.s0 = 1.0f / v.x, .s1 = 0.0f, .s2 = 0.0f, .s3 = 0.0f,
		.s4 = 0.0f, .s5 = 1.0f / v.y, .s6 = 0.0f, .s7 = 0.0f,
		.s8 = 0.0f, .s9 = 0.0f, .sA = 1.0f / v.z, .sB = 0.0f,
		.sC = 0.0f, .sD = 0.0f, .sE = 0.0f, .sF = 1.0f};
}
