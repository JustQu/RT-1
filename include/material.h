/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 00:07:37 by dmelessa          #+#    #+#             */
/*   Updated: 2020/09/28 13:49:20 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIAL_H
# define MATERIAL_H

# ifndef __OPENCL_C_VERSION__
#  include "rt_types.h"
#  include "color.h"
# endif

typedef enum e_material_type		t_material_type;
typedef struct s_material			t_material; //64 bytes

enum e_material_type
{
	matte, //kd, ka
	phong,
	emissive
};

struct					s_material //kd + ks < 1.0
{
	t_color				color;
	t_material_type		type;
	cl_float			kd; //diffuse reflection coefficient [0, 1]
	cl_float			ka; //ambient reflection
	cl_float			ks; //coefficient of specular reflection [0, 1]
	cl_float			exp;
	cl_float			d;
	cl_float			is_reflective;
	cl_float			reflectance_coef;
	cl_float			is_transparent;
	cl_float			transparence_coef;
	cl_float			gap[2];
};

#endif
