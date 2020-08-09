/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_manager.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 13:22:53 by dmelessa          #+#    #+#             */
/*   Updated: 2020/08/03 16:31:14 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_MANAGER
# define OBJECT_MANAGER

# include "objects.h"

struct			s_object_manager
{
	t_obj		*objects;
	t_triangle	*triangles;

	int			nobjects;
	int			ntriangles;
	size_t		objects_malloc_size;
	size_t		triangles_malloc_size;
};

typedef struct s_object_manager t_object_manager;

int	init_object_manager(t_object_manager *object_manager);
int add_object(t_object_manager *object_manager,t_object_info object_info);

#endif
