/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instance_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 19:52:25 by dmelessa          #+#    #+#             */
/*   Updated: 2020/11/14 01:58:14 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "instance_manager.h"
#include "libft.h"
#include "utils.h"
#include "math.h"

#include <assert.h>

int			init_instance_manager(t_instance_manager *mngr)
{
	int	a;

	a = 1;
	*mngr = (t_instance_manager){ .ninstances = 0, .nobjects = 0,
								.ntriangles = 0, .nmatrices = 0,
								.instances_malloc_size = a * sizeof(t_instance),
								.objects_malloc_size = a * sizeof(t_obj),
								.triangles_malloc_size = a * sizeof(t_triangle),
								.matrices_malloc_size = a * sizeof(t_matrix),
								.extra_size = a * sizeof(t_object_info)};
	init_texture_manager(&mngr->texture_manager);
	mngr->instances = (t_instance *)ft_memalloc(mngr->instances_malloc_size);
	mngr->objects = (t_obj *)ft_memalloc(mngr->objects_malloc_size);
	mngr->triangles = (t_triangle *)ft_memalloc(mngr->triangles_malloc_size);
	mngr->matrices = (t_matrix *)ft_memalloc(mngr->matrices_malloc_size);
	mngr->extra = (t_instance_extra *)ft_memalloc(mngr->extra_size);
	assert(mngr->instances);
	assert(mngr->objects);
	assert(mngr->triangles);
	assert(mngr->matrices);
	assert(mngr->extra);
	return (SUCCESS);
}
