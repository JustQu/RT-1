/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_tab_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 11:31:47 by jvoor             #+#    #+#             */
/*   Updated: 2020/12/16 11:31:53 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "rt.h"

void			utils_call_objects_tab_cont(t_window *win,
											t_gui *gui, char **str)
{
	draw_line(win, &gui->colors, gui->all_rect.background,
			  gui->all_rect.ten_button);
	draw_button(win, &gui->all_rect.ten_button, str, &gui->colors);
	free_str(str);
}