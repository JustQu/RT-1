/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qjulia_display.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 18:46:20 by alex              #+#    #+#             */
/*   Updated: 2020/11/09 18:51:12 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "julia.h"

void		setup_preprocessor(t_compute *compute, char *source)
{
	char	*preprocess;
	int		err;

	preprocess = (char*)malloc(strlen(source) + 1024);
	sprintf(preprocess, "\n%s (%d)\n%s (%d)\n%s", "#define J_WIDTH",
		J_WIDTH, "#define J_HEIGHT", J_HEIGHT, source);
	compute->program = clCreateProgramWithSource(compute->context, 1,
		(const char **)&preprocess, NULL, &err);
	if (!compute->program || err != CL_SUCCESS)
		printf("Error: Failed to create compute program!\n");
	free(source);
	free(preprocess);
}

int			recompute(t_compute *compute, t_julia_color *color)
{
	size_t	global[2];
	size_t	local[2];
	int		err;

	if (!compute->kernel || !compute->result)
		return (CL_SUCCESS);
	err = 0;
	ft_values(compute, color);
	global[0] = divide_up(J_WIDTH, compute->work_group_size[0])
		* compute->work_group_size[0];
	global[1] = divide_up(J_HEIGHT, compute->work_group_size[1])
		* compute->work_group_size[1];
	local[0] = compute->work_group_size[0];
	local[1] = compute->work_group_size[1];
	err = clEnqueueNDRangeKernel(compute->commands, compute->kernel, 2,
		NULL, global, local, 0, NULL, NULL);
	if (err)
		printf("Failed to enqueue kernel! %d\n", err);
	err = clEnqueueAcquireGLObjects(compute->commands, 1,
		&compute->image, 0, 0, 0);
	if (err != CL_SUCCESS)
		printf("Failed to acquire GL object! %d\n", err);
	origin_region(compute);
	return (CL_SUCCESS);
}

void		display(t_texture2 *texture, t_compute *compute,
				t_julia_color *color)
{
	int		err;

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	if (compute->animated)
	{
		update_mu(&color->mut, color->mua, color->mub);
		interpolate(color->muc, color->mut, color->mua, color->mub);
		update_color(&color->color_t, color->color_a, color->color_b);
		interpolate(color->color_c, color->color_t,
			color->color_a, color->color_b);
	}
	err = recompute(compute, color);
	if (err != 0)
		printf("Error %d from Recompute!\n", err);
	qjulia_render_texture(texture);
	glFinish();
}

void		qjulia_render_texture(t_texture2 *texture)
{
	gl_render_init(texture);
	if (texture->host_image_buffer)
		glTexSubImage2D(texture->target, 0, 0, 0, J_WIDTH,
		J_HEIGHT, texture->format, texture->type, texture->host_image_buffer);
	glTexParameteri(texture->target, GL_TEXTURE_COMPARE_MODE, GL_NONE);
	glBegin(GL_QUADS);
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 0.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, 0.0f);
	}
	glEnd();
	glBindTexture(texture->target, 0);
	glDisable(texture->target);
}
