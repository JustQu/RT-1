/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:18:45 by dmelessa          #+#    #+#             */
/*   Updated: 2020/10/15 13:39:58 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "gui.h"
#include "app.h"
#include "julia.h"
// #include "app.h"
#include <stdio.h>
#include "libft.h"



#define BANANA 1
#define printf(...) if (BANANA) printf(__VA_ARGS__);

FILE *f;

/**
** L1 Cache = Local Memory(OpenCL) = Shared Memory(CUDA)
*/

void	print_vector(cl_float4 vec)
{
	printf("(%.1f, %.1f, %.1f)", vec.x, vec.y, vec.z);
}


void	exit_program(t_window window)
{
/*
    err = clFlush(command_queue);
    err = clFinish(command_queue);
    err = clReleaseKernel(kernel);
    err = clReleaseProgram(program);
    err = clReleaseMemObject(img_cl);
    err = clReleaseMemObject(obj_cl);
    err = clReleaseCommandQueue(command_queue);
    err = clReleaseContext(context);*/
	SDL_DestroyTexture(window.texture);
	SDL_DestroyRenderer(window.renderer);
	SDL_DestroyWindow(window.ptr);
	SDL_Quit();
}

/**
** @brief
** dispay image in window w
** @param w
** @return ** void
*/
void	display_image(t_window *w)
{
	SDL_UpdateTexture(w->texture, NULL, w->image, sizeof(uint32_t) * w->width);
	SDL_RenderClear(w->renderer);
	SDL_RenderCopy(w->renderer, w->texture, NULL, NULL);
	// SDL_RenderPresent(w->renderer);
}

void	write_buffers(t_rt rt)
{
	clEnqueueWriteBuffer(rt.ocl_program.info.queue, rt.ocl_program.samplers,
		CL_FALSE, 0, sizeof(t_sampler) * rt.sampler_manager.count,
		rt.sampler_manager.samplers, 0, 0, 0);
}

/**
** @brief Очистка памяти
** todo: память очищается не полностью
** @param rt
** @return ** void
*/
// void cleanup(t_rt rt)
// {
// 	clReleaseMemObject(rt.program.disk_samples);
// 	clReleaseMemObject(rt.program.samplers);
// 	clReleaseMemObject(rt.program.hemisphere_samples);
// 	clReleaseMemObject(rt.program.samples);
// 	clReleaseMemObject(rt.program.lights);
// 	clReleaseMemObject(rt.program.objects);
// 	clReleaseMemObject(rt.program.output_image);
// 	clReleaseMemObject(rt.program.triangles);
// 	clReleaseKernel(rt.program.help_kernel);
// 	clReleaseKernel(rt.program.new_kernel);
// 	// clReleaseKernel(rt.program.kernel);
// 	clReleaseProgram(rt.program.program);
// 	clReleaseCommandQueue(rt.program.info.queue);
// 	clReleaseContext(rt.program.info.context);
// 	free(rt.scene.lights);
// 	free(rt.window.image);
// }

#include "time.h"

void	main_loop(t_app app)
{
	int		err_code;

	err_code = 0;
	render_scene(app.rt);
	int	a = NUM_SAMPLES;
	clSetKernelArg(app.rt.ocl_program.help_kernel, 0, sizeof(cl_mem), &app.rt.ocl_program.rgb_image);
	clSetKernelArg(app.rt.ocl_program.help_kernel, 1, sizeof(cl_mem), &app.rt.ocl_program.output_image);
	clSetKernelArg(app.rt.ocl_program.help_kernel, 2, sizeof(cl_int), &a);
	err_code = clEnqueueNDRangeKernel(app.rt.ocl_program.info.queue,
		app.rt.ocl_program.help_kernel, 1, NULL, &app.rt.ocl_program.work_size,
		&app.rt.ocl_program.work_group_size, 0, NULL, NULL);
	assert(!err_code);
	err_code = clEnqueueReadBuffer(app.rt.ocl_program.info.queue,
		app.rt.ocl_program.output_image, CL_TRUE, 0,
		app.rt.ocl_program.work_size * sizeof(uint32_t), app.window.image,
		0, NULL, NULL);
	cl_error(&app.rt.ocl_program, &app.rt.ocl_program.info, err_code);
	assert(!err_code);
}

#include <stdlib.h>
#include <time.h>

int main(int ac, char **av)
{
	t_app	app;
	int		value;
	t_window	window_gui;
	t_all_rect all_rect;
	t_colors color;
	t_rt rt;


	init_colors(&color);
	init_app(&app, ac, av);
	init_rect(&all_rect, &app.window);
	f = fopen("ocl.cl", "w+");
	if (f == NULL)
	{
		printf("ERROR");
		exit(0);
	}
	while (1)
	{
		value = catch_event(&app.rt, &app.window, &all_rect, &color);
		if (value == 1)
			break;
		else if (value == 0)
		{
			// printf("CPU:\nobj %zd\n", sizeof(t_obj));
			// printf("instance %zd\n", sizeof(t_instance));
			// printf("matrix %zd\n", sizeof(t_matrix));
			// printf("material %zd\n", sizeof(t_material));
			// printf("triangle %zd\n", sizeof(t_triangle));
			// main_loop(app);
			display_image(&app.window);
			main_gui(&app.window, &rt, &all_rect, &color);
			SDL_RenderPresent(app.window.renderer);
		}
	}
	// cleanup(app.rt);

	exit_program(app.window);

	SDL_Quit();
	return (0);
}
