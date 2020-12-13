/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_object_vision.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 15:16:50 by alex              #+#    #+#             */
/*   Updated: 2020/12/13 03:18:33 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "rt.h"

void			gui_cone_vision(t_window *win, t_rt *rt, t_all_rect *rect,
								t_colors *color)
{
	char		*str[4];

	get_float_data(1, "Angle", str);
	draw_button(win, &rect->fifth_button, str, color);
	free_str(str);
	get_float_data(2, "Height", str);
	draw_button(win, &rect->sixth_button, str, color);
	free_str(str);
}

void			gui_cylinder_vision(t_window *win, t_rt *rt, t_all_rect *rect,
									t_colors *color)
{
	char		*str[4];

	get_float_data(1, "Radius", str);
	draw_button(win, &rect->fifth_button, str, color);
	free_str(str);
	get_float_data(2, "Height", str);
	draw_button(win, &rect->sixth_button, str, color);
	free_str(str);
}

void			gui_torus_vision(t_window *win, t_rt *rt, t_all_rect *rect,
								t_colors *color)
{
	char		*str[4];

	get_float_data(1, "Radius all", str);
	draw_button(win, &rect->fifth_button, str, color);
	free_str(str);
	get_float_data(2, "Radius", str);
	draw_button(win, &rect->sixth_button, str, color);
	free_str(str);
}

void			gui_box_vision(t_window *win, t_rt *rt, t_all_rect *rect,
								t_colors *color)
{
	char		*str[4];

	get_float_data(1, "minimum", str);
	draw_button(win, &rect->fifth_button, str, color);
	free_str(str);
	get_float_data(2, "maximum", str);
	draw_button(win, &rect->sixth_button, str, color);
	free_str(str);
}

void			gui_rectangle_vision(t_window *win, t_rt *rt, t_all_rect *rect,
										t_colors *color)
{
	char		*str[4];

	get_float4_data(rt->scene.camera.direction, "Vector 1", str);
	draw_button(win, &rect->fifth_button, str, color);
	free_str(str);
	get_float4_data(rt->scene.camera.direction, "Vector 2", str);
	draw_button(win, &rect->sixth_button, str, color);
	free_str(str);
}
