/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qjulia_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 16:05:53 by user              #+#    #+#             */
/*   Updated: 2020/09/10 16:26:09 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "julia.h"

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

void	init_texture_cl(t_texture *texture)
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
