/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 15:31:08 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/13 15:19:17 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERFACE_H
# define INTERFACE_H

# include "gui.h"
# include "console.h"

typedef struct s_gui				t_gui;
typedef struct s_interface			t_interface;
typedef struct s_console_handler	t_console;

typedef enum e_interface_mode		t_interface_mode;

enum	e_interface_mode
{
	no_interface = 0,
	console = 1 << 0,
	window_mode = 1 << 1
};

struct	s_console_handler
{
	int	fd; //stdout now
};

struct	s_interface
{
	t_gui				gui;
	t_console			t_console;

	t_interface_mode	mode;

	//info for displaying
	t_instance_info		current_instance;
	t_light				current_light;
	t_camera			camera;
	t_rt_options		options;

	int					enable_gui;

	t_u32				current_instance_id;
	t_u32				current_light_id;
};


void	init_interface(t_interface *const interface, int interface_mode,
						int enable_gui);

int	display_instance_info(t_interface *const interface);
int	display_light_info(t_interface *const interface);
int	display_camera_info(t_interface *const interface);
int	display_options_info(t_interface *const interface);

#endif
