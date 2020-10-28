/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_tab_bar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 18:03:59 by user              #+#    #+#             */
/*   Updated: 2020/10/28 20:28:25 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "rt.h"

#include <stdio.h>

void			camera_tab(t_window *win, t_rt *rt, t_all_rect *rect,
					t_colors *color)
{
	char		*str[4];
	t_camera	*camera;

	str[0] = malloc(20);
	str[1] = malloc(15);
	str[2] = malloc(15);
	str[3] = (char*)malloc(sizeof(char) * 15);
	camera = get_camera(rt->scene);
	sprintf(str[0], "Position");
	sprintf(str[1], "%.3f", camera->origin.x);
	sprintf(str[2], "%.3f", camera->origin.y);
	sprintf(str[3], "%.3f", camera->origin.z);
	render_tab_bar(win, &color->text_color, &rect->tab_camera_button, "Camera");
	SDL_SetRenderDrawColor(win->renderer, color->text_color.r,
		color->text_color.g, color->text_color.b, color->text_color.a);
	SDL_RenderDrawLine(win->renderer, rect->tab_camera_button.x,
		rect->tab_camera_button.y + rect->tab_camera_button.h,
		rect->tab_camera_button.x + rect->tab_camera_button.w,
		rect->tab_camera_button.y + rect->tab_camera_button.h);
	draw_button(win, &rect->type_button, "Type camera", color);
	if (g_type_pressed)
		draw_is_pressed_button(win, &rect->type_button, "Type camera", color);
	draw_button_xyz(win, &rect->position_button, str, color);
	sprintf(str[0], "Direction");
	draw_button_xyz(win, &rect->direction_button, str, color);
	draw_button(win, &rect->save_img_button, "Save image", color);
}

void			objects_tab(t_window *win, t_rt *rt,
					t_all_rect *rect, t_colors *color)
{
	char		*str[4];

	str[0] = "Position";
	str[1] = "2.32";
	str[2] = "4.32";
	str[3] = "3.43";
	render_tab_bar(win, &color->text_color, &rect->tab_objects_button,
		"Objects");
	SDL_SetRenderDrawColor(win->renderer, color->text_color.r,
		color->text_color.g,
		color->text_color.b, color->text_color.a);
	SDL_RenderDrawLine(win->renderer, rect->tab_objects_button.x,
		rect->tab_objects_button.y + rect->tab_objects_button.h,
		rect->tab_objects_button.x + rect->tab_objects_button.w,
		rect->tab_objects_button.y + rect->tab_objects_button.h);
	draw_button(win, &rect->type_button, "Material", color);
	if (g_type_pressed)
		draw_is_pressed_button(win, &rect->type_button, "Material", color);
	draw_button_xyz(win, &rect->position_button, str, color);
	str[0] = "Direction";
	draw_button_xyz(win, &rect->direction_button, str, color);
	draw_button(win, &rect->radius_button, "Radius", color);
	draw_button(win, &rect->rotate_button, "Rotate", color);
	draw_button(win, &rect->color_button, "Color", color);
	draw_button(win, &rect->diffuse_button, "Diffuse", color);
	draw_button(win, &rect->reflection_button, "Reflection", color);
	draw_button(win, &rect->alpha_button, "Alpha", color);
}

void			option_tab(t_window *win, t_rt *rt,
					t_all_rect *rect, t_colors *color)
{
	render_tab_bar(win, &color->text_color,
		&rect->tab_options_button, "Options");
	SDL_SetRenderDrawColor(win->renderer, color->text_color.r,
	color->text_color.g, color->text_color.b, color->text_color.a);
	SDL_RenderDrawLine(win->renderer, rect->tab_options_button.x,
		rect->tab_options_button.y + rect->tab_options_button.h,
		rect->tab_options_button.x + rect->tab_options_button.w,
		rect->tab_options_button.y + rect->tab_options_button.h);
	draw_button(win, &rect->type_button, "Type RT", color);
	draw_button(win, &rect->samplers_button, "Samplers", color);
	draw_button(win, &rect->deep_button, "Deep", color);
	draw_button(win, &rect->background_button, "Background", color);
	draw_button(win, &rect->resolution_button, "Resolution", color);
}

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
	draw_inside_button(win, rt, rect, color);
}
