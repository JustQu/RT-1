/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsed_scene.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 20:37:35 by aapricot          #+#    #+#             */
/*   Updated: 2020/12/03 19:21:54 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "resource_manager.h"
#include "parser.h"
#include "rt_options.h"
#include "math.h"
#include "sampler_manager.h"
#include "libft.h"
#include "texture_manager.h"
#include "light_manager.h"
#include "logs.h"

void					set_default_camera(t_camera *camera)
{
	if (camera == NULL)
		rt_error("set_default_camera(): given NULL pointer");
	camera->viewplane.pixel_size = 1.0f;
	camera->viewplane.width = IMG_WIDTH;
	camera->viewplane.height = IMG_HEIGHT;
	camera->type = perspective;
	camera->origin = (cl_float4){.x = 0.0f, .y = 1.0f, .z = -8.0f, .w = 0.0f};
	camera->direction = (cl_float4){.x = 0.0f, .y = -0.1f, .z = 1.0f, .w = 0.0f};
	camera->up = (cl_float4){.x = 0.0f, .y = 1.0f, .z = 0.0f, .w = 0.0f};
	camera->d = DEFAULT_WIDTH;
	camera->zoom = 0.5f;
	camera->normalized = FALSE;
	//заново открыть лог файл и записать логи
}

int						init_parsed_scene(t_scene *scene,
	t_sampler_manager *sampler_manager,
	t_res_mngr *resource_manager, char *scene_file)
{
	t_instance_manager	*instance_manager;
	t_parsed_info		asset;

	if (scene == NULL || sampler_manager == NULL ||
			resource_manager == NULL || scene_file == NULL)
		rt_error("init_parsed_scene(): given NULL pointer");
	scene->camera.type = -3;
	instance_manager = &scene->instance_mngr;
	init_instance_manager(instance_manager);
	init_light_manager(&scene->light_manager);
	scene->camera.sampler_id = new_sampler(sampler_manager,
	rand_jitter, 25, DISK_SAMPLES);
	scene->ambient_occluder.color = (t_color){.r = 1.0f, .g = 1.0f, .b = 1.0f};
	scene->ambient_occluder.ls = 0.05f;
	scene->ambient_occluder.min_amount =
	(t_color){ .r = 0.1f, .g = 0.1f, .b = 0.1f };
	scene->ambient_occluder.sampler_id =
	new_sampler(sampler_manager, rand_jitter, 100, HEMISPHERE_SAMPLES);
	scene->ambient_light = (t_light){
		.type = ambient,
		.ls = 0.2f,
		.color = {.r = 1.0f, .b = 1.0f, .g = 1.0f}};
	if (parser(resource_manager, &asset, scene_file) < 0)
		return (-1);
	if (scene->camera.type == -3)
		set_default_camera(&scene->camera);
	compute_uvw(&scene->camera);
	return (0);
}
