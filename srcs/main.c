/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:18:45 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/15 22:02:03 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app.h"
#include <stdio.h>

#define BANANA 1
#define printf(...) if (BANANA) printf(__VA_ARGS__);

FILE *f;

// #include <windows.h>

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

/*
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

/*
** @brief
** dispay image in window w
** @param w
** @return ** void
*/

void	display_image(t_window *w, t_image *image)
{
	SDL_RenderClear(w->renderer);
	SDL_UpdateTexture(w->texture, NULL, image->pixels,
					sizeof(*image->pixels) * image->width);
	SDL_RenderCopy(w->renderer, w->texture, NULL, NULL);
}

#include "time.h"

void	render_image(t_app app)
{
	int		err_code;

	err_code = 0;
	render_scene(app.rt);
	// int	a = NUM_SAMPLES;
	err_code |= clSetKernelArg(app.rt.ocl_program.help_kernel, 0,
								sizeof(cl_mem), &app.rt.ocl_program.rgb_image);
	err_code |= clSetKernelArg(app.rt.ocl_program.help_kernel, 1,
							sizeof(cl_mem), &app.rt.ocl_program.output_image);
	err_code |= clSetKernelArg(app.rt.ocl_program.help_kernel, 2,
								sizeof(cl_float), &app.rt.options.spp);
	rt_is_dead(opencl_err, cl_kernel_arg_error, err_code, "main.c 1");
	err_code = clEnqueueNDRangeKernel(app.rt.ocl_program.info.queue,
		app.rt.ocl_program.help_kernel, 1, NULL, &app.rt.ocl_program.work_size,
		&app.rt.ocl_program.work_group_size, 0, NULL, NULL);
	rt_is_dead(opencl_err, cl_kernel_start_error, err_code, "main.c 2");
	err_code = clEnqueueReadBuffer(app.rt.ocl_program.info.queue,
		app.rt.ocl_program.output_image, CL_TRUE, 0,
		app.image.width * app.image.height * sizeof(uint32_t),
		app.image.pixels, 0, NULL, NULL);
	rt_is_dead(opencl_err, cl_read_buffer_error, err_code, "main.c 3");
}


/*
** @todo: -s 'scene_file_name';
** 		  --img 'img_name' -N (колво сэмплов);
** 		  -h
** 		  --cpu | --gpu
** 		  --resoulution 1920 1080
**		  --window 800 800

** 		  --client;
** 		  --server 'ip';
** 		  --gui(by default)
**		  --interface
** @brief
**
** @param app
** @param ac
** @param av
** @return ** void
*/

void	read_av(t_app *app, int ac, char **av)
{
	//
	app->options.render_device = CL_DEVICE_TYPE_DEFAULT;
	app->options.num_samples = NUM_SAMPLES;
	app->options.image_width = DEFAULT_IMAGE_WIDTH;
	app->options.image_height = DEFAULT_IMAGE_HEIGHT;
	app->options.window_width = DEFAULT_WIDTH;
	app->options.window_height = DEFAULT_HEIGHT;
	app->options.scene_file = NULL;
	app->options.enable_gui = TRUE;
	app->options.enable_logs = FALSE;
	app->options.mode = window_mode;
	//
	if (ac == 2)
	{
		app->options.scene_file = av[1];
	}
	else
		for (int i = 1; i < ac; i++)
		{
			if (av[i][0] == '-')
			{
				if (!strcmp(av[i], "-s"))
				{
					app->options.scene_file = av[i + 1];
					i++;
				}
				else if (!strcmp(av[i], "--gpu"))
				{
					app->options.render_device = CL_DEVICE_TYPE_GPU;
				}
				else if (!strcmp(av[i], "--cpu"))
				{
					app->options.render_device = CL_DEVICE_TYPE_CPU;
				}
				else if (!strcmp(av[i], "--resolution"))
				{
					app->options.image_width = ft_atoi(av[i + 1]);
					app->options.image_height = ft_atoi(av[i + 2]);
					app->options.window_width = ft_atoi(av[i + 1]);
					app->options.window_height = ft_atoi(av[i + 2]);
					i += 3;
				}
				else if (!strcmp(av[i], "-N"))
				{
					app->options.num_samples = ft_atoi(av[i + 1]);
					i += 2;
				}
				else if (!strcmp(av[i], "--img"))
				{
					app->options.image_file = av[i];
					i++;
				}
				else if (!strcmp(av[i], "--console"))
				{

				}
				else if (!strcmp(av[i], "-h"))
				{

				}
				else if (!strcmp(av[i], "--nudes"))
				{

				}
				else
				{
					ft_putendl_fd("Options error.", 1);
					//call usage
					exit(0);
				}
			}
		}
	rt_is_dead(app_err, app_no_scene_file, !app->options.scene_file, NULL);
}

#define exit_loop 1
#define render_state 0

void		display_info(t_interface *const interface,
						t_res_mngr *const mngr,
						t_window *const window)
{
	interface->current_instance = get_instance_info(mngr,
												interface->current_instance_id);
	interface->current_light = get_light_info(mngr, interface->current_light_id);
	interface->camera = mngr->scene->camera;
	interface->options = *mngr->rt_options;
	if (interface->mode == window_mode)
	{
		if (interface->enable_gui == TRUE)
		{
			interface->gui.current_instance = interface->current_instance;
			interface->gui.current_light = interface->current_light;
			interface->gui.camera = interface->camera;
			interface->gui.options = interface->options;
			gui(window, &interface->gui);
		}
	}
	else if (interface->mode == console)
	{
		;
	}
	else
	{
		;
	}
}

static void	window_render_loop(t_app *const app)
{
	int	state;

	state = 0;
	while (state != exit_loop)
	{
		state = catch_event(&app->rt, &app->window, &app->interface);
		if (state == render_state)
		{
			init_rect(&app->interface.gui.all_rect, &app->window);
			render_image(*app);
			display_image(&app->window, &app->image);
			app->rt.options.spp += 1;
			app->rt.options.reset = 0;
			save_image_func(&app->window, &app->image);
			display_info(&app->interface, &app->resource_manager,
						&app->window);
			// gui(&app->window, &app->rt, &app->gui.all_rect, &app->gui.colors);
			SDL_RenderPresent(app->window.renderer);
		}
	}
}

int			main(int ac, char **av)
{
	t_app		app;

	f = fopen("ocl.cl", "w+"); //todo: delete
	read_av(&app, ac, av);
	init_app(&app);
	window_render_loop(&app);
	// exit_program(app.window);

	// fprintf(stdout, "AAA: %d\n",_CrtDumpMemoryLeaks());

	return (0);
}
