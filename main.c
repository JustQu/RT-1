#include <CL/cl.h>
#include <math.h>
#include <stdio.h>
#define PI 3.1415926535

typedef cl_float16 t_matrix;

typedef struct s_obj
{
    cl_float4   center;
    cl_float4   rotate;
    cl_float4   scale;
}               t_obj;

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

t_matrix    move_matrix(cl_float4 move)
{
    t_matrix matrix;

    matrix = default_matrix();
    matrix.s[3] = move.s[0];
    matrix.s[7] = move.s[1];
    matrix.s[11] = move.s[2];
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

    matrix = scale_matrix(obj.scale);
    matrix = mul_matrix(matrix, rotate_matrix(obj.rotate));
    matrix = mul_matrix(matrix, move_matrix(obj.center));
    return (matrix);
}

void    convert(t_obj *obj)
{
    obj->rotate.s[0] = obj->rotate.s[0] / 180 * PI;
    obj->rotate.s[1] = obj->rotate.s[1] / 180 * PI;
    obj->rotate.s[2] = obj->rotate.s[2] / 180 * PI;
}

int     main(void)
{
    t_matrix matrix;
    t_obj   obj;
    int     i;

    obj.center.s[0] = 1;
    obj.center.s[1] = 0;
    obj.center.s[2] = 0;
    obj.rotate.s[0] = 0;
    obj.rotate.s[1] = 360;
    obj.rotate.s[2] = 0;
    obj.scale.s[0] = 1;
    obj.scale.s[1] = 1;
    obj.scale.s[2] = 1;

    convert(&obj);

    matrix = create_affin_matrix(obj);
    i = 0;
    while (i < 16)
    {
        printf("%f ", matrix.s[i]);
        if (i == 3 || i == 7 || i == 11 || i == 15)
            printf("\n");
        i++;
    }
    return (0);
}