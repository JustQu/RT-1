/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 00:27:56 by dmelessa          #+#    #+#             */
/*   Updated: 2020/09/23 23:56:43 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BVH_H
#define BVH_H

#include "types.h"
#include "objects.h"

typedef struct s_bvh_node t_bvh_node;

/*
** array of nodes will represent the struct itself
*/
typedef struct s_bvh_node *t_bvh;

struct s_bvh_node //48
{
	t_bbox		aabb;
	cl_float3	center; //todo(dmelessa): delete this field
	int			instance_id;
	int			next;
	int			gap[2];
};

# ifndef __OPENCL_C_VERSION__

#  include "instance_manager.h"

t_bbox	compute_aabb(t_instance_manager instance_mngr, int id);

# endif

#endif
