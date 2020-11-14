/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 17:43:55 by dmelessa          #+#    #+#             */
/*   Updated: 2020/11/11 00:34:16 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app.h"

int		init_app(t_app *app, int ac, char **av)
{
	char	*scene_file;

	//todo: parse command line arguments
	scene_file = NULL;
	init_window(&app->window);
	init_resource_manager(&app->resource_manager, &app->rt);
	init_rt(&app->rt, scene_file, &app->resource_manager);
	// init_gui(&app->gui);
}
