/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:18:45 by dmelessa          #+#    #+#             */
/*   Updated: 2020/09/23 23:52:19 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "rt.h"

#define BANANA 0
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
	SDL_RenderPresent(w->renderer);
}

void	write_buffers(t_rt rt)
{
	clEnqueueWriteBuffer(rt.program.clp.queue, rt.program.samplers,
		CL_FALSE, 0, sizeof(t_sampler) * rt.sampler_manager.count,
		rt.sampler_manager.samplers, 0, 0, 0);
}

/**
** @brief Очистка памяти
** todo: память очищается не полностью
** @param rt
** @return ** void
*/
void cleanup(t_rt rt)
{
	clReleaseMemObject(rt.program.disk_samples);
	clReleaseMemObject(rt.program.samplers);
	clReleaseMemObject(rt.program.hemisphere_samples);
	clReleaseMemObject(rt.program.samples);
	clReleaseMemObject(rt.program.lights);
	clReleaseMemObject(rt.program.objects);
	clReleaseMemObject(rt.program.output_image);
	clReleaseMemObject(rt.program.triangles);
	clReleaseKernel(rt.program.help_kernel);
	clReleaseKernel(rt.program.new_kernel);
	// clReleaseKernel(rt.program.kernel);
	clReleaseProgram(rt.program.program);
	clReleaseCommandQueue(rt.program.clp.queue);
	clReleaseContext(rt.program.clp.context);
	free(rt.scene.lights);
	free(rt.window.image);
}

void	set_new_kernel_args(t_rt rt, int step)
{
	printf("Pass arguments to kernel\n");
	cl_kernel k;
	int err_code;
	k = rt.program.new_kernel;
	err_code = 0;
	err_code |= clSetKernelArg(k, 0, sizeof(cl_mem), &rt.program.rgb_image);
	err_code |= clSetKernelArg(k, 1, sizeof(cl_int), &step);

	err_code |= clSetKernelArg(k, 2, sizeof(cl_mem), &rt.program.instances);
	err_code |= clSetKernelArg(k, 3, sizeof(cl_int),
		&rt.scene.instance_mngr.ninstances);

	err_code |= clSetKernelArg(k, 4, sizeof(cl_mem), &rt.program.objects);
	err_code |= clSetKernelArg(k, 5, sizeof(cl_int),
		&rt.scene.instance_mngr.nobjects);

	err_code |= clSetKernelArg(k, 6, sizeof(cl_mem), &rt.program.triangles);
	err_code |= clSetKernelArg(k, 7, sizeof(cl_int),
		&rt.scene.instance_mngr.ntriangles);

	err_code |= clSetKernelArg(k, 8, sizeof(cl_mem), &rt.program.matrices);
	err_code |= clSetKernelArg(k, 9, sizeof(cl_int),
		&rt.scene.instance_mngr.nmatrices);

	err_code |= clSetKernelArg(k, 10, sizeof(cl_mem), &rt.program.lights);
	err_code |= clSetKernelArg(k, 11, sizeof(cl_int), &rt.scene.nlights);

	err_code |= clSetKernelArg(k, 12, sizeof(t_camera), &rt.scene.camera);
	err_code |= clSetKernelArg(k, 13, sizeof(t_light), &rt.scene.ambient_light);

	err_code |= clSetKernelArg(k, 14, sizeof(t_ambient_occluder), &rt.scene.ambient_occluder);

	err_code |= clSetKernelArg(k, 15, sizeof(cl_mem), &rt.program.bvh);

	err_code |= clSetKernelArg(k, 16, sizeof(t_render_options), &rt.options);

	err_code |= clSetKernelArg(k, 17, sizeof(cl_mem), &rt.program.samplers);
	err_code |= clSetKernelArg(k, 18, sizeof(cl_mem), &rt.program.samples);
	err_code |= clSetKernelArg(k, 19, sizeof(cl_mem), &rt.program.disk_samples);
	err_code |= clSetKernelArg(k, 20, sizeof(cl_mem), &rt.program.hemisphere_samples);
	cl_error(&rt.program, &rt.program.clp, err_code);
	assert(!err_code);
}

#include "time.h"

void	render_cycle(t_rt rt)
{
	printf("Start render cycle\n");
	int		err_code;

	err_code = 0;
	clEnqueueWriteBuffer(rt.program.clp.queue, rt.program.samplers,
						 CL_TRUE, 0, sizeof(t_obj) * rt.scene.instance_mngr.nobjects,
						 rt.scene.instance_mngr.objects, 0, 0, 0);

	for (int i = 0; i < NUM_SAMPLES; i++)
	{
		printf("Start %d kernel\n", i + 1);

		set_new_kernel_args(rt, i);

		err_code = clEnqueueNDRangeKernel(rt.program.clp.queue,
			rt.program.new_kernel, 1, NULL, &rt.program.work_size,
			&rt.program.work_group_size, 0, NULL, NULL);

		assert(!err_code);
		cl_error(&rt.program, &rt.program.clp, err_code);
		printf("\n");
	}
	printf("Translate image format\n");
	int	a = NUM_SAMPLES;
	clSetKernelArg(rt.program.help_kernel, 0, sizeof(cl_mem), &rt.program.rgb_image);
	clSetKernelArg(rt.program.help_kernel, 1, sizeof(cl_mem), &rt.program.output_image);
	clSetKernelArg(rt.program.help_kernel, 2, sizeof(cl_int), &a);
	err_code = clEnqueueNDRangeKernel(rt.program.clp.queue,
		rt.program.help_kernel, 1, NULL, &rt.program.work_size,
		&rt.program.work_group_size, 0, NULL, NULL);
	assert(!err_code);
	err_code = clEnqueueReadBuffer(rt.program.clp.queue,
		rt.program.output_image, CL_TRUE, 0,
		rt.program.work_size * sizeof(uint32_t), rt.window.image,
		0, NULL, NULL);
	cl_error(&rt.program, &rt.program.clp, err_code);
	assert(!err_code);
}

#include "stdlib.h"
#include "time.h"

int main(int ac, char **av)
{
	printf("Start program\n");

	t_rt	rt;
	int		value;

	fprintf(stdout, "%d\n", CL_DEVICE_MAX_WORK_GROUP_SIZE);
	f = fopen("ocl.cl", "w+");
	if (f == NULL)
	{
		printf("ERROR");
		exit(0);
	}
	ac == 1 ? init_rt(&rt, NULL) : init_rt(&rt, av[1]);

	cl_device_local_mem_type mem_type;

	clGetDeviceInfo(rt.program.clp.de_id,
					CL_DEVICE_LOCAL_MEM_TYPE,
					sizeof(cl_device_local_mem_type),
					&mem_type,
					NULL);

	fprintf(stdout, "%d %d %d\n", CL_LOCAL, CL_GLOBAL, CL_NONE );

	fprintf(stdout, "%d\n", mem_type);

	cl_ulong mem_size;

	clGetDeviceInfo(rt.program.clp.de_id,
					CL_DEVICE_LOCAL_MEM_SIZE,
					sizeof(cl_ulong),
					&mem_size,
					NULL);

	fprintf(stdout, "%d\n", mem_size);

	while (1)
	{
		value = catch_event(&rt);
		if (value == 1)
			break;
		else if (value == 0)
		{
			printf("CPU:\nobj %zd\n", sizeof(t_obj));
			printf("instance %zd\n", sizeof(t_instance));
			printf("matrix %zd\n", sizeof(t_matrix));
			printf("material %zd\n", sizeof(t_material));
			printf("triangle %zd\n", sizeof(t_triangle));
			render_cycle(rt);
			display_image(&rt.window);
		}
	}
	cleanup(rt);
	exit_program(rt.window);
	return (0);
}
