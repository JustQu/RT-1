/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 17:02:27 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/10 23:27:12 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APP_H
# define APP_H

/*
** Main header of the app.
** Include other parts of programm
*/

# include "rt.h"
# include "window.h"
# include "interface.h"
# include "parser.h"
# include "resource_manager.h"

typedef struct s_app			t_app;
typedef struct s_app_options	t_app_opt;

/*
** mode: 0 - gui, 1 - console
** todo: interface struct
*/

struct	s_app
{
	t_res_mngr		resource_manager;
	t_rt			rt;
	t_window		window;
	t_gui			gui;

	// t_image			image;

	t_s32			render_mode;//console mode, window mode
};

struct	s_app_options
{
	char	*scene_file;

	int		num_samples;

	int		enable_gui;
	int		mode;//console or window or server or client
	int		interface;//gui or console or no

	int		enable_logs;
	char	*log_file;
};

/*
** Initialization of our app
*/

int			init_app(t_app *app, int ac, char **av);

/*
** Cleaning everything on exit
*/

void		cleanup_app(t_app *app);

/*
** Error functions
*/

void cl_error(t_cl_program *program, t_clp *clp, int code);
void ft_clerror(cl_int ret);

#endif
