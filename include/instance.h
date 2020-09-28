/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instance.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 20:05:10 by dmelessa          #+#    #+#             */
/*   Updated: 2020/09/28 13:50:45 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INSTANCE_H
# define INSTANCE_H

# ifndef __OPENCL_C_VERSION__
#  include "material.h"
#  include "objects.h"
# endif

typedef struct s_instance	t_instance;

struct	s_instance
{
	t_material			material;	// todo: сделать менеджер материалов. Зачем? чтобы не загружать полностью материал каждый раз
	cl_int				object_id; //triangle_id if type == triangle
	cl_int				matrix_id;
	t_type				type;
	cl_int				gap[5];
};

#endif
