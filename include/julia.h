/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 15:32:04 by user              #+#    #+#             */
/*   Updated: 2020/11/10 14:51:55 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _JULIA_H_
# define _JULIA_H_

# define J_WIDTH 800
# define J_HEIGHT 800

# include <SDL2/SDL.h>

# define GL_SILENCE_DEPRECATION
# include <OpenGL/OpenGL.h>
# include <OpenGL/gl.h>
# include <OpenGL/CGLDevice.h>
# include <GLUT/glut.h>
# include <OpenCL/opencl.h>

# include <math.h>

# include <fcntl.h>
# include <stdarg.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "rt.h"

# define COMPUTE_KERNEL_FILENAME ("srcs/cl/qjulia_kernel.cl")
# define COMPUTE_KERNEL_METHOD_NAME ("QJuliaKernel")

typedef struct			s_julia_color
{
	float				mut;
	float				mua[4];
	float				mub[4];
	float				muc[4];
	float				epsilon;
	float				color_t;
	float				color_a[4];
	float				color_b[4];
	float				color_c[4];
}						t_julia_color;

typedef struct			s_texture2
{
	uint32_t			id;
	uint32_t			target;
	uint32_t			format;
	uint32_t			type;
	uint32_t			internal;
	size_t				type_size;
	uint32_t			active_uint;
	void				*host_image_buffer;
}						t_texture2;

typedef struct			s_compute
{
	cl_context			context;
	cl_command_queue	commands;
	cl_device_type		device_type;
	cl_device_id		device_id;
	cl_program			program;
	cl_kernel			kernel;
	cl_mem				result;
	cl_mem				image;
	int					animated;
	int					update;
	size_t				max_work_group_size;
	int					work_group_size[2];
	int					work_group_items;
}						t_compute;

SDL_Window				*qjulia_sdl_init(void);
void					gl_render_init(t_texture2 *texture);
void					init_julia_color(t_julia_color *color);
void					init_compute_cl(t_compute *compute);
void					init_texture_cl(t_texture2 *texture);
int						recompute(t_compute *compute,
							t_julia_color *color);
void					setup_color(float color[4], SDL_Color *colors);
int						setup_compute_device(t_compute *compute);
void					setup_preprocessor(t_compute *compute,
							char *source);
void					random_color(float v[4]);
void					update_mu(float t[4], float a[4], float b[4]);
int						divide_up(int a, int b);
void					interpolate(float m[4], float t,
							float a[4], float b[4]);
void					update_color(float t[4], float a[4], float b[4]);
void					error_julia(int err, char *str);
void					julia_texture(t_texture2 *texture);
int						recompute(t_compute *compute, t_julia_color *color);
int						create_compute_result(t_texture2 *texture,
							t_compute *compute);
int						setup_compute_kernel(t_compute *compute);
int						load_text_from_file(
							const char *file_name,
							char **result_string, size_t *string_len);
int						setup_compute_device(t_compute *compute);
int						setup_graphics(t_texture2 *texture);
void					create_texture(t_texture2 *texture);
int						init_cl(t_texture2 *texture, t_compute *compute,
							t_julia_color *color);
void					main_qjulia(void);
void					display(t_texture2 *texture, t_compute *compute,
							t_julia_color *color);
void					qjulia_render_texture(t_texture2 *texture);
void					shutdown(t_compute *compute);
void					cleanup(t_compute *compute);
int						origin_region(t_compute *compute);
void					ft_values(t_compute *compute,
							t_julia_color *color);

#endif