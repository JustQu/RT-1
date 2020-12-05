/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 17:02:27 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/03 21:16:10 by dmelessa         ###   ########.fr       */
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

typedef struct s_app	t_app;

/*
** mode: 0 - gui, 1 - console
** todo: interface struct
*/
struct	s_app
{
	t_res_mngr		resource_manager;
	t_rt			rt;
	t_window		window;

	int				mode; //0 - gui, 1 - console
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
