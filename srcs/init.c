/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 17:43:55 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/11 21:13:39 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app.h"

/*
** @brief
**
** @todo: parse command line arguments
** 		  init gui
** @param app
** @param ac
** @param av
** @return ** int
*/

int		init_app(t_app *app, int ac, char **av)
{
	char	*scene_file;

	if (app == NULL || av == NULL)
		rt_error("init_app(): given NULL pointer");
	scene_file = NULL;
	if (ac == 2)
		scene_file = av[1];
	if (init_window(&app->window))
		rt_error("init_app(): init_window() error");
	if (init_resource_manager(&app->resource_manager, &app->rt))
		rt_error("init_app(): init_resource_manager() error");
	if (init_rt(&app->rt, scene_file, &app->resource_manager, &app->window))
		rt_error("init_app(): init_rt() error");
	return (SUCCESS);
}
