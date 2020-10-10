/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:18:45 by dmelessa          #+#    #+#             */
/*   Updated: 2020/10/10 14:54:50 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "gui.h"
#include "app.h"
#include "julia.h"
// #include "app.h"
#include <stdio.h>
#include "libft.h"



SDL_Rect	init_rect_size(int x, int y, int w, int h)
{
	SDL_Rect rect;

	rect.x = x;
	rect.y = y;
	rect.h = h;
	rect.w = w;
	return (rect);
}

void	init_rect(t_all_rect *rect, t_window *win)
{
	 rect->color_picker_button = init_rect_size(WIDTH_OFFSET + MARGIN,
		(FONT_TITLE_SIZE + MARGIN_Y) * 9 + MARGIN_Y * 6 + HEIGHT_BUTTON,
		rect->color_picker_button.x + 70,
		rect->color_picker_button.y + HEIGHT_BUTTON);

	rect->background = init_rect_size(win->width - 300, 0, WIDTH_MENU, HEIGHT);

	rect->color_picker = init_rect_size(WIDTH_OFFSET + MARGIN, 500, WIDTH_MENU - MARGIN * 2, 200);

	rect->checkbox_button_shadow = init_rect_size(WIDTH_OFFSET + WIDTH_MENU / 1.4 - HEIGHT_BUTTON - MARGIN,
										(FONT_TITLE_SIZE + MARGIN_Y) * 4 + MARGIN_Y,
										WIDTH_OFFSET + WIDTH_MENU / 1.4 - HEIGHT_BUTTON - MARGIN + HEIGHT_BUTTON,
										(FONT_TITLE_SIZE + MARGIN_Y) * 4 + MARGIN_Y + HEIGHT_BUTTON);

	rect->checkbox_button_ambient = init_rect_size(WIDTH - MARGIN - HEIGHT_BUTTON,
		(FONT_TITLE_SIZE + MARGIN_Y) * 4 + MARGIN_Y, WIDTH - MARGIN - HEIGHT_BUTTON + HEIGHT_BUTTON,
		(FONT_TITLE_SIZE + MARGIN_Y) * 4 + MARGIN_Y + HEIGHT_BUTTON);

	rect->specular_button_10 = init_rect_size(WIDTH - MARGIN - HEIGHT_BUTTON, ((FONT_TITLE_SIZE + MARGIN_Y) * 4 + MARGIN_Y) * 2 + MARGIN_Y * 6,
		WIDTH - MARGIN - HEIGHT_BUTTON + HEIGHT_BUTTON, ((FONT_TITLE_SIZE + MARGIN_Y) * 4 + MARGIN_Y) * 2 + MARGIN_Y * 6 + HEIGHT_BUTTON);

	rect->tab_camera_button = init_rect_size(win->width - win->width / 4,
		win->height / 7, (win->width / 4) / 3, 30);

	rect->tab_objects_button = init_rect_size(win->width - win->width / 4 + rect->tab_camera_button.w,
		win->height / 7, (win->width / 4) / 3, 30);

	rect->tab_options_button = init_rect_size(win->width - win->width / 4 + rect->tab_camera_button.w + rect->tab_objects_button.w,
		win->height / 7, (win->width / 4) / 3, 30);

	rect->fractol_button = init_rect_size(WIDTH_OFFSET + MARGIN, (FONT_TITLE_SIZE + MARGIN_Y) * 9 + MARGIN_Y * 4 + HEIGHT_BUTTON * 2,
		WIDTH - MARGIN, (FONT_TITLE_SIZE + MARGIN_Y) * 9 + MARGIN_Y * 4 + HEIGHT_BUTTON * 3);
}

void	init_colors(t_colors *color)
{
	color->preground.r = 255;
	color->preground.g = 255;
	color->preground.b = 255;
	color->preground.a = 0;

	color->title_text_color.r = 0;
	color->title_text_color.g = 0;
	color->title_text_color.b = 0;
	color->title_text_color.a = 0;

	color->border_color.r = 217;
	color->border_color.g = 217;
	color->border_color.b = 217;
	color->border_color.a = 0;

	color->subtitle_xyz_color.r = 36;
	color->subtitle_xyz_color.g = 36;
	color->subtitle_xyz_color.b = 36;
	color->subtitle_xyz_color.a = 0;

	color->xyz_text_color.r = 100;
	color->xyz_text_color.g = 100;
	color->xyz_text_color.b = 100;
	color->xyz_text_color.a = 0;

	color->background_color.r = 242;
	color->background_color.g = 242;
	color->background_color.b = 242;
	color->background_color.a = 0;

	color->tab_pressed_color.r = 106;
	color->tab_pressed_color.g = 30;
	color->tab_pressed_color.b = 239;
	color->tab_pressed_color.a = 0;

	color->green_color.r = 0;
	color->green_color.g = 255;
	color->green_color.b = 0;
	color->green_color.a = 0;
}

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

// void	init_gui(t_window *win)
// {
// 	if (!(win->texture = SDL_CreateTexture(win->renderer,
// 		SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING,
// 		WIDTH_MENU, DEFAULT_HEIGHT)))
// 	{
// 		SDL_DestroyWindow(win->ptr);
// 		// quit("SDL_CreateTexture Error");
// 	}
// 	win->image = (uint32_t *)malloc(sizeof(uint32_t) *
// 				WIDTH_MENU * DEFAULT_HEIGHT);
// 	ft_memset(win->image, 0, sizeof(uint32_t) * WIDTH_MENU * DEFAULT_HEIGHT);
// 	if (!win->image)
// 		perror("win->image malloc");
// 	win->rgb_image = (t_color *)malloc(sizeof(t_color) * WIDTH_MENU * DEFAULT_HEIGHT);
// 	ft_memset(win->rgb_image, 0, sizeof(t_color) * WIDTH_MENU * DEFAULT_HEIGHT);
// }

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

	//init rt
	// rt.direction.x = 1.23;
	// rt.direction.y = 1.02;
	// rt.direction.z = 2.093432;
	// rt.center.x = 0.23;
	// rt.center.y = 1.22;
	// rt.center.z = 5.393432;
	// rt.rotate.x = 30;
	// rt.rotate.y = 45;
	// rt.rotate.z = 90;
	// rt.is_pressed.shadow = 1;
	// rt.is_pressed.and_more = 0;
	// rt.is_pressed.specular = 0;
	// rt.is_pressed.ambient = 1;
	// rt.is_pressed.render_tab = 0;
	// rt.is_pressed.main_tab = 0;
	// 	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	// 	printf("Error");
	// IMG_Init(IMG_INIT_PNG);
	// window_gui.ptr = SDL_CreateWindow("Menu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	// if (window_gui.ptr == NULL)
	// 	printf("Error");
	// window_gui.renderer = SDL_CreateRenderer(window_gui.ptr, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	// if (window_gui.renderer == NULL)
	// 	printf("Error");
	// SDL_SetRenderDrawColor(window_gui.renderer, 255, 255, 255, 255);
	// SDL_RenderClear(window_gui.renderer);
	// main_gui(&window_gui, &rt, &all_rect, &color);

	SDL_Quit();
	return (0);
}
