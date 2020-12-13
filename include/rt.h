/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:00:53 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/13 17:28:17 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <string.h>
# include <stdio.h>
# include <stdint.h>
# include <fcntl.h>
# include <math.h>

# include <assert.h>

# ifdef __APPLE__
#  include <SDL.h>
# elif __unix__
#  include <SDL2/SDL.h>
# else
#  include <SDL.h>
# endif

# include "sampler_manager.h"
# include "scene.h"
# include "rt_options.h"
# include "rt_ocl.h"
# include "rt.h"
# include "window.h"
# include "gui.h"
# include "resource_manager.h"
# include "interface.h"

typedef struct s_rt		t_rt;

struct	s_rt
{
	t_scene				scene;
	t_sampler_manager	sampler_manager;
	t_rt_options		options;
	t_cl_program		ocl_program;
};

int		init_rt(t_rt *rt, char *scene_file,
				t_res_mngr *resource_manager, t_window *window, t_image *image,
				cl_device_type device_type);

void	init_buffers(t_cl_program *const program, t_scene *const scene,
					t_sampler_manager *const sampler_manager);

void	render_scene(t_rt rt);

void	read_data(t_scene *scene, t_sampler_manager *sampler_manager,
						char *scene_file);

/*
** event_functions
*/

int		catch_event(t_rt *rt, t_window *win, t_interface *interface);

/*
** util functions
*/

float	rand_float();
int		rand_int();
void	swap_int(int *a, int *b);
void	swap_float2(cl_float2 *a, cl_float2 *b);

/*
**		src/rt_error.c
*/

void	rt_error(char *message);

# define WIDTH 1200
# define HEIGHT 600

#endif
