/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instance.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 20:05:10 by dmelessa          #+#    #+#             */
/*   Updated: 2020/08/12 20:44:10 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INSTANCE_H
# define INSTANCE_H

#include "material.h"
#include "objects.h"

typedef struct s_instance	t_instance;

#ifdef _WIN64
//__declspec(align(4))
// #pragma pack(1)
#endif
struct
# ifdef __OPENCL_C_VERSION__
// __attribute__((packed))
# endif
s_instance
{
	t_material			material;	// todo: сделать менеджер материалов. Зачем? чтобы не загружать полностью материал каждый раз
	t_type				type;
	cl_int				object_id; //triangle_id if type == triangle
	cl_int				matrix_id;
	cl_int				gap[5];
};

#endif
