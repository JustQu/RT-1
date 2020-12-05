/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:18:45 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/04 12:52:08 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app.h"
#include <stdio.h>
#include "libft.h"

#define BANANA 1
#define printf(...) if (BANANA) printf(__VA_ARGS__);

FILE *f;

// #include <windows.h>
#include "rt_types.h"

// #define _CRTDBG_MAP_ALLOC
// #include <stdlib.h>
// #include <crtdbg.h>

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
	SDL_RenderClear(w->renderer);
	SDL_UpdateTexture(w->texture, NULL, w->image, sizeof(uint32_t) * IMG_WIDTH);
	SDL_RenderCopy(w->renderer, w->texture, NULL, NULL);
	// SDL_RenderPresent(w->renderer);
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
	clSetKernelArg(app.rt.ocl_program.help_kernel, 2, sizeof(cl_float), &app.rt.options.spp);
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

#include "app.h"

/**
** @todo: -s 'scene_file_name';
** 		  --client;
** 		  --server 'ip';
** 		  --img 'img_name' -N (колво сэмплов);
** 		  --gui(by default)
**		  --log "file_name" - логирование
** @brief
**
** @param app
** @param ac
** @param av
** @return ** void
*/
void	read_av(t_app *app, int ac, char **av)
{
	for (int i = 1; i < ac; i++)
	{
		if (av[i][0] == '-')
		{
			if (strcmp(av[i], "--img"))
			{

			}
		}
	}
}

int main(int ac, char **av)
{
	t_app		app;
	int			value;
	t_all_rect	all_rect;
	t_colors	color;
	t_rt		rt;

	f = fopen("ocl.cl", "w+");
	init_colors(&color);
	init_app(&app, ac, av);
	init_rect(&all_rect, &app.window);
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
			main_loop(app);
			display_image(&app.window);
			save_image_func(&app.window);
			app.rt.options.spp += NUM_SAMPLES;
			app.rt.options.reset = 0;
			gui(&app.window, &app.rt, &all_rect, &color);
			SDL_RenderPresent(app.window.renderer);
		}
		// else
		// {
		// 	gui(&app.window, &app.rt, &all_rect, &color);
		// 	SDL_RenderPresent(app.window.renderer);
		// }
	}

	// exit_program(app.window);
	// fprintf(stdout, "AAA: %d\n",_CrtDumpMemoryLeaks());

	return (0);
}
