/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 17:43:55 by dmelessa          #+#    #+#             */
/*   Updated: 2020/11/23 17:46:47 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app.h"

int		init_app(t_app *app, int ac, char **av)
{
	char	*scene_file;

	//todo: parse command line arguments
	scene_file = NULL;
	if (ac == 2)
		scene_file = av[1];
	init_window(&app->window);
	init_resource_manager(&app->resource_manager, &app->rt);
	init_rt(&app->rt, scene_file, &app->resource_manager);
	return (0);
	// init_gui(&app->gui);
}
