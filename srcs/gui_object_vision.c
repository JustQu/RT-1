/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_object_vision.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 15:16:50 by alex              #+#    #+#             */
/*   Updated: 2020/12/13 18:35:19 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "rt.h"

void			gui_cone_vision(t_window *win, t_gui *gui)
{
	char		*str[4];

	if (gui->options.depth >= 0)
		;
	get_float_data(gui->current_instance.r, "Angle", str); // ?
	draw_button(win, &gui->all_rect.fifth_button, str, &gui->colors);
	free_str(str);
	get_float_data(gui->current_instance.height, "Height", str); // ?
	draw_button(win, &gui->all_rect.sixth_button, str, &gui->colors);
	free_str(str);
}

void			gui_cylinder_vision(t_window *win, t_gui *gui)
{
	char		*str[4];

	if (gui->options.depth >= 0)
		;
	get_float_data(gui->current_instance.r, "Radius", str); // ?
	draw_button(win, &gui->all_rect.fifth_button, str, &gui->colors);
	free_str(str);
	get_float_data(gui->current_instance.height, "Height", str); // ?
	draw_button(win, &gui->all_rect.sixth_button, str, &gui->colors);
	free_str(str);
}

void			gui_torus_vision(t_window *win, t_gui *gui)
{
	char		*str[4];

	if (gui->options.depth >= 0)
		;
	get_float_data(gui->current_instance.r2, "Radius all", str); // ?
	draw_button(win, &gui->all_rect.fifth_button, str, &gui->colors);
	free_str(str);
	get_float_data(gui->current_instance.r, "Radius", str); // ?
	draw_button(win, &gui->all_rect.sixth_button, str, &gui->colors);
	free_str(str);
}

void			gui_box_vision(t_window *win, t_gui *gui)
{
	char		*str[4];

	if (gui->options.depth >= 0)
		;
	get_float_data(gui->current_instance.e, "minimum", str); // ?
	draw_button(win, &gui->all_rect.fifth_button, str, &gui->colors);
	free_str(str);
	get_float_data(gui->current_instance.e, "maximum", str); // ?
	draw_button(win, &gui->all_rect.sixth_button, str, &gui->colors);
	free_str(str);
}

void			gui_rectangle_vision(t_window *win, t_gui *gui)
{
	char		*str[4];

	if (gui->options.depth >= 0)
		;
	get_float4_data(gui->current_instance.v1, "Vector 1", str);
	draw_button(win, &gui->all_rect.fifth_button, str, &gui->colors);
	free_str(str);
	get_float4_data(gui->current_instance.v2, "Vector 2", str);
	draw_button(win, &gui->all_rect.sixth_button, str, &gui->colors);
	free_str(str);
}
