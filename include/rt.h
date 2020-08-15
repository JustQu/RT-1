/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:00:53 by dmelessa          #+#    #+#             */
/*   Updated: 2020/08/13 19:00:03 by dmelessa         ###   ########.fr       */
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
# include <SDL.h>
# elif __unix__
#  include "SDL2/SDL.h"
# else
#  include "SDL.h"
# endif

# include "libft.h"
# include "world.h"
# include "bool.h"
# include "sampler_manager.h"
# include "instance_manager.h"

# ifdef _WIN64
#  define DEFAULT_KERNEL_FILE "main_kernel.cl"
#  define DEFAULT_KERNEL_DIR "./srcs/cl/"
# else
#  define DEFAULT_KERNEL_FILE "main_kernel.cl"
#  define DEFAULT_KERNEL_DIR "./srcs/cl/"
# endif

/**
** NOTE: нельзя сделать кернел с именем 'main'
** на встроенной видеокарте intel
*/
# define DEFAULT_KERNEL_NAME	"main_kernel"

# define DEFAULT_KERNEL_INCLUDE	"-I ./include -I ./srcs/cl"
# define DEFAULT_WORK_SIZE		DEFAULT_WIDTH * DEFAULT_HEIGHT

#define SUCCESS	0
#define ERROR	-1

/**
** @brief
** информация о opencl
*/
typedef struct			s_clp
{
	cl_platform_id		pl_id;
	cl_device_id		de_id;
	cl_uint				ret_num_devices;
	cl_uint				ret_num_platforms;
	cl_int				ret;
	cl_context			context;
	cl_command_queue	queue;
}						t_clp;

/**
** @brief
** to manipulate sdl windows
*/
typedef struct			s_window
{
	SDL_Window			*ptr;
	SDL_Renderer		*renderer;
	SDL_Texture			*texture;
	uint32_t			*image; // TODO(dmelessa): change to cl_image later
	t_color				*rgb_image;
	int					width;
	int					height;
}						t_window;

/**
** @brief
** all information needed to start our kernel
*/
typedef struct			s_cl_program
{
	t_clp				clp;

	cl_program			program;

	cl_kernel			kernel;
	cl_kernel			new_kernel;
	cl_kernel			help_kernel;

	cl_mem				rgb_image;
	cl_mem				output_image;
	cl_mem				instances;
	cl_mem				objects;
	cl_mem				triangles;
	cl_mem				matrices;
	cl_mem				lights;
	cl_mem				samplers;
	cl_mem				samples;
	cl_mem				disk_samples;
	cl_mem				hemisphere_samples;

	size_t				work_size;
	size_t				work_group_size;
}						t_cl_program;

/**
** @brief
** struct containing information about scene: camera, objects, triangles and light sources
*/
typedef struct s_scene	t_scene;
struct					s_scene
{
	t_instance_manager	instance_manager;
	t_light				ambient_light;
	t_light				*lights;
	t_ambient_occluder	ambient_occluder;
	t_camera			camera;
	int					nlights;
};

typedef struct			s_rt
{
	t_cl_program		program;
	t_window			window;
	t_scene				scene;
	t_sampler_manager	sampler_manager;
	t_render_options	options;
}						t_rt;

/* program initialization */
int			init_window(t_window *window);
int			init_rt(t_rt *rt, char *scene_file);
int			init_sampler_manager(t_sampler_manager *sampler_manager);
cl_program	create_program(cl_context context);

void		read_data(t_scene *scene, t_sampler_manager *sampler_manager, char *scene_file);

/* events */
int			catch_event(t_rt *rt);

/* errors */
void		cl_error(t_cl_program *program, t_clp *clp, int code);
void		ft_clerror(cl_int ret);

/* utils */
float		rand_float();
int			rand_int();
void		swap_int(int *a, int *b);
void		swap_float2(cl_float2 *a, cl_float2 *b);

#endif
