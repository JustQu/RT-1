/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_tab_bar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 18:03:59 by user              #+#    #+#             */
/*   Updated: 2020/11/20 09:33:37 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "rt.h"
#include "libft.h"

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
	free_str(&str);
	get_float4_data(rt->scene.camera.origin, "Position", &str);
	draw_button_xyz(win, &rect->second_button, str, color);
	free_str(&str);
	get_float4_data(rt->scene.camera.direction, "Direction", &str);
	draw_button_xyz(win, &rect->third_button, str, color);
	free_str(&str);
	get_str_data("save", "Save image", &str);
	draw_button(win, &rect->fourth_button, str, color);
	free_str(&str);
	get_void_data("Light", &str);
	draw_button(win, &rect->fifth_button, str, color);
	free_str(&str);
	light_tab(win, rt, rect, color);
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
	1, "Shape", &str); // objects type
	draw_button(win, &rect->first_button, str, color);
	free_str(&str);
	get_float4_data(rt->scene.camera.origin, "Origin", &str);
	draw_button_xyz(win, &rect->second_button, str, color);
	free_str(&str);
	get_float4_data(rt->scene.camera.direction, "Rotation", &str);
	draw_button_xyz(win, &rect->third_button, str, color);
	free_str(&str);
	get_float4_data(
	rt->scene.camera.direction, "Scalling", &str); // scaling data
	draw_button_xyz(win, &rect->fourth_button, str, color);
	free_str(&str);
	objects_tab_cont(win, rt, rect, color);
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
	get_intensive_data(1,
		"Type", &str); //type intensity
	draw_button(win, &rect->sixth_button, str, color);
	free_str(&str);
	get_float_data(1,
		"Intensity", &str); // intensity
	draw_button(win, &rect->seven_button, str, color);
	is_type_lights(win, rt, rect, color);
	free_str(&str);
}

void			type_ambien_il(t_window *win, t_rt *rt,
					t_all_rect *rect, t_colors *color)
{
	char *str[4];

	if (rt->scene.ambient_light.type == 0)
	{
		get_float_data(1, "coefficient", &str); // ambient coef
		draw_button(win, &rect->sixth_button, str, color);
		free_str(&str);
	}
	if (rt->scene.ambient_light.type == 1)
	{
		get_float_data(1, "min_amount", &str); // min amount
		draw_button(win, &rect->sixth_button, str, color);
		free_str(&str);
	}
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
	free_str(&str);
	get_float_data(rt->scene.camera.sampler_id, "Samplers", &str); //samplers
	draw_button(win, &rect->second_button, str, color);
	free_str(&str);
	get_float_data(rt->scene.camera.d, "Deep", &str);
	draw_button(win, &rect->third_button, str, color);
	free_str(&str);
	get_float_data(1, "Back_color", &str); //get background color
	draw_button(win, &rect->fourth_button, str, color);
	free_str(&str);
	get_ambient_il_data(1, "Ambient_il", &str); // get
	draw_button(win, &rect->fifth_button, str, color);
	free_str(&str);
	type_ambien_il(win, rt, rect, color);
	get_true_data(1, "Shadows", &str); // get shadows
	draw_button(win, &rect->seven_button, str, color);
	free_str(&str);
	get_float_data(1, "Depth", &str); // get depth
	draw_button(win, &rect->eight_button, str, color);
	free_str(&str);
	get_true_data(1, "Global_il", &str); // get global_illumination
	draw_button(win, &rect->nine_button, str, color);
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
