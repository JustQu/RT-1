/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 00:33:50 by dmelessa          #+#    #+#             */
/*   Updated: 2020/11/21 21:31:27 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "light_manager.h"
# include "camera.h"
# include "bvh.h"
# include "instance_manager.h"
# include "sampler_manager.h"

typedef struct s_resource_manager	t_res_mngr;

/**
** @brief
** struct containing information about scene: camera, objects, triangles and light sources
*/
typedef struct s_scene	t_scene;

struct					s_scene
{
	t_camera			camera;
	t_instance_manager	instance_mngr;
	t_ambient_occluder	ambient_occluder;
	t_light_manager		light_manager;
	t_light				ambient_light;
	t_bvh				bvh;
	uint32_t			gap[2];
};

int		init_default_scene(t_scene *scene, t_sampler_manager *sampler_manager,
						t_res_mngr *resource_manager, char *scene_file);
t_bvh	build_bvh(t_scene *scene);
int			parser(t_res_mngr *resource_manager, t_parsed_info *asset, char *file_name, t_camera *camera);
void		pars_camera(char *str, t_camera *camera);

#endif
