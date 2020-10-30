/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_tab_bar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 18:03:59 by user              #+#    #+#             */
/*   Updated: 2020/10/30 21:35:05 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "rt.h"
#include "libft.h"

#include <stdio.h>

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
	draw_button(win, &rect->type_button, str, color);
	/* if (g_type_pressed) */
	 	/* draw_is_pressed_button(win, &rect->type_button, str[1], color); */
	get_float4_data(rt->scene.camera.origin, "Position", &str);
	draw_button_xyz(win, &rect->position_button, str, color);
	get_float4_data(rt->scene.camera.direction, "Direction", &str);
	draw_button_xyz(win, &rect->direction_button, str, color);
	get_str_data("save", "Save image", &str);
	draw_button(win, &rect->save_img_button, str, color);
}

void			objects_tab_cont(t_window *win, t_rt *rt,
					t_all_rect *rect, t_colors *color)
{
	char		*str[4];

	get_float4_data(rt->scene.camera.origin, "Position", &str);
	draw_button_xyz(win, &rect->position_button, str, color);
	get_float4_data(rt->scene.camera.direction, "Direction", &str);
	draw_button_xyz(win, &rect->direction_button, str, color);
	get_float_data(rt->scene.camera.l, "Radius", &str);
	draw_button(win, &rect->radius_button, str, color);
	get_float_data(rt->scene.camera.ratio, "Rotate", &str); //need radius
	draw_button(win, &rect->rotate_button, str, color);
	get_float_data(rt->scene.camera.d, "Color", &str);	//need color
	draw_button(win, &rect->color_button, str, color);
	get_float_data(rt->scene.camera.d, "Diffuse", &str); // need diffuse
	draw_button(win, &rect->diffuse_button, str, color);
	get_float_data(rt->scene.camera.zoom, "Reflection", &str); // need reflection
	draw_button(win, &rect->reflection_button, str, color);
	get_float_data(rt->scene.camera.f, "Alpha", &str);	//need alpha
	draw_button(win, &rect->alpha_button, str, color);
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
	get_material_data(1,
		"Material", &str); // rt->scene.instance_mngr.instances_info->material.type dont work
	draw_button(win, &rect->type_button, str, color);
	/* if (g_type_pressed) */
	 	/* draw_is_pressed_button(win, &rect->type_button, str[1], color); */
	objects_tab_cont(win, rt, rect, color);
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
	draw_button(win, &rect->type_button, str, color);
	get_float_data(rt->scene.camera.sampler_id, "Samplers", &str); //samplers
	draw_button(win, &rect->samplers_button, str, color);
	get_float_data(rt->scene.camera.d, "Deep", &str);
	draw_button(win, &rect->deep_button, str, color);
	// draw_button(win, &rect->background_button, "Background", color);
	// draw_button(win, &rect->resolution_button, "Resolution", color);
}

/*
void			draw_inside_button(t_window *win, t_rt *rt,
					t_all_rect *rect, t_colors *color)
{
	char		*str[4];

	str[0] = "type1";
	str[1] = "type2";
	str[2] = "type3";
	str[3] = "type4";
	str[4] = NULL;
	if (g_type_pressed == 1 && g_camera_tab_pressed == 1)
	{
		SDL_SetRenderDrawColor(win->renderer, 43, 43, 45, 255);
		SDL_RenderFillRect(win->renderer, &rect->type_choise_rect);
		g_size = 4;
		draw_button_choise(win, &rect->type_choise_rect, str, color);
	}
	if (g_type_pressed == 1 && g_objects_tab_pressed == 1)
	{
		SDL_SetRenderDrawColor(win->renderer, 43, 43, 45, 255);
		SDL_RenderFillRect(win->renderer, &rect->type_choise_rect);
		g_size = 3;
		draw_button_choise(win, &rect->type_choise_rect, str, color);
	}
	if (g_type_pressed == 1 && g_options_tab_pressed == 1)
	{
		SDL_SetRenderDrawColor(win->renderer, 43, 43, 45, 255);
		SDL_RenderFillRect(win->renderer, &rect->type_choise_rect);
		g_size = 2;
		draw_button_choise(win, &rect->type_choise_rect, str, color);
	}
}
*/

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
	// draw_inside_button(win, rt, rect, color);
}
