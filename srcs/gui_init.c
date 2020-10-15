/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 13:33:27 by user              #+#    #+#             */
/*   Updated: 2020/10/15 13:50:25 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "window.h"
#include "rt_options.h"
#include "rt.h"

void	init_rect(t_all_rect *rect, t_window *win)
{
	rect->background = init_rect_size(win->width - 300, 0, WIDTH_MENU, HEIGHT);

	rect->tab_camera_button = init_rect_size(win->width - win->width / 4,
		win->height / 9, (win->width / 4) / 3, 30);

	rect->tab_objects_button = init_rect_size(win->width - win->width / 4 + rect->tab_camera_button.w,
		win->height / 9, (win->width / 4) / 3, 30);

	rect->tab_options_button = init_rect_size(win->width - win->width / 4 +
		rect->tab_camera_button.w + rect->tab_objects_button.w, win->height / 9, (win->width / 4) / 3, 30);

	rect->type_button = init_rect_size(win->width - win->width / 4 + SPACER,
		rect->tab_camera_button.y + rect->tab_camera_button.h + MARGIN_Y, win->width / 4, 30);

	rect->position_button = init_rect_size(win->width - win->width / 4 + SPACER,
		rect->type_button.y + rect->type_button.h + MARGIN_Y,  win->width / 4, 30);

	rect->direction_button = init_rect_size(win->width - win->width / 4 + SPACER,
		rect->position_button.y + rect->position_button.h + MARGIN_Y * 4, win->width / 4, 30);

	rect->radius_button = init_rect_size(win->width - win->width / 4 + SPACER,
		rect->direction_button.y + rect->direction_button.h + MARGIN_Y * 4, win->width / 4, 30);

	rect->rotate_button = init_rect_size(win->width - win->width / 4 + SPACER,
		rect->radius_button.y + rect->radius_button.h + MARGIN_Y * 2, win->width / 4, 30);

	rect->color_button = init_rect_size(win->width - win->width / 4 + SPACER,
		rect->rotate_button.y + rect->rotate_button.h + MARGIN_Y * 2, win->width / 4, 30);

	rect->diffuse_button = init_rect_size(win->width - win->width / 4 + SPACER,
		rect->color_button.y + rect->color_button.h + MARGIN_Y * 2, win->width / 4, 30);

	rect->reflection_button = init_rect_size(win->width - win->width / 4 + SPACER,
		rect->diffuse_button.y + rect->diffuse_button.h + MARGIN_Y * 2, win->width / 4, 30);

	rect->alpha_button = init_rect_size(win->width - win->width / 4 + SPACER,
		rect->reflection_button.y + rect->reflection_button.h + MARGIN_Y * 2, win->width / 4, 30);

	rect->samplers_button = init_rect_size(win->width - win->width / 4 + SPACER,
		rect->type_button.y + rect->type_button.h + MARGIN_Y * 2, win->width / 4, 30);

	rect->deep_button = init_rect_size(win->width - win->width / 4 + SPACER,
		rect->samplers_button.y + rect->samplers_button.h + MARGIN_Y * 2, win->width / 4, 30);

	rect->background_button = init_rect_size(win->width - win->width / 4 + SPACER,
		rect->deep_button.y + rect->deep_button.h + MARGIN_Y * 2, win->width / 4, 30);

	rect->resolution_button = init_rect_size(win->width - win->width / 4 + SPACER,
		rect->background_button.y + rect->background_button.h + MARGIN_Y * 2, win->width / 4, 30);

	rect->type_choise_rect = init_rect_size(rect->type_button.x + MARGIN,
		rect->type_button.y - 100, rect->type_button.w - 150 - MARGIN * 2, 100);
}

void	init_colors(t_colors *color)
{
	color->background_color = init_color(240, 240, 240, 0);

	color->border_color = init_color(14, 128, 217, 0);

	color->inside_color = init_color(226, 241, 252, 0);

	color->text_color = init_color(10, 15, 15, 0);
}
