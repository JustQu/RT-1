/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 13:10:39 by maximka           #+#    #+#             */
/*   Updated: 2020/07/27 20:29:45 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/**
** @brief
** print log about opencl build fail
** @param program
** @param clp
** @param code
** @return ** void
*/
void cl_error(t_cl_program *program, t_clp *clp, int code)
{
	if (code != CL_SUCCESS)
	{
		printf("%d:", code);
		// Determine the size of the log
		size_t log_size;
		clGetProgramBuildInfo(program->program, clp->de_id, CL_PROGRAM_BUILD_LOG, 0,
							  NULL, &log_size);

		// Allocate memory for the log
		char *log;
		log = (char *)malloc(log_size);
		if (!log)
		{
			ft_putendl("malloc error");
			// exit (0);
		}
		// Get the log
		clGetProgramBuildInfo(program->program, clp->de_id, CL_PROGRAM_BUILD_LOG,
							  log_size, log, NULL);

		// Print the log
		printf("log:%s\n", log);
	}
}

int		init(t_clp *clp, t_window *window, t_cl_program *program)
{
	//opencl```````
	clp->pl_id = NULL;
	clp->de_id = NULL;
	clp->ret = clGetPlatformIDs(1, &(clp->pl_id), NULL);
	assert(!clp->ret);
	clp->ret = clGetDeviceIDs(clp->pl_id, CL_DEVICE_TYPE_ALL, 1, &(clp->de_id), &(clp->ret_num_devices));
	assert(!clp->ret);
	clp->context = clCreateContext(NULL, 1, &(clp->de_id), NULL, NULL, &(clp->ret));
	assert(!clp->ret);
	clp->queue = clCreateCommandQueue(clp->context, clp->de_id, 0, &(clp->ret));
	assert(!clp->ret);

	//sdl
	SDL_Init(SDL_INIT_VIDEO);
	window->ptr = SDL_CreateWindow("RT", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 600, 0);
	assert(window->ptr);
	window->renderer = SDL_CreateRenderer(window->ptr, -1, SDL_RENDERER_ACCELERATED);
	assert(window->renderer);
	window->texture = SDL_CreateTexture(window->renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, 1200, 600);
	assert(window->texture);
	window->image = malloc(sizeof(uint32_t) * 1200 * 600);
	ft_memset(window->image, 0, sizeof(uint32_t) * 1200 * 600);

	int	ret;
	program->image = clCreateBuffer(clp->context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(int) * 1200 * 600, window->image, &ret);
	assert(!ret);
	program->program = create_program(clp->context);
	ret = clBuildProgram(program->program, 1, &clp->de_id, NULL, NULL, NULL);
	cl_error(program, clp, ret);

	assert(!ret);
	program->kernel = clCreateKernel(program->program, "main_kernel", &ret);
	cl_error(program, clp, ret);
	assert(!ret);
	return (0);
}

void	render(t_window *window, t_cl_program *program, t_clp *clp)
{
	int	ret;
	size_t global_work_size = 1200 * 600;
	size_t group_size = 128;
	ret = clSetKernelArg(program->kernel, 0, sizeof(cl_mem), &program->image);
	printf("%d\n", ret);
	assert(!ret);
	ret = clEnqueueNDRangeKernel(clp->queue, program->kernel, 1, NULL, &global_work_size, &group_size, 0, NULL, NULL);
	printf("%d\n", ret);
	assert(!ret);
	ret = clEnqueueReadBuffer(clp->queue, program->image, CL_TRUE, 0, sizeof(int) * 1200 * 600, window->image, 0, NULL, NULL);
	assert(!ret);

	ret = SDL_UpdateTexture(window->texture, NULL, window->image, sizeof(int) * 1200);
	assert(!ret);
	SDL_RenderClear(window->renderer);
	SDL_RenderCopy(window->renderer, window->texture, NULL, NULL);
	SDL_RenderPresent(window->renderer);
}

#include "windows.h"
int		main(int argc, char **argv)
{
	t_obj			obj;
	t_clp			clp;
	t_window		window;
	t_cl_program	program;
	// t_matrix		matrix;
	int i;

	// /*Object*/
	// obj.origin.s[0] = 0;
	// obj.origin.s[1] = 0;
	// obj.origin.s[2] = 0;
	// obj.rotate.s[0] = 0;
	// obj.rotate.s[1] = 0;
	// obj.rotate.s[2] = 0;
	// obj.scale.s[0] = 1;
	// obj.scale.s[1] = 1;
	// obj.scale.s[2] = 1;
	// /*************/
	// convert(&obj);
	// matrix = create_affin_matrix(obj);
    // print_matrix(matrix);

	init(&clp, &window, &program);
	render(&window, &program, &clp);
	while (1);
	return (0);
}
