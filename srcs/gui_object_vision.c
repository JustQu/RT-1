/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_object_vision.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 15:16:50 by alex              #+#    #+#             */
/*   Updated: 2020/12/04 22:32:08 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "rt.h"

void			gui_cone_vision(t_window *win, t_rt *rt,
					t_all_rect *rect, t_colors *color)
{
	char		*str[4];

	if (win == NULL || rt == NULL || rect == NULL || color == NULL)
		rt_error("gui_cone_vision(): given NULL pointer");
	get_float_data(1, "Angle", str); // angle cone
	draw_button(win, &rect->fifth_button, str, color);
	free_str(str);
	get_float_data(2, "Height", str); //height cone
	draw_button(win, &rect->sixth_button, str, color);
	free_str(str);
}

void			gui_cylinder_vision(t_window *win, t_rt *rt,
					t_all_rect *rect, t_colors *color)
{
	char		*str[4];

	if (win == NULL || rt == NULL || rect == NULL || color == NULL)
		rt_error("gui_cylinder_vision(): given NULL pointer");
	get_float_data(1,
		"Radius", str); // radius cilin
	draw_button(win, &rect->fifth_button, str, color);
	free_str(str);
	get_float_data(2,
		"Height", str); //height cilin
	draw_button(win, &rect->sixth_button, str, color);
	free_str(str);
}

void			gui_torus_vision(t_window *win, t_rt *rt,
					t_all_rect *rect, t_colors *color)
{
	char		*str[4];

	if (win == NULL || rt == NULL || rect == NULL || color == NULL)
		rt_error("gui_torus_vision(): given NULL pointer");
	get_float_data(1,
		"Radius all", str); // radius torus max
	draw_button(win, &rect->fifth_button, str, color);
	free_str(str);
	get_float_data(2,
		"Radius", str); //radius  torus min
	draw_button(win, &rect->sixth_button, str, color);
	free_str(str);
}

void			gui_box_vision(t_window *win, t_rt *rt,
					t_all_rect *rect, t_colors *color)
{
	char		*str[4];

	if (win == NULL || rt == NULL || rect == NULL || color == NULL)
		rt_error("gui_box_vision(): given NULL pointer");
	get_float_data(1,
		"minimum", str); // min box
	draw_button(win, &rect->fifth_button, str, color);
	free_str(str);
	get_float_data(2,
		"maximum", str); //max box
	draw_button(win, &rect->sixth_button, str, color);
	free_str(str);
}

void			gui_rectangle_vision(t_window *win, t_rt *rt,
					t_all_rect *rect, t_colors *color)
{
	char		*str[4];

	if (win == NULL || rt == NULL || rect == NULL || color == NULL)
		rt_error("gui_rectangle_vision(): given NULL pointer");
	get_float4_data(rt->scene.camera.direction,
		"Vector 1", str); // vector 1 rectangle
	draw_button(win, &rect->fifth_button, str, color);
	free_str(str);
	get_float4_data(rt->scene.camera.direction, "Vector 2", str); //vector 2 rectangle
	draw_button(win, &rect->sixth_button, str, color);
	free_str(str);
}
