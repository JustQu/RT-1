/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_tab_bar_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 14:53:11 by alex              #+#    #+#             */
/*   Updated: 2020/12/13 21:20:51 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "rt.h"

static void		is_type_light_cont(t_window *win,
					t_gui *gui)
{
	char		*str[4];

	if (gui->current_light.type == area)
	{
		get_float_data(gui->current_light.object_id, "Object_id", str);
		draw_button(win, &gui->all_rect.eight_button, str, &gui->colors);
		free_str(str);
	}
	if (gui->current_light.type == ambient_occluder)
	{
		get_float_data(gui->current_light.ls, "Min light", str);
		draw_button(win, &gui->all_rect.eight_button, str, &gui->colors);
		free_str(str);
	}
}

void			is_type_lights(t_window *win,
					t_gui *gui)
{
	char		*str[4];

	if (gui->current_light.type == directional)
	{
		get_float4_data(gui->current_light.direction, "Direction", str);
		draw_button_xyz(win, &gui->all_rect.eight_button, str, &gui->colors);
		free_str(str);
	}
	if (gui->current_light.type == point)
	{
		get_float4_data(gui->current_light.origin, "Origin", str);
		draw_button_xyz(win, &gui->all_rect.eight_button, str, &gui->colors);
		free_str(str);
	}
	is_type_light_cont(win, gui);
}

void			gui_material_type(t_window *win,
					t_gui *gui)
{
	char		*str[4];

	if (gui->current_instance.material.type == metal)
	{
		get_float_data(gui->current_instance.material.kr, // ?
			"reflective", str);
		draw_button(win, &gui->all_rect.nine_button, str, &gui->colors);
		free_str(str);
	}
	if (gui->current_instance.material.type == dielectric)
	{
		get_float_data(gui->current_instance.material.ks, // ?
			"transparent", str);
		draw_button(win, &gui->all_rect.nine_button, str, &gui->colors);
		free_str(str);
	}
	if (gui->current_instance.material.type == emissive)
	{
		get_float_data(gui->current_instance.material.kt, // ?
			"specular", str);
		draw_button(win, &gui->all_rect.nine_button, str, &gui->colors);
		free_str(str);
	}
}

static void		shape_type_vision(t_window *win,
					t_gui *gui)
{
	if (gui->current_instance.type == cone)
		gui_cone_vision(win, gui);
	else if (gui->current_instance.type == cylinder)
		gui_cylinder_vision(win, gui);
	else if (gui->current_instance.type == sphere)
		gui_disk_vision(win, gui);
	else if (gui->current_instance.type == torus)
		gui_torus_vision(win, gui);
	else if (gui->current_instance.type == box)
		gui_box_vision(win, gui);
	else if (gui->current_instance.type == disk)
		gui_disk_vision(win, gui);
	else if (gui->current_instance.type == rectangle)
		gui_rectangle_vision(win, gui);
}

void			objects_tab_cont(t_window *win,
					t_gui *gui)
{
	char		*str[4];

	shape_type_vision(win, gui);
	draw_line(win, &gui->colors, gui->all_rect.background,
		gui->all_rect.seven_button);
	get_material_data(gui->current_instance.material.type,
						"Material", str);
	draw_button(win, &gui->all_rect.seven_button, str, &gui->colors);
	free_str(str);
	get_float_data(gui->current_instance.material.ks, // ?
					"ambient", str);
	draw_button(win, &gui->all_rect.eight_button, str, &gui->colors);
	free_str(str);
	gui_material_type(win, gui);
	get_texture_data(1,// ?
						"texture", str);
	utils_call_objects_tab_cont(win, gui, str);
	get_color_data(gui->options.background_color, "Color", str); // ?
	free(str[1]);
	str[1] = NULL;
	draw_button(win, &gui->all_rect.eleven_button, str, &gui->colors);
	draw_color_button(win, &gui->colors, gui->options.background_color,
		&gui->all_rect.eleven_button); //?
	free_str(str);
}
