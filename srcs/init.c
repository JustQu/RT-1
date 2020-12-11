/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 17:43:55 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/10 18:32:03 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app.h"

/*
** @brief
**
** @todo: parse command line arguments
** @param app
** @param ac
** @param av
** @return ** int
*/

int		init_app(t_app *app, int ac, char **av)
{
	char	*scene_file;

	scene_file = NULL;
	if (ac == 2)
		scene_file = av[1];
	init_window(&app->window);
	init_gui(&app->gui);
	init_resource_manager(&app->resource_manager, &app->rt);
	init_rt(&app->rt, scene_file, &app->resource_manager);
	return (SUCCESS);
}
