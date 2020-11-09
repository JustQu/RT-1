/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qjulia.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 15:28:34 by user              #+#    #+#             */
/*   Updated: 2020/11/09 19:48:04 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "julia.h"
#include "gui.h"
#include "rt.h"

void				compute_build_program(int err, t_compute *compute)
{
	size_t			len;
	char			buffer[2048];

	if (err != CL_SUCCESS)
	{
		printf("Error: Failed to build program executable!\n");
		clGetProgramBuildInfo(compute->program, compute->device_id,
			CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, &len);
		printf("%s\n", buffer);
	}
}

int					setup_compute_kernel(t_compute *compute)
{
	int				err;
	char			*source;
	size_t			lenght;

	if (compute->kernel)
		clReleaseKernel(compute->kernel);
	compute->kernel = 0;
	if (compute->program)
		clReleaseProgram(compute->program);
	compute->program = 0;
	err = load_text_from_file(COMPUTE_KERNEL_FILENAME, &source, &lenght);
	setup_preprocessor(compute, source);
	err = clBuildProgram(compute->program, 0, NULL, NULL, NULL, NULL);
	compute_build_program(err, compute);
	compute->kernel = clCreateKernel(compute->program,
		COMPUTE_KERNEL_METHOD_NAME, &err);
	err = clGetKernelWorkGroupInfo(compute->kernel, compute->device_id,
			CL_KERNEL_WORK_GROUP_SIZE, sizeof(size_t),
			&compute->max_work_group_size, NULL);
	compute->work_group_size[0] = (compute->max_work_group_size > 1)
		? (compute->max_work_group_size
		/ compute->work_group_items) : compute->max_work_group_size;
	compute->work_group_size[1] = compute->max_work_group_size
		/ compute->work_group_size[0];
	return (CL_SUCCESS);
}

int					create_compute_result(t_texture2 *texture,
						t_compute *compute)
{
	int				err;

	err = 0;
	if (compute->image)
		clReleaseMemObject(compute->image);
	compute->image = 0;
	compute->image = clCreateFromGLTexture2D(compute->context,
		CL_MEM_WRITE_ONLY, texture->target, 0, texture->id, &err);
	if (!compute->image || err != CL_SUCCESS)
		printf("Failed to create OpenGL texture reference! %d\n", err);
	if (compute->result)
		clReleaseMemObject(compute->result);
	compute->result = 0;
	compute->result = clCreateBuffer(compute->context, CL_MEM_WRITE_ONLY,
		texture->type_size * 4 * J_WIDTH * J_HEIGHT, NULL, NULL);
	if (!compute->result)
		printf("Failed to create OpenCL array!\n");
	return (CL_SUCCESS);
}

void				qjulia_main_loop(t_compute *compute,
	t_texture2 *texture, t_julia_color *color, SDL_Window *win)
{
	SDL_Event		event;

	while (SDL_PollEvent(&event))
	{
		if ((event.type == SDL_QUIT ||
			event.key.keysym.sym == SDLK_ESCAPE)
			&& SDL_GetWindowID(win) == event.window.windowID)
		{
			exit(0);
		}
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_SPACE)
				compute->animated ^= 1;
		}
	}
}

void				main_qjulia(void)
{
	t_compute		compute;
	t_texture		texture;
	t_julia_color	color;
	SDL_Window		*window;
	int				loop;

	loop = 1;
	init_texture_cl(&texture);
	init_compute_cl(&compute);
	init_julia_color(&color);
	window = qjulia_sdl_init();
	if (init_cl(&texture, &compute, &color) == GL_NO_ERROR)
	{
		while (loop)
		{
			qjulia_main_loop(&compute, &texture, &color, &window);
			display(&texture, &compute, &color);
			SDL_GL_SwapWindow(window);
		}
		cleanup(&compute);
		SDL_DestroyWindow(window);
	}
}
