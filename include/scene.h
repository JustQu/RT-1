/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 00:33:50 by dmelessa          #+#    #+#             */
/*   Updated: 2020/11/11 01:42:54 by dmelessa         ###   ########.fr       */
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
						t_res_mngr *resource_manager);
t_bvh	build_bvh(t_scene *scene);

#endif
