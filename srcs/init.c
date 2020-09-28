/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 17:43:55 by dmelessa          #+#    #+#             */
/*   Updated: 2020/09/27 00:33:46 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app.h"

int		init_app(t_app *app, int ac, char **av)
{
	char	*scene_file;

	//todo: parse command line arguments
	scene_file = NULL;
	init_window(&app->window);
	init_rt(&app->rt, scene_file);
	// init_gui(&app->gui);
}
