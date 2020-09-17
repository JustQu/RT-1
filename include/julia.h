/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 15:32:04 by user              #+#    #+#             */
/*   Updated: 2020/09/15 18:17:31 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _JULIA_H_
# define _JULIA_H_

#define J_WIDTH 800
#define J_HEIGHT 800

#include <SDL2/SDL.h>

#define GL_SILENCE_DEPRECATION
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl.h>
#include <OpenGL/CGLDevice.h>
#include <GLUT/glut.h>
#include <OpenCL/opencl.h>

#define GL_SILENCE_DEPRECATION
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl.h>
#include <OpenGL/CGLDevice.h>
#include <GLUT/glut.h>
#include <OpenCL/opencl.h>

#include <mach/mach_time.h>
#include <math.h>

#include <fcntl.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <mach/mach_time.h>

#define COMPUTE_KERNEL_FILENAME	("srcs/qjulia_cl/qjulia_kernel.cl")
#define COMPUTE_KERNEL_METHOD_NAME ("QJuliaKernel")

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

typedef struct			s_texture
{
	uint				id;
	uint				target;
	uint				format;
	uint				type;
	uint				internal;
	size_t				type_size;
	uint				active_uint;
	void				*host_image_buffer;
}						t_texture;

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

void					init_julia_color(t_julia_color *color);
void					init_compute_cl(t_compute *compute);
void					init_texture_cl(t_texture *texture);
void					setup_color(float color[4], float r,
							float g, float b, float a);
void					random_color(float v[4]);
void					update_mu(float t[4], float a[4], float b[4]);
int						divide_up(int a, int b);
void					interpolate(float m[4], float t, float a[4], float b[4]);
void					update_color(float t[4], float a[4], float b[4]);
void					error_julia(int err, char *str);
void					julia_texture(t_texture *texture);
int						recompute(t_compute *compute, t_julia_color *color);
int						create_compute_result(t_texture *texture, t_compute *compute);
int						setup_compute_kernel(t_compute *compute);
int						load_text_from_file(
							const char *file_name, char **result_string, size_t *string_len);
int						setup_compute_device(t_compute *compute);
int						setup_graphics(t_texture *texture);
void					create_texture(t_texture *texture);
int						init_cl(t_texture *texture, t_compute *compute,
							t_julia_color *color);
int						main_qjulia();
#endif
