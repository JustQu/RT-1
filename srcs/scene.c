/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 22:57:18 by dmelessa          #+#    #+#             */
/*   Updated: 2020/11/09 18:57:49 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "rt_options.h"
#include "math.h"
#include "sampler_manager.h"
#include "libft.h"
#include "texture_manager.h"
#include "light_manager.h"

static const t_camera default_camera = {
	.viewplane = {
		.pixel_size = 1.0f,
		.width = IMG_WIDTH,
		.height = IMG_HEIGHT},
	.type = perspective,
	.origin = {.x = 0.0f, .y = 1.0f, .z = -8.0f, .w = 0.0f},
	.direction = {.x = 0.0f, .y = -0.1f, .z = 1.0f, .w = 0.0f},
	.up = {.x = 0.0f, .y = 1.0f, .z = 0.0f, .w = 0.0f},
	.d = DEFAULT_WIDTH,
	.zoom = 0.5f,
	.normalized = FALSE};

static const t_camera default_thin_lens_camera = {
	.viewplane = {
		.pixel_size = 1.0f,
		.width = IMG_WIDTH,
		.height = IMG_HEIGHT,
	},
	.type = thin_lens,
	.origin = {.x = 0.0f, .y = 0.0f, .z = -8.0f, .w = 0.0f},
	.direction = {.x = 0.0f, .y = 0.0f, .z = 1.0f, .w = 0.0f},
	.up = {.x = 0.0f, .y = 1.0f, .z = 0.0f, .w = 0.0f},
	.d = DEFAULT_WIDTH,
	.zoom = 0.5f,
	.normalized = FALSE,

	.l = 0.2f,
	.f = 8.0f};

static const t_camera default_fisheye_camera = {
	.viewplane = {
		.pixel_size = 1.0f,
		.width = IMG_WIDTH,
		.height = IMG_HEIGHT,
	},
	.type = fisheye,
	.origin = {.x = 0.0f, .y = 0.0f, .z = -8.0f, .w = 0.0f},
	.direction = {.x = 0.0f, .y = 0.0f, .z = 1.0f, .w = 0.0f},
	.up = {.x = 0.0f, .y = 1.0f, .z = 0.0f, .w = 0.0f},
	.d = DEFAULT_WIDTH,
	.zoom = 0.5f,
	.normalized = FALSE,

	.f = 120.0f / 2.0f};

static const t_camera default_stereo_camera = {
	.viewplane = {
		.pixel_size = 1.0f,
		.width = DEFAULT_WIDTH,
		.height = DEFAULT_HEIGHT,
	},
	.type = stereo,
	.origin = {.x = 0.0f, .y = 0.0f, .z = -3.0f, .w = 0.0f},
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
	// .color = {.r = 0.0f, .g = 0xaf / (float)0xff, 1.0f},
	.kd = 0.5f,
	.ka = 0.1f,
	.ks = 0.0f,
	.exp = 0.0f};

static const t_material default_emissive_material = {
	.type = emissive,
	// .color = {.r = 1.0f, .g = 1.0f, .b = 0.0f},
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
		.x = 1000000,
		.y = 1000000,
		.z = 1000000,
		.w = 0.0f,
	},
	.direction = {.x = -1.0f, .y = -1.0f, .z = 1.0f, .w = 0.0f},
	.ls = 0.8f,
	.color = {.r = 1.0f, .g = 1.0f, .b = 1.0f}
	// .color = 0x00ffffff
};

static const t_light default_point_light = {
	.type = point,
	.origin = {
		.x = 1.0f,
		.y = 8.0f,
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
	init_light_manager(&scene->light_manager);

	// scene->camera = default_thin_lens_camera;
	// scene->camera = default_fisheye_camera;
	// scene->camera = default_spherical_camera;
	// scene->camera = default_stereo_camera;
	scene->camera.sampler_id = new_sampler(sampler_manager, rand_jitter, 25, DISK_SAMPLES);

	compute_uvw(&scene->camera);

	//default_scene
	//Объекты
	static t_material	zero_material;

	static t_parsed_object		object;
	t_material					material;
	t_texture					texture;

	/* #0 SPHERE 1 */
	object.type = sphere;
	object.r = 1.0f;
	object.origin = (cl_float4){ .x = 1.0f, .y = 0.0f, .z = 0.0f, .w = 0.0f };
	object.scaling = (cl_float4){ .x = 1.0f, .y = 1.0f, .z = 1.0f, .w = 0.0f };
	texture.type = solid;
	texture.data.solid.color.r = 1.0f;
	texture.data.solid.color.b = 0.0f;
	texture.data.solid.color.g = 0.0f;
	object.material.type = matte;
	object.material.kd = 0.9f;
	object.material.ka = 0.25f;
	object.material.texture_id = add_texture(&instance_manager->texture_manager, texture);
	// add_parsed_object(instance_manager, object);

	/* #1 BOTTOM BOX */
	object.type = plane;
	object.origin = (cl_float4){ .x = -10.0f, .y = -1.0f, .z = -10.0f };
	object.scaling = (cl_float4){ 1.0f, 1.0f, 1.0f };
	object.vector1 = (cl_float4){ .x = 0.0f, .y = 0.0f,.z = 0.0f };
	object.vector2 = (cl_float4){ .x = 20.0f, .y = .01f, .z = 20.0f };
	// texture.type = smooth_perlin;
	// texture.data.smooth_perlin.scale = 5.0f;
	texture.type = checker;
	texture.data.checker.odd = (t_color){ .r = 0.0f, .g = 0.0f, .b = 1.0f };
	texture.data.checker.even = (t_color){ .r = 0.5f, .g = 0.5f, .b = 0.5f };
	// texture.type = wave_perlin;
	// texture.data.smooth_perlin.scale = 10.0f;
	object.material.type = metal;
	object.material.kt = 0.95f;
	object.material.kd = 1.0f;
	object.material.ka = 0.25f;
	object.material.texture_id = add_texture(&instance_manager->texture_manager, texture);
	// add_parsed_object(instance_manager, object);

	object.type = box;
	object.origin = (cl_float4){.x = -10.0f, .y = 5.0f, .z = -10.0f};
	object.scaling = (cl_float4){1.0f, 1.0f, 1.0f};
	object.vector1 = (cl_float4){.x = 0.0f, .y = 0.0f, .z = 0.0f};
	object.vector2 = (cl_float4){.x = 20.0f, .y = .01f, .z = 20.0f};
	// texture.type = smooth_perlin;
	// texture.data.smooth_perlin.scale = 5.0f;
	texture.type = checker;
	texture.data.checker.odd = (t_color){.r = 0.0f, .g = 0.0f, .b = 1.0f};
	texture.data.checker.even = (t_color){.r = 0.5f, .g = 0.5f, .b = 0.0f};
	// texture.type = wave_perlin;
	// texture.data.smooth_perlin.scale = 10.0f;
	object.material.type = matte;
	object.material.kd = 1.0f;
	object.material.ka = 0.25f;
	object.material.texture_id = add_texture(&instance_manager->texture_manager, texture);
	// add_parsed_object(instance_manager, object);

	/* #2 ELIPSE 1 */
	object.type = sphere;
	object.r = 1.0f;
	object.origin = (cl_float4){ 0.0f, 0.0f, 0.0f, 0.0f };
	object.scaling = (cl_float3){ 1.0f, 4.0f, 1.0f };
	object.rotation = (cl_float3){ 0.0f, 0.0f, 45.0f };
	texture.type = checker;
	texture.data.checker.odd = (t_color){ .r = 0.8f, .g = 0.3f, .b = 0.3f };
	texture.data.checker.even = (t_color){ .r = 0.5f, .g = 0.5f, .b = 0.0f };
	// texture.data.solid.color = (t_color){ 0.8f, 0.3f, 0.3f };
	object.material.type = matte;
	object.material.kd = 1.0f;
	object.material.ka = 0.25f;
	object.material.texture_id = add_texture(&instance_manager->texture_manager, texture);
	// add_parsed_object(instance_manager, object);

	/* #3 TORUS 	1 */
	object.type = torus;
	object.r = 1.0f;
	object.r2 = 0.2f;
	object.origin = (cl_float4){ .x = 1.5f, .y = 1.0f, .z = -2.0f };
	object.scaling = (cl_float3){ .x = 2.0f, .y = 3.0f, .z = 1.0f };
	object.rotation = (cl_float3){ .x = -45.0f, .y = 0.0f, .z = 0.0f };
	texture.type = solid;
	texture.data.solid.color = (t_color){.r = 1.0f, .g = 0.9f, .b = 0.686f};
	object.material.type = dielectric;
	object.material.kt = 2.4f;
	object.material.kd = 1.0f;
	object.material.texture_id = add_texture(&instance_manager->texture_manager, texture);
	// add_parsed_object(instance_manager, object);

	object.type = cylinder;
	object.r = 1.0f;
	object.origin = (cl_float4){ .x = -4.5f, .y = -1.0f, .z = 0.0f, .w = 0.0f };
	object.rotation = (cl_float3){ .x = -30.0f, .y = 0.0f, .z = 45.0f };
	object.scaling = (cl_float3){ .x = 1.0f, .y = 4.0f, .z = 1.0f };
	texture.type = solid;
	texture.data.solid.color = (t_color){ .r = 0.8f, .g = 0.6f, .b = 0.2f };
	object.material.type = matte;
	object.material.kr = 0.95f;
	object.material.kd = 0.8f;
	object.material.ks = 0.1f;
	object.material.exp = 100000.0f;
	object.minm = 0.0f;
	object.maxm = 1.0f;
	object.material.texture_id = add_texture(&instance_manager->texture_manager, texture);
	// add_parsed_object(instance_manager, object);

	object.type = cone;
	object.origin = (cl_float4){ .x = -3.0f, .y = 2.0f, .z = -4.0f, .w = 0.0f };
	object.rotation = (cl_float4){ 180.0f, 0.0f, 0.0f, 0.0f };
	object.scaling = (cl_float4){ .x = 1.0f, .y = 1.0f, .z = 1.0f, .w = 0.0f };
	texture.type = turbulence_perlin;
	texture.data.smooth_perlin.scale = 0.5f;
	object.material.type = metal;
	object.material.kr = 1.0f;
	object.material.kt = 1.333f;
	object.material.kd = 2.0f;
	object.material.texture_id = add_texture(&instance_manager->texture_manager, texture);
	object.r2 = 60.0f;
	object.minm = 0.0f;
	object.maxm = 1.5f;
	// add_parsed_object(instance_manager, object);

	object.type = sphere;
	object.r = 2.0f;
	object.origin = (cl_float4){ .x = 3.0f , .y = 1.0f, .z = 1.0f };
	object.rotation = (cl_float3){ .x = 0.0f, .y = 0.0f, .z = 0.0f };
	object.scaling = (cl_float3){ 2.0f, 2.0f, 2.0f };
	texture.type = solid;
	texture.data.solid.color = (t_color){ .r = 0.3f, .g = 0.2f, .b = 0.7f };
	object.material.type = matte;
	object.material.kd = 1.0f;
	object.material.texture_id = add_texture(&instance_manager->texture_manager, texture);
	// add_parsed_object(instance_manager, object);

	object.type = sphere;
	object.r = 1.0f;
	object.origin = (cl_float4){ .x = -3.0f, .y = 0.0f, .z = -4.0f };
	object.rotation = (cl_float3){ .x = 0.0f, .y = 0.0f, .z = 0.0f };
	object.scaling = (cl_float3){ .x = 1.0f, .y = 1.0f, .z = 1.0f };
	texture.type = turbulence_perlin;
	texture.data.smooth_perlin.scale = 0.5f;
	object.material.type = matte;
	object.material.type = dielectric;
	object.material.type = metal;
	object.material.is_reflective = FALSE;
	object.material.kr = 1.0f;
	object.material.kt = 1.333f;
	object.material.kd = 2.0f;
	object.material.texture_id = add_texture(&instance_manager->texture_manager, texture);
	// add_parsed_object(instance_manager, object);

	object.type = sphere;
	object.r = 1.0f;
	object.origin = (cl_float4){ .x = 3.0f, .y = -0.25f, .z = -2.5f };
	object.rotation = (cl_float3){ .x = 0.0f, .y = 0.0f, .z = 0.0f };
	object.scaling = (cl_float3){ .x = 0.75f, .y = 0.75f, .z = 0.75f };
	texture.type = smooth_perlin;
	texture.data.smooth_perlin.scale = 20.0f;
	object.material.type = matte;
	object.material.kd = 1.0f;
	object.material.texture_id = add_texture(&instance_manager->texture_manager, texture);
	// add_parsed_object(instance_manager, object);


	object.type = sphere;
	object.r = 0.25f;
	object.origin = (cl_float4){.x = 3.0f, .y = -0.5f, .z = -3.5f};
	object.rotation = (cl_float3){.x = 0.0f, .y = 0.0f, .z = 0.0f};
	object.scaling = (cl_float3){.x = 0.5f, .y = 0.5f, .z = 0.5f};
	texture.type = turbulence_perlin;
	texture.data.smooth_perlin.scale = 3.0f;
	object.material.type = matte;
	object.material.kd = 1.0f;
	object.material.texture_id = add_texture(&instance_manager->texture_manager, texture);
	// add_parsed_object(instance_manager, object);

	object.type = disk;
	object.r = 1.0f;
	object.r2 = 1.0f;
	object.origin = (cl_float4){.x = 5.0f, .y = 2.0f, .z = 0.0f, .w = 0.0f};
	object.rotation = (cl_float3){.x = 90.0f, .y = 0.0f, .z = 0.0f};
	object.scaling = (cl_float3){.x = 1.0f, .y = 1.0f, .z = 1.0f};
	texture.type = solid;
	texture.data.solid.color = (t_color){.r = 0.8f, .g = 0.6f, .b = 0.2f};
	object.material.type = matte;
	object.material.kr = 0.95f;
	object.material.kd = 0.8f;
	object.material.texture_id = add_texture(&instance_manager->texture_manager, texture);
	// add_parsed_object(instance_manager, object);

	object.type = paraboloid;
	object.r = 0.1f;
	object.r2 = 1.0f;
	object.origin = (cl_float4){.x = 0.0f, .y = 1.0f, .z = -2.0f, .w = 0.0f};
	object.rotation = (cl_float3){.x = 0.0f, .y = 0.0f, .z = 90.0f};
	object.scaling = (cl_float3){.x = 1.0f, .y = 1.0f, .z = 1.0f};
	texture.type = solid;
	texture.data.solid.color = (t_color){.r = 0.8f, .g = 0.6f, .b = 0.5f};
	object.material.type = matte;
	object.material.kr = 0.95f;
	object.material.kd = 0.8f;
	object.maxm = 3.0f;
	object.material.texture_id = add_texture(&instance_manager->texture_manager, texture);
	// add_parsed_object(instance_manager, object);

	object.type = rectangle;
	object.r = 5.0f;
	object.r2 = 5.0f;
	object.origin = (cl_float4){ -0.5f, 10.0f, 0.0f, 0.0f };
	object.scaling = (cl_float3){ 1.0f, 1.0f, 1.0f };
	object.rotation = (cl_float3){ .x = 90.0f, .y = 0.0f, .z = 0.0f};
	object.vector1 = (cl_float4){ .x = 1.0f, .y = 0.0f,.z = 0.0f };
	object.vector2 = (cl_float4){ .x = 0.0f, .y = 1.0f, .z = 0.0f };
	texture.type = solid;
	texture.data.solid.color = (t_color){ .r = 1.0f, .g = 1.0f, .b = 1.0f };
	object.material.type = emissive;
	object.material.kd = 1.0f;
	object.material.ls = 1.0f;
	object.material.texture_id = add_texture(&instance_manager->texture_manager, texture);
	// int i = add_parsed_object(instance_manager, object);

	object.type = triangle;
	object.origin = (cl_float4){ 0.0f, 0.0f, -2.0f, 0.0f};
	object.vector1 = (cl_float3){ 1.0f, 0.0f, 0.0f, 0.0f };
	object.vector2 = (cl_float3){ 0.0f, 1.0f, 0.0f, 0.0f };
	object.rotation = (cl_float3) { 0.0f, 0.0f, 0.0f, 0.0f };
	object.scaling = (cl_float3){ 1.0f, 1.0f, 1.0f };
	texture.data.solid.color = (t_color){.r = 1.0f, .g = 0.0f, .b = 1.0f};
	texture.type = solid;
	object.material.type = matte;
	// add_parsed_object(instance_manager, object);

	// set_sampler(instance_manager, i, new_sampler(sampler_manager, rand_jitter, 100, 0));

	t_parsed_light light;

	light.type = area;
	light.ls = 1.0f;
	light.color = (t_color){ .r = 1.0f, .b = 1.0f, .g = 1.0f};
	// int j = add_parsed_light(&scene->light_manager, light);
	// scene->light_manager.lights[j].object_id = i;
	// scene->light_manager.lights[j].matrix = get_transformation_matrix(*instance_manager, i);

	object.type = sphere;
	object.r = 1.0f;
	object.origin = (cl_float4){ -4.0f, 0.0f, -2.0f, 0.0f };
	object.scaling = (cl_float3){ 1.0f, 1.0f, 1.0f };
	object.rotation = (cl_float3){ 0.0f, 0.0f, 0.0f };
	texture.type = solid;
	texture.data.solid.color = (t_color){ .r = 1.0f, .g = 1.0f, .b = 1.0f };
	object.material.type = emissive;
	object.material.kd = 1.0f;
	object.material.ls = 1.0f;
	object.material.texture_id = add_texture(&instance_manager->texture_manager, texture);
	// add_parsed_object(instance_manager, object);

	/* Cornell box */
	scene->camera.type = thin_lens;
	scene->camera.l = 0.0f;
	scene->camera.f = 1000.0f;
	scene->camera.viewplane.pixel_size = 1.0f;
	scene->camera.viewplane.width = IMG_WIDTH;
	scene->camera.viewplane.height = IMG_HEIGHT;
	scene->camera.origin =
		(cl_float4){ .x = 278.0f, .y = 278.0f, .z = -800.0f, .w = 0.0f };
	scene->camera.direction =
		(cl_float4){ .x = 0.0f, .y = 0.0f, .z = 1.0f, .w = 0.0f };
	scene->camera.d = 900;
	scene->camera.zoom = 1.0f;
	scene->camera.normalized = FALSE;
	compute_uvw(&scene->camera);

	object.type = sphere;
	object.r = 1.0f;
	object.origin = (cl_float4){278.0f, 278.0f, 278.0f, 0.0f};
	object.scaling = (cl_float3){10.0f, 10.0f, 10.0f};
	object.rotation = (cl_float3){0.0f, 0.0f, 0.0f};
	texture.type = solid;
	texture.data.solid.color = (t_color){.r = 1.0f, .g = 1.0f, .b = 1.0f};
	object.material.type = diffuse_light;
	object.material.kd = 1.0f;
	object.material.texture_id = add_texture(&instance_manager->texture_manager, texture);
	// add_parsed_object(instance_manager, object);

	/* LEFT WALL */
	object.type = box;
	object.origin = (cl_float4){.x = 0.0f, .y = 0.0f, .z = 0.0f};
	object.scaling = (cl_float4){ 1.0f, 1.0f, 1.0f };
	object.vector1 = (cl_float4){.x = 0.0f, .y = 0.0f, .z = 0.0f};
	object.vector2 = (cl_float4){.x = 0.01f, .y = 555.0f, .z = 555.0f};
	texture.type = solid;
	texture.data.solid.color = (t_color){ .r = 0.0f, .g = 1.0f, .b = 0.0f };
	object.material.type = plastic;
	object.material.exp = 0.3f;
	object.material.kr = 0.5f;
	object.material.texture_id = add_texture(&instance_manager->texture_manager, texture);
	add_parsed_object(instance_manager, object);

	/* RIGHT WALL*/
	object.type = box;
	object.origin = (cl_float4){.x = 555.0f, .y = 0.0f, .z = 0.0f};
	object.scaling = (cl_float4){1.0f, 1.0f, 1.0f};
	object.vector1 = (cl_float4){.x = 0.0f, .y = 0.0f, .z = 0.0f};
	object.vector2 = (cl_float4){.x = 0.001f, .y = 555.0f, .z = 555.0f};
	texture.type = solid;
	texture.data.solid.color = (t_color){.r = 1.0f, .g = 0.0f, .b = 0.0f};
	object.material.type = plastic;
	object.material.kr = 0.2f;
	object.material.exp = 0.15f;
	object.material.kd = 1.0f;
	object.material.texture_id = add_texture(&instance_manager->texture_manager, texture);
	add_parsed_object(instance_manager, object);

	/* BOTTOM */
	object.type = box;
	object.origin = (cl_float4){.x = 0.0f, .y = 0.0f, .z = 0.0f};
	object.scaling = (cl_float4){1.0f, 1.0f, 1.0f};
	object.vector1 = (cl_float4){.x = 0.0f, .y = 0.0f, .z = 0.0f};
	object.vector2 = (cl_float4){.x = 555.0f, .y = 0.001f, .z = 555.0f};
	texture.type = solid;
	texture.data.solid.color = (t_color){.r = 1.0f, .g = 1.0f, .b = 1.0f};
	object.material.type = matte;
	object.material.exp = 2.01f;
	object.material.kd = 1.0f;
	object.material.texture_id = add_texture(&instance_manager->texture_manager, texture);
	add_parsed_object(instance_manager, object);

	object.type = box;
	object.origin = (cl_float4){.x = 0.0f, .y = 555.0f, .z = 0.0f};
	object.scaling = (cl_float4){1.0f, 1.0f, 1.0f};
	object.vector1 = (cl_float4){.x = 0.0f, .y = 0.0f, .z = 0.0f};
	object.vector2 = (cl_float4){.x = 555.0f, .y = 0.001f, .z = 555.0f};
	texture.type = solid;
	texture.data.solid.color = (t_color){.r = 1.0f, .g = 1.0f, .b = 1.0f};
	object.material.type = matte;
	object.material.kd = 1.0f;
	object.material.texture_id = add_texture(&instance_manager->texture_manager, texture);
	add_parsed_object(instance_manager, object);

	/* BACK WALL */
	object.type = box;
	object.origin = (cl_float4){.x = 0.0f, .y = 0.0f, .z = 555.0f};
	object.scaling = (cl_float4){1.0f, 1.0f, 1.0f};
	object.vector1 = (cl_float4){.x = 0.0f, .y = 0.0f, .z = 0.0f};
	object.vector2 = (cl_float4){.x = 555.0f, .y = 555.0f, .z = 0.001f};
	texture.type = solid;
	texture.data.solid.color = (t_color){.r = 1.0f, .g = 1.0f, .b = 1.0f};
	object.material.type = plastic;
	object.material.exp = 0.01f;
	object.material.kt = 1.8f;
	object.material.kr = 1.8f;
	object.material.kd = 1.0f;
	object.material.texture_id = add_texture(&instance_manager->texture_manager, texture);
	add_parsed_object(instance_manager, object);

	object.type = rectangle;
	object.origin = (cl_float4){ .x = 213.0f, .y = 553.0f, .z = 250.0f, .w = 0.0f };
	object.r = 130.0f;
	object.r2 = 105.0f;
	object.scaling = (cl_float3){1.0f, 1.0f, 1.0f};
	object.rotation = (cl_float3){.x = 90.0f, .y = 0.0f, .z = 0.0f};
	object.vector1 = (cl_float4){.x = 1.0f, .y = 0.0f, .z = 0.0f};
	object.vector2 = (cl_float4){.x = 0.0f, .y = 1.0f, .z = 0.0f};
	texture.type = solid;
	texture.data.solid.color = (t_color){.r = 1.0f, .g = 1.0f, .b = 1.0f};
	object.material.type = emissive;
	object.material.kd = 1.0f;
	object.material.ls = 1.0f;
	object.material.texture_id = add_texture(&instance_manager->texture_manager, texture);
	int i = add_parsed_object(instance_manager, object);
	set_sampler(instance_manager, i, new_sampler(sampler_manager, pure_random, 1024, 0));

	light.type = area;
	light.ls = 1.0f;
	light.color = (t_color){.r = 1.0f, .b = 1.0f, .g = 1.0f};
	int j = add_parsed_light(&scene->light_manager, light);
	scene->light_manager.lights[j].object_id = i;
	scene->light_manager.lights[j].matrix = get_transformation_matrix(*instance_manager, i);

	/* boxes inside */
	object.type = box;
	object.origin = (cl_float4){ .x = 265.0f, .y = 0.0f, .z = 135.0f, .w = 0.0f };
	object.vector1 = (cl_float4){ .x = 0.0f, .y = 0.0f, .z = 0.0f, .w = 0.0f };
	object.vector2 = (cl_float4){ .x = 165.0f, .y = 165.0f, .z = 165.0f, .w = 0.0f };
	object.rotation = (cl_float3){ .x = 0.0f, .y = 18.0f, .z = 0.0f };
	object.scaling = (cl_float4){ 1.0f, 1.0f, 1.0f };
	texture.type = solid;
	texture.data.solid.color = (t_color){ .r = 1.0f, .g = 1.0f, .b = 1.0f };
	object.material.type = mirror;
	object.material.kd = 1.0f;
	object.material.texture_id = add_texture(&instance_manager->texture_manager, texture);
	// add_parsed_object(instance_manager, object);

	object.type = box;
	object.origin = (cl_float4){.x = 130.0f, .y = 0.0f, .z = 265.0f, .w = 0.0f};
	object.vector1 = (cl_float4){.x = 0.0f, .y = 0.0f, .z = 0.0f, .w = 0.0f};
	object.vector2 = (cl_float4){.x = 165.0f, .y = 330.0f, .z = 165.0f, .w = 0.0f};
	object.rotation = (cl_float3){.x = 0.0f, .y = -18.0f, .z = 0.0f};
	object.scaling = (cl_float4){1.0f, 1.0f, 1.0f};
	texture.type = solid;
	texture.data.solid.color = (t_color){.r = 1.0f, .g = 1.0f, .b = 1.0f};
	object.material.type = matte;
	// object.material.type = metal;
	object.material.exp = 0.5f;
	object.material.kr = 1.0f;
	object.material.kd = 1.0f;
	object.material.texture_id = add_texture(&instance_manager->texture_manager, texture);
	add_parsed_object(instance_manager, object);

	object.type = sphere;
	object.r = 1.0f;
	object.origin = (cl_float4){.x = 350.0f, .y = 80.0f, .z = 190.0f, .w = 0.0f};
	object.scaling = (cl_float4){80.0f, 80.0f, 80.0f};
	object.rotation = (cl_float3){.x = 00.0f, .y = 0.0f, .z = 0.0f};
	texture.type = solid;
	texture.data.solid.color = (t_color){.r = 0.4f, .g = 0.4f, .b = 1.0f};
	object.material.type = plastic;
	object.material.exp = 0.01f;
	object.material.kt = 0.2f;
	object.material.kr = 0.8f;
	object.material.kd = 1.0f;
	object.material.ka = 0.1f;
	object.material.texture_id = add_texture(&instance_manager->texture_manager, texture);
	add_parsed_object(instance_manager, object);

	object.type = torus;
	object.r = 1.0f;
	object.r2 = 0.25f;
	object.origin = (cl_float4){ .x = 350.0f, .y = 100.0f, .z = 90.0f, .w = 0.0f };
	object.scaling = (cl_float3){ .x = 80.0f, .y = 60.0f, .z = 80.0f, .w = 0.0f };
	object.rotation = (cl_float4){ 30.0f, 0.0f, 45.0f };
	texture.type = solid;
	texture.data.solid.color = (t_color){ .r = 1.0f, .g = 1.0f, .b = 1.0f };
	object.material.type = dielectric;
	object.material.kt = 1.5f;
	object.material.texture_id = add_texture(&instance_manager->texture_manager, texture);
	// add_parsed_object(instance_manager, object);

	object.type = torus;
	object.r = 1.0f;
	object.r2 = 0.25f;
	object.origin = (cl_float4){ .x = 350.0f, .y = 100.0f, .z = 200.0f, .w = 0.0f };
	object.scaling = (cl_float3){ .x = 80.0f, .y = 60.0f, .z = 80.0f, .w = 0.0f };
	object.rotation = (cl_float4){ 30.0f, 0.0f, 135.0f };
	texture.type = solid;
	texture.data.solid.color = (t_color){ .r = 1.0f, .g = 1.0f, .b = 1.0f };
	object.material.type = dielectric;
	object.material.kt = 1.5f;
	object.material.texture_id = add_texture(&instance_manager->texture_manager, texture);
	// add_parsed_object(instance_manager, object);

	//Освещение

	scene->ambient_occluder.color = (t_color){.r = 1.0f, .g = 1.0f, .b = 1.0f};
	scene->ambient_occluder.ls = 0.2f;
	scene->ambient_occluder.min_amount = (t_color){ .r = 0.1f, .g = 0.1f, .b = 0.1f };
	scene->ambient_occluder.sampler_id = new_sampler(sampler_manager, rand_jitter, 100, HEMISPHERE_SAMPLES);

	scene->ambient_light = (t_light){
		.type = ambient,
		.ls = 0.2f,
		.color = {.r = 1.0f, .b = 1.0f, .g = 1.0f}};

	light.type = point;
	light.origin = default_point_light.origin;
	// light.origin.y = 1000.0f;
	light.direction = default_point_light.direction;
	light.ls = default_point_light.ls;
	light.color = default_point_light.color;
	// add_parsed_light(&scene->light_manager, light);
	// scene->lights[0] = default_point_light;

	light.type = default_directional_light.type;
	light.origin = default_directional_light.origin;
	light.direction = default_directional_light.direction;
	light.ls = default_directional_light.ls;
	light.ls = 1.0f;
	light.color = default_directional_light.color;
	// add_parsed_light(&scene->light_manager, light);
}
