/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 17:43:55 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/15 21:10:42 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app.h"
#include "gui.h"

/*
** @brief
**
** @todo: parse command line arguments
** @param app
** @param ac
** @param av
** @return ** int
*/

int		init_app(t_app *app)
{
	init_window(&app->window, app->options.window_width,
				app->options.window_height);
	init_image(&app->image, app->options.image_width,
				app->options.image_height);
	init_interface(&app->interface, app->options.mode, app->options.enable_gui);
	init_gui(&app->interface.gui, app->window);
	init_resource_manager(&app->resource_manager, &app->rt);
	init_rt(&app->rt, app->options.scene_file,
			&app->resource_manager, &app->window, &app->image,
			app->options.render_device);
	app->rt.scene.camera.viewplane.width = app->options.image_width;
	app->rt.scene.camera.viewplane.height = app->options.image_height;
	return (SUCCESS);
}
