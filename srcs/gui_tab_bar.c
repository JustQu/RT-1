/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_tab_bar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 18:03:59 by user              #+#    #+#             */
/*   Updated: 2020/11/10 15:15:05 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "rt.h"
#include "libft.h"
#include "julia.h"

#include <stdio.h>

void			is_type_lights(t_window *win, t_rt *rt,
					t_all_rect *rect, t_colors *color)
{
	char		*str[4];
	int			ptr;

	ptr = 0;//rt->options.current_id;
	if (rt->scene.lights[ptr].type == directional)
	{
		get_float4_data(rt->scene.lights[ptr].direction, "Direction", &str);
		draw_button_xyz(win, &rect->eight_button, str, color);
	}
	if (rt->scene.lights[ptr].type == point)
	{
		get_float4_data(rt->scene.lights[ptr].origin, "Origin", &str);
		draw_button_xyz(win, &rect->eight_button, str, color);
	}
	if (rt->scene.lights[ptr].type == area)
	{
		get_float_data(rt->scene.lights[ptr].object_id, "Object_id", &str);
		draw_button(win, &rect->eight_button, str, color);
	}
	if (rt->scene.lights[ptr].type == ambient_occluder)
	{
		get_float_data(rt->scene.lights[ptr].ls, "Min light", &str);
		draw_button(win, &rect->eight_button, str, color);
	}
	free_str(&str);
}

void			camera_tab(t_window *win, t_rt *rt, t_all_rect *rect,
					t_colors *color)
{
	char		*str[4];

	render_tab_bar(win, &color->text_color, &rect->tab_camera_button, "Camera");
	SDL_SetRenderDrawColor(win->renderer, color->text_color.r,
		color->text_color.g, color->text_color.b, color->text_color.a);
	SDL_RenderDrawLine(win->renderer, rect->tab_camera_button.x,
		rect->tab_camera_button.y + rect->tab_camera_button.h,
		rect->tab_camera_button.x + rect->tab_camera_button.w,
		rect->tab_camera_button.y + rect->tab_camera_button.h);
	get_camera_type_data(rt->scene.camera.type, "Type camera", &str);
	draw_button(win, &rect->first_button, str, color);
	get_float4_data(rt->scene.camera.origin, "Position", &str);
	draw_button_xyz(win, &rect->second_button, str, color);
	get_float4_data(rt->scene.camera.direction, "Direction", &str);
	draw_button_xyz(win, &rect->third_button, str, color);
	get_str_data("save", "Save image", &str);
	draw_button(win, &rect->fourth_button, str, color);
	get_void_data("Light", &str);
	draw_button(win, &rect->fifth_button, str, color);
	light_tab(win, rt, rect, color);
	free_str(&str);
}

void			shape_type_vision(t_window *win, t_rt *rt,
					t_all_rect *rect, t_colors *color)
{
	if (rt->scene.instance_mngr.instances_info[rt->options.current_id].type
		== cone)
		gui_cone_vision(win, rt, rect, color);
	else if (rt->scene.instance_mngr.instances_info[rt->options.current_id].type
		== cylinder)
		gui_cylinder_vision(win, rt, rect, color);
	else if (rt->scene.instance_mngr.instances_info[rt->options.current_id].type
		== sphere)
		gui_disk_vision(win, rt, rect, color);
	else if (rt->scene.instance_mngr.instances_info[rt->options.current_id].type
		== torus)
		gui_torus_vision(win, rt, rect, color);
	else if (rt->scene.instance_mngr.instances_info[rt->options.current_id].type
		== box)
		gui_box_vision(win, rt, rect, color);
	else if (rt->scene.instance_mngr.instances_info[rt->options.current_id].type
		== disk)
		gui_disk_vision(win, rt, rect, color);
	else if (rt->scene.instance_mngr.instances_info[rt->options.current_id].type
		== rectangle)
		gui_rectangle_vision(win, rt, rect, color);
}

void			gui_material_type(t_window *win, t_rt *rt,
					t_all_rect *rect, t_colors *color)
{
	char		*str[4];
	int			ptr;

	ptr = rt->options.current_id;
	if (rt->scene.instance_mngr.instances_info[ptr].material.type == metal)
	{
		get_float_data(rt->scene.instance_mngr.instances_info[ptr].material.kr,
			"reflective", &str);	//reflective coefficient
		draw_button(win, &rect->nine_button, str, color);
		free_str(&str);
	}
	if (rt->scene.instance_mngr.instances_info[ptr].material.type == dielectric)
	{
		get_float_data(rt->scene.instance_mngr.instances_info[ptr].material.kt,
			"transparent", &str);	//transparent coefficient
		draw_button(win, &rect->nine_button, str, color);
		free_str(&str);
	}
	if (rt->scene.instance_mngr.instances_info[ptr].material.type == emissive)
	{
		get_float_data(rt->scene.instance_mngr.instances_info[ptr].material.ks,
			"specular", &str);	//transparent coefficient
		draw_button(win, &rect->nine_button, str, color);
		free_str(&str);
	}
}

void			objects_tab_cont(t_window *win, t_rt *rt,
					t_all_rect *rect, t_colors *color)
{
	char		*str[4];
	int			ptr;

	ptr = rt->options.current_id;
	get_material_data(rt->scene.instance_mngr.instances_info[ptr].material.type,
		"Material", &str); // material type
	draw_button(win, &rect->seven_button, str, color);
	get_float_data(rt->scene.instance_mngr.instances_info[ptr].material.ka,
		"ambient", &str); // ambient reflect
	draw_button(win, &rect->eight_button, str, color);
	gui_material_type(win, rt, rect, color);
	get_texture_data(rt->scene.instance_mngr.texture_manager.textures->type,
		"texture", &str); // texture type
	draw_button(win, &rect->ten_button, &str, color);
	free_str(&str);
}



void			objects_tab(t_window *win, t_rt *rt,
					t_all_rect *rect, t_colors *color)
{
	char		*str[4];

	render_tab_bar(win, &color->text_color, &rect->tab_objects_button,
		"Objects");
	SDL_SetRenderDrawColor(win->renderer, color->text_color.r,
		color->text_color.g,
		color->text_color.b, color->text_color.a);
	SDL_RenderDrawLine(win->renderer, rect->tab_objects_button.x,
		rect->tab_objects_button.y + rect->tab_objects_button.h,
		rect->tab_objects_button.x + rect->tab_objects_button.w,
		rect->tab_objects_button.y + rect->tab_objects_button.h);
	get_shape_data(
	rt->scene.instance_mngr.instances_info[rt->options.current_id].type,
		"Shape", &str); // objects type
	draw_button(win, &rect->first_button, str, color);
	get_float4_data(rt->scene.camera.origin, "Origin", &str);
	draw_button_xyz(win, &rect->second_button, str, color);
	get_float4_data(rt->scene.camera.direction, "Rotation", &str);
	draw_button_xyz(win, &rect->third_button, str, color);
	get_float4_data(
	rt->scene.instance_mngr.instances_info[rt->options.current_id].scaling,
		"Scalling", &str); // scaling data
	draw_button_xyz(win, &rect->fourth_button, str, color);
	shape_type_vision(win, rt, rect, color);
	objects_tab_cont(win, rt, rect, color);
	free_str(&str);
}

void			light_tab(t_window *win, t_rt *rt,
					t_all_rect *rect, t_colors *color)
{
	char		*str[4];

	SDL_SetRenderDrawColor(win->renderer, color->text_color.r,
		color->text_color.g, color->text_color.b, color->text_color.a);
	SDL_RenderDrawLine(win->renderer, rect->tab_camera_button.x,
		rect->fifth_button.y + rect->fifth_button.h,
		rect->fifth_button.x + rect->fifth_button.w,
		rect->fifth_button.y + rect->fifth_button.h);
	get_intensive_data(rt->scene.lights[0].type,
		"Type", &str);
	draw_button(win, &rect->sixth_button, str, color);
	get_float_data(rt->scene.lights[0].ls,
		"Intensity", &str);
	draw_button(win, &rect->seven_button, str, color);
	is_type_lights(win, rt, rect, color);
	get_str_data("julia", "Fractal", &str);
	SDL_SetRenderDrawColor(win->renderer, color->text_color.r,
		color->text_color.g, color->text_color.b, color->text_color.a);
	SDL_RenderDrawLine(win->renderer, rect->tab_camera_button.x,
		rect->ten_button.y - MARGIN_Y,
		rect->ten_button.x + rect->ten_button.w,
		rect->ten_button.y - MARGIN_Y);
	draw_button(win, &rect->ten_button, str, color);
	free_str(&str);
}

void			option_tab(t_window *win, t_rt *rt,
					t_all_rect *rect, t_colors *color)
{
	char	*str[4];

	render_tab_bar(win, &color->text_color,
		&rect->tab_options_button, "Options");
	SDL_SetRenderDrawColor(win->renderer, color->text_color.r,
	color->text_color.g, color->text_color.b, color->text_color.a);
	SDL_RenderDrawLine(win->renderer, rect->tab_options_button.x,
		rect->tab_options_button.y + rect->tab_options_button.h,
		rect->tab_options_button.x + rect->tab_options_button.w,
		rect->tab_options_button.y + rect->tab_options_button.h);
	get_float_data(1, "Type RT", &str); // need type rt
	draw_button(win, &rect->first_button, str, color);
	get_float_data(rt->scene.camera.sampler_id, "Samplers", &str); //samplers
	draw_button(win, &rect->samplers_button, str, color);
	get_float_data(rt->scene.camera.d, "Deep", &str);
	draw_button(win, &rect->deep_button, str, color);
	// draw_button(win, &rect->background_button, "Background", color);
	// draw_button(win, &rect->resolution_button, "Resolution", color);
	free_str(&str);
}

void			gui_tab_bar(t_window *win, t_rt *rt,
					t_all_rect *rect, t_colors *color)
{
	SDL_SetRenderDrawColor(win->renderer, color->border_color.r,
		color->border_color.g, color->border_color.b, color->border_color.a);
	SDL_RenderDrawLine(win->renderer, rect->tab_camera_button.x,
		rect->tab_options_button.y + rect->tab_options_button.h,
		rect->tab_camera_button.x + rect->tab_options_button.x +
		rect->tab_options_button.w, rect->tab_options_button.y +
		rect->tab_options_button.h);
	if (g_camera_tab_pressed == 1)
		camera_tab(win, rt, rect, color);
	else
		render_tab_bar(win, &color->border_color,
			&rect->tab_camera_button, "Camera");
	if (g_objects_tab_pressed == 1)
		objects_tab(win, rt, rect, color);
	else
		render_tab_bar(win, &color->border_color,
			&rect->tab_objects_button, "Objects");
	if (g_options_tab_pressed == 1)
		option_tab(win, rt, rect, color);
	else
		render_tab_bar(win, &color->border_color,
			&rect->tab_options_button, "Options");
}
