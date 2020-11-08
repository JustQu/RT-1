/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qjulia_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 16:05:53 by user              #+#    #+#             */
/*   Updated: 2020/11/08 14:21:07 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "julia.h"

int		init_cl(t_texture2 *texture, t_compute *compute, t_julia_color *color)
{
	int err;
	cl_bool image_support;

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
		error_julia(err, "Qjulia requires images: Images not supported on this device.");
	err = setup_compute_kernel(compute);
	if (err != CL_SUCCESS)
		error_julia(err,"Failed to setup compute kernel! Error");
	err = create_compute_result(texture, compute);
	if (err != CL_SUCCESS)
		error_julia(err, "Failed to create compute result! Error");
	random_color(color->color_a);
	random_color(color->color_b);
	random_color(color->color_c);
	return CL_SUCCESS;
}

void	init_julia_color(t_julia_color *color)
{
	color->mut = 0.0f;
	setup_color(color->mua, -.278f, -.479f, 0.0f, 0.0f);
	setup_color(color->mub, 0.278f, 0.479f, 0.0f, 0.0f);
	setup_color(color->muc, -.278f, -.479f, -.231f, .235f);
	color->epsilon = 0.003f;
	color->color_t = 0.0f;
	setup_color(color->color_a, 0.25f, 0.45f, 1.0f, 1.0f);
	setup_color(color->color_b, 0.25f, 0.45f, 1.0f, 1.0f);
	setup_color(color->color_c, 0.25f, 0.45f, 1.0f, 1.0f);
}

void	init_texture_cl(t_texture2 *texture)
{
	texture->id = 0;
	texture->target = GL_TEXTURE_2D;
	texture->format = GL_RGBA;
	texture->type	= GL_UNSIGNED_BYTE;
	texture->internal = GL_RGBA;
	texture->type_size = sizeof(char);
	texture->active_uint = 0x84C1;
	texture->host_image_buffer = 0;
}

void	init_compute_cl(t_compute *compute)
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
