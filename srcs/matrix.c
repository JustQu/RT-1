/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 21:18:06 by marvin            #+#    #+#             */
/*   Updated: 2020/07/28 16:20:24 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include "objects.h"

void        print_matrix(t_matrix matrix)
{
    int     i;

    i = 0;
    while (i < 16)
    {
        printf("%f ", matrix.s[i]);
        if (i == 3 || i == 7 || i == 11 || i == 15)
            printf("\n");
        i++;
    }
}

t_matrix    mul_matrix(t_matrix A, t_matrix B)
{
    t_matrix    C;
    int     i;
    int     j;

    i = 0;
    while (i < 16)
    {
        C.s[i] = A.s[i / 4 * 4] * B.s[i % 4] + A.s[i / 4 * 4 + 1] * B.s[i % 4 + 4]
            + A.s[i / 4 * 4 + 2] * B.s[i % 4 + 8] + A.s[i / 4 * 4 + 3] * B.s[i % 4 + 12];
        ++i;
    }
    return (C);
}

t_matrix    default_matrix(void)
{
    int     i;
    t_matrix matrix;

    i = 0;
    while (i < 16)
    {
        matrix.s[i] = 0;
        if (i % 5 == 0)
            matrix.s[i] = 1;
        i++;
    }
    return (matrix);
}

t_matrix    scale_matrix(cl_float4 scale)
{
    t_matrix    matrix;

    matrix = default_matrix();
    matrix.s[0] = scale.s[0];
    matrix.s[5] = scale.s[1];
    matrix.s[10] = scale.s[2];
    return (matrix);
}

t_matrix    move_matrix(cl_float4 origin)
{
    t_matrix matrix;

    matrix = default_matrix();
    matrix.s[3] = origin.s[0];
    matrix.s[7] = origin.s[1];
    matrix.s[11] = origin.s[2];
    return (matrix);
}

t_matrix    x_rotate(cl_float angle)
{
    t_matrix matrix;

    matrix = default_matrix();
    matrix.s[5] = cos(angle);
    matrix.s[6] = -sin(angle);
    matrix.s[9] = sin(angle);
    matrix.s[10] = cos(angle);
    return (matrix);
}

t_matrix    y_rotate(cl_float angle)
{
    t_matrix matrix;

    matrix = default_matrix();
    matrix.s[0] = cos(angle);
    matrix.s[2] = sin(angle);
    matrix.s[8] = -sin(angle);
    matrix.s[10] = cos(angle);
    return (matrix);
}

t_matrix    z_rotate(cl_float angle)
{
    t_matrix matrix;

    matrix = default_matrix();
    matrix.s[0] = cos(angle);
    matrix.s[1] = -sin(angle);
    matrix.s[4] = sin(angle);
    matrix.s[5] = cos(angle);
    return (matrix);
}

t_matrix    rotate_matrix(cl_float4 rotate)
{
    t_matrix    matrix;

    matrix = default_matrix();
    matrix = mul_matrix(matrix, x_rotate(rotate.s[0]));
    matrix = mul_matrix(matrix, y_rotate(rotate.s[1]));
    matrix = mul_matrix(matrix, z_rotate(rotate.s[2]));
    return (matrix);
}

t_matrix    create_affin_matrix(t_obj obj)
{
    t_matrix    matrix;

    // matrix = scale_matrix(obj.scale);
    // matrix = mul_matrix(matrix, rotate_matrix(obj.rotate));
    matrix = mul_matrix(matrix, move_matrix(obj.origin));
    return (matrix);
}

void    convert(t_obj *obj)
{
    // obj->rotate.s[0] = obj->rotate.s[0] / 180 * PI;
    // obj->rotate.s[1] = obj->rotate.s[1] / 180 * PI;
    // obj->rotate.s[2] = obj->rotate.s[2] / 180 * PI;
    obj->origin.s[0] *= -1;
    obj->origin.s[1] *= -1;
    obj->origin.s[2] *= -1;
    // obj->scale.s[0] = 1 / obj->scale.s[0];
    // obj->scale.s[1] = 1 / obj->scale.s[1];
    // obj->scale.s[2] = 1 / obj->scale.s[2];
}
