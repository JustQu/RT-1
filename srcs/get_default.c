/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_default.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 17:11:31 by aapricot          #+#    #+#             */
/*   Updated: 2020/11/23 21:37:02 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "offset.h"

t_camera		get_default_camera()
{
	t_camera	camera;

	camera.viewplane.pixel_size = 1.0f;
	camera.viewplane.width = IMG_WIDTH;
	camera.viewplane.height = IMG_HEIGHT;
	camera.type = perspective;
	camera.origin = (cl_float4){.x = 0.0f, .y = 1.0f, .z = -8.0f, .w = 0.0f};
	camera.direction = (cl_float4){.x = 0.0f, .y = -0.1f, .z = 1.0f, .w = 0.0f};
	camera.up = (cl_float4){.x = 0.0f, .y = 1.0f, .z = 0.0f, .w = 0.0f};
	camera.d = DEFAULT_WIDTH;
	camera.zoom = 0.5f;
	camera.normalized = FALSE;
	return (camera);
}

t_parsed_light			get_default_light()
{
	t_parsed_light		light;

	light.type = point;
	light.origin = (cl_float4){1.0f, 8.0f, -5.0f, 0.0f};
	light.ls = 2.0f;
	light.color = (t_color){1.0f, 1.0f, 1.0f};
	return (light);
}

void			set_default_texture(t_texture *texture)
{
	texture->type = solid;
	texture->data.solid.color = (t_color){1.0f, 1.0f, 1.0f};
	texture->data.checker.even = (t_color){0.5f, 0.5f, 0.5f};
	texture->data.checker.odd = (t_color){0.0f, 0.0f, 1.0f};
	texture->data.smooth_perlin.scale = 0.0f;
}

void			set_default_material(t_material *material)
{
	material->exp = 0.0f;
	material->is_reflective = 1;
	material->is_transparent = 1;
	material->ka = 0.0f;
	material->kd = 1.0f;
	material->kr = 0.0f;
	material->ks = 0.0f;
	material->kt = 0.0f;
	material->reflective_color = (t_color){1.0f, 0.0f, 0.0f};
	material->type = matte;
}

t_parsed_object		get_default_obj()
{
	t_parsed_object	obj;

	obj.direction = (cl_float4){NAN};
	set_default_material(&obj.material);
	set_default_texture(&obj.texture);
	obj.maxm = 0.0f;
	obj.minm = 0.0f;
	obj.origin = (cl_float4){NAN};
	obj.r2 = 0.0f;
	obj.r= 0.0f;
	obj.rotation = (cl_float3){0.0f, 0.0f, 0.0f};
	obj.scaling = (cl_float3){1.0f, 1.0f, 1.0f};
	obj.type = -2;
	obj.vector1 = (cl_float4){0.0f, 0.0f, 0.0f};
	obj.vector2 = (cl_float4){0.0f, 0.0f, 0.0f};
	return (obj);
}

t_rt_options		get_default_options()
{
	t_rt_options	options;

	options.shadows = 1;
	options.depth = 1;
	return (options);
}