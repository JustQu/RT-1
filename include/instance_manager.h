/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instance_manager.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 18:12:50 by dmelessa          #+#    #+#             */
/*   Updated: 2020/10/18 20:25:14 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INSTANCE_MANAGER
# define INSTANCE_MANAGER

# include "instance.h"
# include "objects.h"
# include "matrix.h"
# include "parser.h"
# include "texture_manager.h"

typedef struct			s_instance_manager
{
	t_texture_manager	texture_manager;
	t_instance			*instances;
	t_obj				*objects;
	t_triangle			*triangles;
	t_matrix			*matrices;
	t_object_info		*instances_info;
	size_t				instances_malloc_size;
	size_t				objects_malloc_size;
	size_t				triangles_malloc_size;
	size_t				matrices_malloc_size;
	size_t				instances_info_malloc_size;
	int					ninstances;
	int					nobjects;
	int					ntriangles;
	int					nmatrices;
}						t_instance_manager;

int			init_instance_manager(t_instance_manager * instance_manager);

int			add_parsed_object(t_instance_manager *instance_mngr,
								t_parsed_object parsed_object);

t_object_info	get_object_info(t_instance_manager *instance_manager,
								int id);

t_instance	get_instance(t_instance_manager *instance_mngr, int instance_id);

t_matrix	get_transformation_matrix(t_instance_manager mngr, int instance_id);

int			add_object(t_instance_manager *instance_manager, t_object_info object_info);
int			add_matrix(t_instance_manager *mngr, t_matrix matrix);

t_matrix	get_matrix(t_instance_manager *instance_manager, int instance_id);

t_obj		*get_objects(t_instance_manager *instance_manager);
int			get_num_of_objects(t_instance_manager *instance_manager);
t_matrix	*get_matrices(t_instance_manager *instance_manager);
int			get_num_of_matrices(t_instance_manager *instance_manager);
t_triangle	*get_triangles(t_instance_manager *instance_manager);
int			get_num_of_triangles(t_instance_manager *instance_manager);

t_aabb		compute_aabb(t_instance_manager instance_manager, int instance_id);

//
void	get_instance_id(t_instance_manager *instance_manager, int x, int y);
void	get_instance_type(t_instance_manager *instance_manager, int id);

#endif
