/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 17:02:27 by dmelessa          #+#    #+#             */
/*   Updated: 2020/10/28 20:22:44 by alex             ###   ########.fr       */
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

typedef struct s_app	t_app;

struct	s_app
{
	t_rt			rt;
	t_window		window;
	// t_gui			gui;
};

int			init_app(t_app *app, int ac, char **av);
void		cleanup_app(t_app *app);

/* errors */
void cl_error(t_cl_program *program, t_clp *clp, int code);
void ft_clerror(cl_int ret);

#endif
