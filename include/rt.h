/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:00:53 by dmelessa          #+#    #+#             */
/*   Updated: 2020/10/10 14:06:40 by user             ###   ########.fr       */
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
# include "window.h"
# include "gui.h"

typedef struct			s_rt
{
	t_scene				scene;
	t_sampler_manager	sampler_manager;
	t_rt_options		options;
	t_cl_program		ocl_program;
}						t_rt;

// typedef struct		s_rt
// {
// 	t_sdl			sdl;
//     t_gui           gui;
//     t_vector        direction;
//     t_vector        center;
//     t_vector        rotate;
// 	t_pressed		is_pressed;
// }					t_rt;

int			init_rt(t_rt *rt, char *scene_file);

void		render_scene(t_rt rt);

void		read_data(t_scene *scene, t_sampler_manager *sampler_manager, char *scene_file);

/* events */
int			catch_event(t_rt *rt, t_window *win, t_all_rect *rect, t_colors *color);

/* utils */
float		rand_float();
int			rand_int();
void		swap_int(int *a, int *b);
void		swap_float2(cl_float2 *a, cl_float2 *b);

// #include <SDL2/SDL.h>
#define WIDTH 1200
#define HEIGHT 600

#endif
