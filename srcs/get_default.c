/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_default.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 17:11:31 by aapricot          #+#    #+#             */
/*   Updated: 2020/12/07 20:51:45 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "offset.h"

t_camera			get_default_camera(void)
{
	t_camera		camera;

	camera.viewplane.pixel_size = 1.0f;
	camera.viewplane.width = IMG_WIDTH;
	camera.viewplane.height = IMG_HEIGHT;
	camera.type = -2;
	camera.origin.x = NAN;
	camera.direction.x = NAN;
	camera.up = (cl_float4){.x = 0.0f, .y = 1.0f, .z = 0.0f, .w = 0.0f};
	camera.d = DEFAULT_WIDTH;
	camera.zoom = NAN;
	camera.normalized = FALSE;
	return (camera);
}

t_parsed_light		get_default_light(void)
{
	t_parsed_light	light;

	light.type = point;
	light.origin = (cl_float4){1.0f, 8.0f, -5.0f, 0.0f};
	light.ls = 2.0f;
	light.color = (t_color){1.0f, 1.0f, 1.0f};
	return (light);
}

void				set_default_texture(t_texture *texture)
{
	if (texture == NULL)
		rt_error("set_default_texture(): given NULL pointer");
	texture->type = -2;
	texture->data.solid.color.r = NAN;
	texture->data.checker.even.r = NAN;
	texture->data.checker.odd.r = NAN;
	texture->data.smooth_perlin.scale = NAN;
}

void				set_default_material(t_material *material)
{
	if (material == NULL)
		rt_error("set_default_material(): given NULL pointer");
	material->exp = NAN;
	material->is_reflective = 1;
	material->is_transparent = 1;
	material->ka = NAN;
	material->kd = NAN;
	material->kr = NAN;
	material->ks = NAN;
	material->kt = NAN;
	material->reflective_color = (t_color){1.0f, 0.0f, 0.0f};
	material->type = -2;
}

t_parsed_object		get_default_obj(void)
{
	t_parsed_object	obj;

	obj.direction = (cl_float4){NAN};
	set_default_material(&obj.material);
	set_default_texture(&obj.texture);
	obj.maxm = NAN;
	obj.minm = NAN;
	obj.origin = (cl_float4){NAN};
	obj.r2 = NAN;
	obj.r = NAN;
	obj.rotation.x = NAN;
	obj.scaling = (cl_float3){1.0f, 1.0f, 1.0f};
	obj.type = -2;
	obj.vector1.x = NAN;
	obj.vector2.x = NAN;
	return (obj);
}
