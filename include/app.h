/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 17:02:27 by dmelessa          #+#    #+#             */
/*   Updated: 2020/10/30 23:38:49 by dmelessa         ###   ########.fr       */
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
};

int			init_app(t_app *app, int ac, char **av);
void		cleanup_app(t_app *app);

/* errors */
void cl_error(t_cl_program *program, t_clp *clp, int code);
void ft_clerror(cl_int ret);

#endif
