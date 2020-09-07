/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 15:32:04 by user              #+#    #+#             */
/*   Updated: 2020/09/07 18:21:59 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _JULIA_H_
# define _JULIA_H_

#define WIDTH 1200
#define HEIGHT 800

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

#define COMPUTE_KERNEL_FILENAME	("qjulia_kernel.cl")
#define COMPUTE_KERNEL_METHOD_NAME ("QJuliaKernel")

static int animated		= 1;
static int update		= 1;

static cl_context		compute_context;
static cl_command_queue	compute_commands;
static cl_device_type	compute_device_type;
static cl_device_id		compute_device_id;

static cl_program		compute_program;
static cl_kernel		compute_kernel;
static cl_mem			compute_result;
static cl_mem			compute_image;

static size_t			max_work_group_size;
static int				work_group_size[2];
static int				work_group_items = 32;

static uint texture_id = 0;
static uint texture_width = WIDTH;
static uint texture_height = HEIGHT;
static uint texture_target = GL_TEXTURE_2D;
static uint texture_format = GL_RGBA;
static uint texture_type	= GL_UNSIGNED_BYTE;
static uint texture_internal = GL_RGBA;
static size_t texture_type_size = sizeof(char);
static uint active_texture_uint = 0x84C1;
static void *host_image_buffer = 0;

static float mut			= 0.0f;
static float mua[4]			= { -.278f, -.479f, 0.0f, 0.0f };
static float mub[4]			= { 0.278f, 0.479f, 0.0f, 0.0f };
static float muc[4]			= { -.278f, -.479f, -.231f, .235f };

static float epsilon		= 0.003f;

static float color_t		= 0.0f;
static float color_a[4]		= { 0.25f, 0.45f, 1.0f, 1.0f };
static float color_b[4]		= { 0.25f, 0.45f, 1.0f, 1.0f };
static float color_c[4]		= { 0.25f, 0.45f, 1.0f, 1.0f };

static float shadow_text_color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
static float highlight_text_color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
static uint text_offset[2]			= { 25, 25};

static double time_elapsed	= 0;
static int frame_count 		= 0;
static uint report_stats_interval = 30;

static float tex_coords[4][2];

static float vertex_pos[4][2] = { { -1.0f, -1.0f},
								  { +1.0f, -1.0f},
								  { +1.0f, +1.0f},
								  { -1.0f, +1.0f} };

static uint show_stats		= 1;
static char stats_string[512] = "\0";
static uint show_info		= 1;
static char info_string[512] = "\0";

#endif
