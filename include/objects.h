/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 00:07:20 by dmelessa          #+#    #+#             */
/*   Updated: 2020/07/25 22:38:53 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "types.h"
# include "material.h"
# include "matrix.h"

typedef enum e_types				t_type;
typedef struct s_obj				t_obj;
typedef struct s_triangle			t_triangle;
typedef struct s_bbox				t_bbox;
enum	e_types
{
	cone,
	cylinder,
	paraboloid,
	plane,
	sphere,
	torus,
	triangle,
	box,
	disk,
	rectangle,
	generic_shere
	//todo(dmelessa): another generic types
};

/**
** @brief
** axis-aligned bounding box for object
*/
#ifdef _WIN64
__declspec(align(4))
#endif
struct					s_bbox
{
	cl_float4			min;
	cl_float4			max;
};

# ifdef _WIN64
__declspec(align(4))
# endif
struct					s_obj
{
	t_type				type;
	t_material			material;
	t_bbox				bounding_box;
	cl_float4			origin;
	cl_float4			direction;
	cl_float4			dir2;
	cl_float4			normal;
	cl_float			r;
	cl_float			r2;
	cl_float			angle;
	cl_float			maxm;
	cl_float			minm;
	cl_int				shadows;
	cl_int				sampler_id;
};

// int a = sizeof(struct s_obj);

# ifdef _WIN64
__declspec(align(4))
# endif
struct	s_triangle
{
	t_material	material;
	cl_float4	vertex1;
	cl_float4	vertex2;
	cl_float4	vertex3;
	cl_float4	vector1; //vertex2 - vertex1
	cl_float4	vector2; // vertex3 - vertex1
	cl_float4	normal;
};

#ifdef _WIN64
__declspec(align(4))
#endif
struct	s_instance
{
	t_type	type;
	int		object_id; //Если дженерик тип, то -1
	int		matrix_id;
};
typedef struct s_instance	t_instance;

#ifdef _WIN64
__declspec(align(4))
#endif
struct	s_instance_manager
{
	t_instance			*instances;
	unsigned int		ninstances;
	size_t				malloc_size;

	t_matrix_manager	matrix_manager;
};
typedef struct s_instance_manager	t_instance_manager;

void	rotatate_object(t_obj *obj, int axis, float angle);
void	translate_object(t_obj *obj, float x, float y, float z);
void	scale_object(t_obj *obj, float a, float b, float c);
void	shear_object(t_obj *obj);
void	reflect_object(t_obj *obj);

#endif
