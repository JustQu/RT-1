/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instance_manager.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 18:12:50 by dmelessa          #+#    #+#             */
/*   Updated: 2020/08/13 18:48:55 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INSTANCE_MANAGER
# define INSTANCE_MANAGER

# include "instance.h"
# include "objects.h"
# include "matrix.h"

typedef struct			s_instance_manager
{
# if !OPEN_CL

# endif
	t_instance			*instances;
	t_obj				*objects;
	t_triangle			*triangles;
	t_matrix			*matrices;
	size_t				instances_malloc_size;
	size_t				objects_malloc_size;
	size_t				triangles_malloc_size;
	size_t				matrices_malloc_size;
	int					ninstances;
	int					nobjects;
	int					ntriangles;
	int					nmatrices;
	// t_object_manager	object_manager;//не нужно. Избавиться от этого слоя
	// t_matrix_manager	matrix_manager;//абстракции
}						t_instance_manager;

int			init_instance_manager(t_instance_manager * instance_manager);
int			add_instance(t_instance_manager *instance_manager,
						t_object_info object_info);
int			add_object(t_instance_manager *instance_manager,
						t_object_info object_info);
int			add_matrix(t_instance_manager *mngr, t_matrix matrix);

t_matrix	get_matrix(t_instance_manager *instance_manager, int instance_id);

t_obj		*get_object(t_instance_manager *instance_manager);
int			get_num_of_objects(t_instance_manager *instance_manager);
t_matrix	*get_matrices(t_instance_manager *instance_manager);
int			get_num_of_matrices(t_instance_manager *instance_manager);
t_triangle	*get_triangles(t_instance_manager *instance_manager);
int			get_num_of_triangles(t_instance_manager *instance_manager);

void		*ft_realloc(void *mem, size_t current_size, size_t new_size);

#endif
