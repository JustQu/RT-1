/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instance.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 20:05:10 by dmelessa          #+#    #+#             */
/*   Updated: 2020/11/11 22:19:06 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INSTANCE_H
# define INSTANCE_H

# ifndef __OPENCL_C_VERSION__
#  include "material.h"
#  include "objects.h"
# endif

typedef struct s_instance	t_instance; //96bytes

struct	s_instance
{
	t_material			material; //64 bytes

	cl_int				object_id; //triangle_id if type == triangle
									// может быть надо назвать geometry?
	cl_int				matrix_id; //менеджер матрицы не нужен, избавиться
	t_type				type;
	cl_float			area;	//area for emissive objects
	cl_int				gap[3];
	cl_uchar			uchar_gap[3];
	cl_uchar			shadows;
};

#endif
