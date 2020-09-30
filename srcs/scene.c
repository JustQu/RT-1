/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 22:57:18 by dmelessa          #+#    #+#             */
/*   Updated: 2020/09/30 21:12:56 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "rt_options.h"
#include "math.h"
#include "sampler_manager.h"
#include "libft.h"

static const t_camera default_camera = {
	.viewplane = {
		.pixel_size = 1.0f,
		.width = DEFAULT_WIDTH,
		.height = DEFAULT_HEIGHT},
	.type = perspective,
	.origin = {.x = 0.0f, .y = 0.0f, .z = -3.0f, .w = 0.0f},
	.direction = {.x = -0.0f, .y = -0.0f, .z = 1.0f, .w = 0.0f},
	.up = {.x = 0.0f, .y = 1.0f, .z = 0.0f, .w = 0.0f},
	.d = DEFAULT_WIDTH / 4,
	.zoom = 1.0f,
	.normalized = FALSE};

static const t_camera default_thin_lens_camera = {
	.viewplane = {
		.pixel_size = 1.0f,
		.width = DEFAULT_WIDTH,
		.height = DEFAULT_HEIGHT,
	},
	.type = thin_lens,
	.origin = {.x = 0.0f, .y = 1.0f, .z = -2.0f, .w = 0.0f},
	.direction = {.x = 0.0f, .y = 0.0f, .z = 1.0f, .w = 0.0f},
	.up = {.x = 0.0f, .y = 1.0f, .z = 0.0f, .w = 0.0f},
	.d = DEFAULT_WIDTH / 4,
	.zoom = 1.0f,
	.normalized = FALSE,

	.l = 0.2f,
	.f = 7.0f};

static const t_camera default_fisheye_camera = {
	.viewplane = {
		.pixel_size = 1.0f,
		.width = DEFAULT_WIDTH,
		.height = DEFAULT_HEIGHT,
	},
	.type = fisheye,
	.origin = {.x = 0.0f, .y = 1.0f, .z = 0.0f, .w = 0.0f},
	.direction = {.x = 0.0f, .y = 0.0f, .z = 1.0f, .w = 0.0f},
	.up = {.x = 0.0f, .y = 1.0f, .z = 0.0f, .w = 0.0f},
	.d = DEFAULT_WIDTH / 2,
	.zoom = 1.0f,
	.normalized = TRUE,

	.f = 180.0 / 2.0f};

static const t_camera default_stereo_camera = {
	.viewplane = {
		.pixel_size = 1.0f,
		.width = DEFAULT_WIDTH,
		.height = DEFAULT_HEIGHT,
	},
	.type = stereo,
	.origin = {.x = 0.0f, .y = 0.0f, .z = 0.0f, .w = 0.0f},
	.direction = {.x = 0.0f, .y = 0.0f, .z = 1.0f, .w = 0.0f},
	.up = {.x = 0.0f, .y = 1.0f, .z = 0.0f, .w = 0.0f},
	.d = DEFAULT_WIDTH / 4,
	.zoom = 1.0f,
	.normalized = FALSE,

	.f = 1.0f,
	.l = 10.0f,
};

/**
** NOTE: images rendered with a spherical camera must have their aspect ration equal to lambda / phi,
** otherwise images will be distorted
*/
static const t_camera default_spherical_camera = {
	.viewplane = {
		.pixel_size = 1.0f,
		.width = DEFAULT_WIDTH,
		.height = DEFAULT_HEIGHT,
	},
	.type = spherical,
	.origin = {.x = 0.0f, .y = 1.0f, .z = 0.0f, .w = 0.0f},
	.direction = {.x = 0.0f, .y = 0.0f, .z = 1.0f, .w = 0.0f},
	.up = {.x = 0.0f, .y = 1.0f, .z = 0.0f, .w = 0.0f},
	.d = DEFAULT_WIDTH / 2,
	.zoom = 1.0f,
	.normalized = TRUE,
	.l = 360.0f / 2,
	.f = 180.0f / 2,
};

static const t_material default_matte_material = {
	.type = matte,
	.color = {.r = 0.0f, .g = 0xaf / (float)0xff, 1.0f},
	.kd = 0.5f,
	.ka = 0.1f,
	.ks = 0.0f,
	.exp = 0.0f};

static const t_material default_emissive_material = {
	.type = emissive,
	.color = {.r = 1.0f, .g = 1.0f, .b = 0.0f},
	.ka = 1.0f,
};

static const t_obj default_sphere = {
	// .type = sphere,
	.origin = {
		.x = 0.0f,
		.y = 0.0f,
		.z = 1.0f,
		.w = 0.0f},
	.r = 1.0f,
	.r2 = 1.0f,
	// .material = {.type = phong, .color = {.value = 0x000000ff}, .kd = 0.5f, .ka = 0.1f, .ks = 0.5, .exp = 10},
	.shadows = CL_TRUE};

static const t_obj default_plane = {
	// .type = plane,
	.origin = {
		.x = 0.0f,
		.y = -1.0f,
		.z = 0.0f,
		.w = 0.0f},
	// .material = {.type = phong, .color = {.value = 0x00aaaaaa}, .kd = 0.8f, .ka = 0.1f, .ks = 0.05f, .exp = 10.0f},
	.shadows = CL_TRUE};

static const t_obj default_cylinder = {
	// .type = cylinder,
	.origin = {
		.x = 2.0f,
		.y = 3.0f,
		.z = 5.0f,
		.w = 0.0f},
	.r = 1.0f,
	.r2 = 1.0f,
	.maxm = 5.0f, //max height of cylinder
	// .material = {.type = phong, .color = {.value = 0x001002af}, .kd = 0.6f, .ka = 0.1f, .ks = 0.2, .exp = 5},
	.shadows = CL_TRUE};

static const t_obj default_cone = {
	// .type = cone,
	.origin = {
		.x = 0.0f,
		.y = 2.0f,
		.z = 5.0f,
		.w = 0.0f,
	},
	.r = 0.57735026919,
	.r2 = 1.33333333333, //tan(angle / 2) + 1
	.maxm = 3.0f,
	.minm = -3.0f,
	// .material = {.type = phong, .color = {.value = 0x00ffaf}, .kd = 0.6f, .ka = 0.1f, .ks = 0.2f, .exp = 50.0f},
	.shadows = CL_TRUE};

static const t_obj default_paraboloid = {
	// .type = paraboloid,
	.origin = {
		.x = 2.0f,
		.y = 1.0f,
		.z = 5.0f,
		.w = 0.0f},
	.r = 0.3f,
	.minm = 0.0f,
	.maxm = 2.0f,
	// .material = {.type = phong, .color = {.value = 0x05f000f}, .kd = 0.6f, .ka = 0.1f, .ks = 0.2f, .exp = 50.0f},
	.shadows = CL_TRUE};

static const t_obj default_torus = {
	// .type = torus,
	.origin = {
		.x = 0.0f,
		.y = 1.0f,
		.z = 1.0f,
		.w = 0.0f},
	.r = 2.0f,
	.r2 = 0.4f,
	// .material = {.type = phong, .color = {.value = 0x00bf8f0f}, .kd = 0.6f, .ka = 0.1f, .ks = 0.2f, .exp = 50.0f},
	.shadows = CL_TRUE};

static const t_triangle default_triangle = {
	.vertex1 = {
		.x = -3.0f,
		.y = 1.0f,
		.z = -5.0f,
		.w = 0.0f},
	.vertex2 = {.x = -1.0f, .y = 1.0f, .z = 5.0f, .w = 0.0f},
	.vertex3 = {.x = -2.0f, .y = 3.0f, .z = 5.0f, .w = 0.0f},
	.vector1 = {
		.x = 2.0f,
		.y = 0.0f,
		.z = 0.0f,
		.w = 0.0f,
	},
	.vector2 = {.x = 1.0f, .y = 2.0f, .z = 0.0f, .w = 0.0f},
	.normal = {.x = 0.0f, .y = 0.0f, .z = -1.0f, .w = 0.0f},
	// .material = {.color = 0x00af00af, .type = phong, .kd = 0.2, .ka = 0.25, .ks = 0.8, .exp = 10}
};
static const t_obj default_box = {
	.shadows = CL_TRUE};

static const t_obj default_disk = {
	.origin = {
		.x = -1.0f,
		.y = 2.0f,
		.z = 3.0f,
		.w = 0.0f},
	.r = 1.0f,
	.r2 = 1.0f,
	.shadows = CL_TRUE};

static const t_obj default_rectangle = {
	.origin = {
		.x = -1.2f,
		.y = 0.0f,
		.z = 2.0f,
		.w = 0.0f},
	.normal = {.x = 0.0f, .y = 0.0f, .z = 1.0f, .w = 0.0f},
	.r = 1.0f,
	.r2 = 1.0f,
	.shadows = CL_TRUE};

static const t_light default_ambient_light = {
	.type = ambient,
	.origin = {
		.x = 0.0f,
		.y = 0.0f,
		.z = 0.0f,
		.w = 0.0f}};

static const t_light default_directional_light = {
	.type = directional,
	.origin = {
		.x = 0.0f,
		.y = 0.0f,
		.z = 0.0f,
		.w = 0.0f,
	},
	.direction = {.x = 0.0f, .y = -1.0f, .z = -1.0f, .w = 0.0f},
	.ls = 3.0f,
	.color = 0x00ffffff};

static const t_light default_point_light = {
	.type = point,
	.origin = {
		.x = 1.0f,
		.y = 0.0f,
		.z = -5.0f,
		.w = 0.0f},
	.ls = 2.0f,
	.color = {.r = 1.0f, .g = 1.0f, .b = 1.0f}
};

int		init_default_scene(t_scene *scene, t_sampler_manager *sampler_manager)
{
	t_instance_manager *instance_manager;
	t_object_info object_info;
	scene->camera = default_camera;

	instance_manager = &scene->instance_mngr;
	init_instance_manager(instance_manager);

	// scene->camera = default_thin_lens_camera;
	// scene->camera = default_fisheye_camera;
	// scene->camera = default_spherical_camera;
	// scene->camera = default_stereo_camera;
	scene->camera.sampler_id = new_sampler(sampler_manager, rand_jitter, NUM_SAMPLES, DISK_SAMPLES);

	compute_uvw(&scene->camera);

	scene->nlights = 1;
	scene->lights = (t_light *)malloc(sizeof(t_light) * (scene->nlights + 10));

	//default_scene
	//Объекты
	static t_material zero_material;
	t_parsed_object object;

	object.type = plane;
	object.origin = (cl_float4){.x = 0.0f, .y = -1.0f, .z = 5.0f, .w = 0.0f};
	object.direction = (cl_float4){.x = 0.0f, .y = 1.0f, .z = 0.0f, .w = 0.0f};
	object.scaling = (cl_float3){.x = 1.0f, .y = 1.0f, .z = 1.0f};
	object.rotation = (cl_float3){.x = 0.0f, .y = 0.0f, .z = 0.0f};
	object.material = (t_material){.type = matte,
								   .color = {.r = 1.0f, .g = 1.0f, .b = (float)0xf0 / 0xff},
								   .kd = 0.9f,
								   .ka = 0.1f,
								   .ks = 0.0f,
								   .exp = 1.0f};
	// add_parsed_object(instance_manager, object);
	// add_instance(instance_manager, object_info);

	object.type = sphere;
	object.origin = (cl_float4){.x = 0.0f, .y = 0.0f, .z = 20.0f, .w = 0.0f};
	object.r = 1.0f;
	object.r2 = 1.0f;
	object.scaling = (cl_float3){.x = 1.0f, .y = 2.0f, .z = 1.0f};
	object.material = zero_material;
	object.material = (t_material){.type = matte,
								   .color = {.r = 1.0f, .g = 0.0f, .b = 0.0f},
								   .kd = 0.8f,
								   .ka = 0.1f,
								   .ks = 0.1f,
								   .exp = 100.0f};
	add_parsed_object(instance_manager, object);

	// add_instance(instance_manager, object_info);

	object.type = cylinder;
	object.origin = (cl_float4){.x = -3.0f, .y = 0.0f, .z = 2.0f, .w = 0.0f};
	object.scaling = (cl_float3){.x = 1.0f, .y = 4.0f, .z = 1.0f};
	object.r = 1.0f;
	object.material = (t_material){.type = phong,
								   .color = {.r = 1.0f, .g = 0.0f, .b = 0.0f},
								   .kd = 0.8f,
								   .ka = 0.1f,
								   .ks = 0.1f,
								   .exp = 100.0f};
	add_parsed_object(instance_manager, object);

	// add_instance(instance_manager, object_info);

	object.type = torus;
	object.r = 1.0f;
	object.r2 = 0.4f;
	object.rotation = (cl_float3){.x = 0.0f, .y = 0.0f, .z = 0.0f};
	object.direction = (cl_float4){.x = 0.0f, .y = 1.0f, .z = 0.0f, .w = 0.0f};
	object.origin = (cl_float4){.x = 0.0f, .y = 0.0f, .z = 3.0f, .w = 0.0f};
	object.scaling = (cl_float3){.x = 1.0f, .y = 1.0f, .z = 1.0f};
	object.material.type = phong;
	object.material.ks = 0.1f;
	object.material.exp = 10.0f;
	object.material.color =
		(t_color){.r = 0.0f, .g = (float)0xfa / 0xff, .b = (float)0xaf / 0xff};
	add_parsed_object(instance_manager, object);

	object.type = sphere;
	object.r = 1.0f;
	object.origin = (cl_float4){.x = 2.0f, .y = 4.0f, .z = 5.0f};
	add_parsed_object(instance_manager, object);

	object.type = sphere;
	object.r = 1.0f;
	object.scaling = (cl_float3){.x = 2.0f, .y = 0.5f, .z = 1.0f};
	object.origin = (cl_float4){.x = 0.0f, .y = 2.0f, .z = 0.0f};
	add_parsed_object(instance_manager, object);

	object.scaling = (cl_float3){.x = 1.0f, .y = 1.0f, .z = 1.0f};

	object.type = sphere;
	object.r = 1.0f;
	object.origin = (cl_float4){.x = -3.0f, .y = 2.0f, .z = 1.0f};
	add_parsed_object(instance_manager, object);

	object.type = sphere;
	object.r = 2.0f;
	object.origin = (cl_float4){.x = -2.0f, .y = 3.0f, .z = 6.0f};
	add_parsed_object(instance_manager, object);

	object.type = sphere;
	object.r = 1.0f;
	object.origin = (cl_float4){.x = -4.0f, .y = 2.0f, .z = 3.0f};
	add_parsed_object(instance_manager, object);

	object.type = sphere;
	object.r = 1.0f;
	object.origin = (cl_float4){.x = -6.0f, .y = 4.0f, .z = 3.0f};
	add_parsed_object(instance_manager, object);

	object.type = sphere;
	object.r = 3.0f;
	object.origin = (cl_float4){.x = -2.5f, .y = -2.0f, .z = 6.0f};
	add_parsed_object(instance_manager, object);

	object.type = sphere;
	object.r = 2.0f;
	object.origin = (cl_float4){.x = -1.0f, .y = 7.0f, .z = 3.0f};
	add_parsed_object(instance_manager, object);

	object.type = sphere;
	object.r = 1.0f;
	object.origin = (cl_float4){.x = -8.0f, .y = -3.0f, .z = 2.0f};
	add_parsed_object(instance_manager, object);

	//Освещение

	scene->ambient_occluder.color = (t_color){.r = 1.0f, .g = 1.0f, .b = 1.0f};
	scene->ambient_occluder.ls = 0.01f;
	scene->ambient_occluder.min_amount = (t_color){.r = 0.0f, .g = 0.0f, .b = 0.0f};
	scene->ambient_occluder.sampler_id = new_sampler(sampler_manager, pure_random, NUM_SAMPLES, HEMISPHERE_SAMPLES);

	scene->ambient_light = (t_light){
		.type = ambient,
		.ls = 0.2f,
		.color = {.r = 1.0f, .b = 1.0f, .g = 1.0f}};
	scene->lights[0] = default_point_light;

	scene->lights[1] = default_directional_light;
	scene->lights[1].ls = 0.2f;
	scene->lights[1].origin.x = INFINITY;
	scene->lights[1].origin.y = INFINITY;
	scene->lights[1].origin.z = INFINITY;

	scene->lights[2] = default_point_light;
	scene->lights[2].origin.x = 0.0f;
	scene->lights[2].origin.y = 5.0f;
	scene->lights[2].origin.y = 5.0f;

	scene->lights[2].ls = 1.0f;
}
