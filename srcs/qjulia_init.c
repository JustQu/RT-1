/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qjulia_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 16:05:53 by user              #+#    #+#             */
/*   Updated: 2020/11/08 16:07:05 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "julia.h"

int			init_cl(t_texture2 *texture, t_compute *compute,
				t_julia_color *color)
{
	int		err;
	cl_bool	image_support;

	err = setup_graphics(texture);
	if (err != GL_NO_ERROR)
		error_julia(err, "Failed to setup openGL state");
	err = setup_compute_device(compute);
	if (err != CL_SUCCESS)
		error_julia(err, "Failed to connect to compute device! Error");
	err = clGetDeviceInfo(compute->device_id, CL_DEVICE_IMAGE_SUPPORT,
							sizeof(image_support), &image_support, NULL);
	if (err != CL_SUCCESS)
		error_julia(err, "Unable to query device for image support");
	if (image_support == CL_FALSE)
		error_julia(err, "Images not supported on this device.");
	err = setup_compute_kernel(compute);
	if (err != CL_SUCCESS)
		error_julia(err, "Failed to setup compute kernel! Error");
	err = create_compute_result(texture, compute);
	if (err != CL_SUCCESS)
		error_julia(err, "Failed to create compute result! Error");
	random_color(color->color_a);
	random_color(color->color_b);
	random_color(color->color_c);
	return (CL_SUCCESS);
}

SDL_Color		init_sdl_colors(float r, float g, float b, float a)
{
	SDL_Color color;

	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
	return (color);
}

void		init_julia_color(t_julia_color *color)
{
	SDL_Color colors;

	color->mut = 0.0f;
	colors = init_sdl_colors(-.278f, -.479f, 0.0f, 0.0f);
	setup_color(color->mua, &colors);
	colors = init_sdl_colors(0.278f, 0.479f, 0.0f, 0.0f);
	setup_color(color->mub, &colors);
	colors = init_sdl_colors(-.278f, -.479f, -.231f, .235f);
	setup_color(color->muc, &colors);
	color->epsilon = 0.003f;
	color->color_t = 0.0f;
	colors = init_sdl_colors(0.25f, 0.45f, 1.0f, 1.0f);
	setup_color(color->color_a, &colors);
	setup_color(color->color_b, &colors);
	setup_color(color->color_c, &colors);
}

void		init_texture_cl(t_texture2 *texture)
{
	texture->id = 0;
	texture->target = GL_TEXTURE_2D;
	texture->format = GL_RGBA;
	texture->type = GL_UNSIGNED_BYTE;
	texture->internal = GL_RGBA;
	texture->type_size = sizeof(char);
	texture->active_uint = 0x84C1;
	texture->host_image_buffer = 0;
}

void		init_compute_cl(t_compute *compute)
{
	compute->device_id = 0;
	compute->context = 0;
	compute->commands = 0;
	compute->device_type = 0;
	compute->image = 0;
	compute->kernel = 0;
	compute->program = 0;
	compute->result = 0;
	compute->work_group_items = 32;
	compute->animated = 1;
	compute->update = 1;
}
