/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 17:02:27 by dmelessa          #+#    #+#             */
/*   Updated: 2020/11/14 18:40:10 by dmelessa         ###   ########.fr       */
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

struct	s_app
{
	t_res_mngr		resource_manager;
	t_rt			rt;
	t_window		window;
	t_gui			gui;

	int				mode; //0 - gui, 1 - console
};

int			init_app(t_app *app, int ac, char **av);
void		cleanup_app(t_app *app);

/* errors */
void cl_error(t_cl_program *program, t_clp *clp, int code);
void ft_clerror(cl_int ret);

#endif
