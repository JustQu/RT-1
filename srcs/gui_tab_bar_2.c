/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_tab_bar_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 14:53:11 by alex              #+#    #+#             */
/*   Updated: 2020/11/12 14:42:25 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "rt.h"

void			is_type_lights(t_window *win, t_rt *rt,
					t_all_rect *rect, t_colors *color)
{
	char		*str[4];
	int			ptr;

	ptr = 0;//rt->ten.current_id;
	if (rt->scene.lights[ptr].type == directional)
	{
		get_float4_data(rt->scene.lights[ptr].direction, "Direction", &str);
		draw_button_xyz(win, &rect->eight_button, str, color);
		free_str(&str);
	}
	if (rt->scene.lights[ptr].type == point)
	{
		get_float4_data(rt->scene.lights[ptr].origin, "Origin", &str);
		draw_button_xyz(win, &rect->eight_button, str, color);
		free_str(&str);
	}
	if (rt->scene.lights[ptr].type == area)
	{
		get_float_data(rt->scene.lights[ptr].object_id, "Object_id", &str);
		draw_button(win, &rect->eight_button, str, color);
		free_str(&str);
	}
	if (rt->scene.lights[ptr].type == ambient_occluder)
	{
		get_float_data(rt->scene.lights[ptr].ls, "Min light", &str);
		draw_button(win, &rect->eight_button, str, color);
		free_str(&str);
	}
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
			"reflective", &str);//reflective coefficient
		draw_button(win, &rect->nine_button, str, color);
		free_str(&str);
	}
	if (rt->scene.instance_mngr.instances_info[ptr].material.type == dielectric)
	{
		get_float_data(rt->scene.instance_mngr.instances_info[ptr].material.kt,
			"transparent", &str);//transparent coefficient
		draw_button(win, &rect->nine_button, str, color);
		free_str(&str);
	}
	if (rt->scene.instance_mngr.instances_info[ptr].material.type == emissive)
	{
		get_float_data(rt->scene.instance_mngr.instances_info[ptr].material.ks,
			"specular", &str);//transparent coefficient
		draw_button(win, &rect->nine_button, str, color);
		free_str(&str);
	}
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

void			objects_tab_cont(t_window *win, t_rt *rt,
					t_all_rect *rect, t_colors *color)
{
	char		*str[4];
	int			ptr;

	ptr = rt->options.current_id;
	shape_type_vision(win, rt, rect, color);
	SDL_SetRenderDrawColor(win->renderer, color->text_color.r,
	color->text_color.g, color->text_color.b, color->text_color.a);
	SDL_RenderDrawLine(win->renderer, rect->background.x,
		rect->seven_button.y - MARGIN_Y,
		rect->seven_button.x + rect->seven_button.w,
		rect->seven_button.y - MARGIN_Y);
	get_material_data(rt->scene.instance_mngr.instances_info[ptr].material.type,
		"Material", &str); // material type
	draw_button(win, &rect->seven_button, str, color);
	free_str(&str);
	get_float_data(rt->scene.instance_mngr.instances_info[ptr].material.ka,
		"ambient", &str); // ambient reflect
	draw_button(win, &rect->eight_button, str, color);
	free_str(&str);
	gui_material_type(win, rt, rect, color);
	get_texture_data(rt->scene.instance_mngr.texture_manager.textures->type,
		"texture", &str); // texture type
	SDL_SetRenderDrawColor(win->renderer, color->text_color.r,
	color->text_color.g, color->text_color.b, color->text_color.a);
	SDL_RenderDrawLine(win->renderer, rect->background.x,
		rect->ten_button.y - MARGIN_Y,
		rect->ten_button.x + rect->ten_button.w,
		rect->ten_button.y - MARGIN_Y);
	draw_button(win, &rect->ten_button, &str, color);
	free_str(&str);
	get_float_data(1, "Color", &str);
	draw_button(win, &rect->eleven_button, &str, color);
	free_str(&str);
}
