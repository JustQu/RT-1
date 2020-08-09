/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 17:43:55 by dmelessa          #+#    #+#             */
/*   Updated: 2020/08/06 20:51:08 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/**
** @brief
** get
**  opencl GPU device
** create opencl context and command queue
** @param clp
** @return ** int
*/
int init_cl(t_clp *clp)
{
	if (clp == NULL)
		return (1);
	clp->pl_id = NULL;
	clp->de_id = NULL;
	clp->ret = clGetPlatformIDs(1, &(clp->pl_id), NULL);
	ft_clerror(clp->ret);
	clp->ret = clGetDeviceIDs(clp->pl_id, CL_DEVICE_TYPE_ALL, 1, &(clp->de_id),
							  &(clp->ret_num_devices));
	assert(!clp->ret);
	clp->context = clCreateContext(NULL, 1, &(clp->de_id), NULL, NULL,
								   &(clp->ret));
	assert(!clp->ret);
	clp->queue = clCreateCommandQueue(clp->context, clp->de_id, 0, &(clp->ret));
	ft_clerror(clp->ret);
	return (0);
}

//NOTE: deal with case when there is no objects
//TODO: mem manager like sampler_manager but for scene
void init_buffers(t_cl_program *program, t_scene *scene,
				  t_sampler_manager *sampler_manager)
{
	int ret;
	int ro;
	cl_context cntx;

	ro = CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR;
	cntx = program->clp.context;
	program->rgb_image = clCreateBuffer(cntx, CL_MEM_READ_WRITE, sizeof(cl_float3) * program->work_size, NULL, &ret);
	cl_error(program, &program->clp, ret);
	program->output_image = clCreateBuffer(cntx, CL_MEM_READ_WRITE,
										   sizeof(uint32_t) * program->work_size, NULL, &ret);
	cl_error(program, &program->clp, ret);

	program->instances = clCreateBuffer(cntx, ro, sizeof(t_instance) *
		scene->instance_manager.ninstances, scene->instance_manager.instances,
		&ret);
	cl_error(program, &program->clp, ret);

	program->objects = clCreateBuffer(cntx, ro,
		sizeof(t_obj) * scene->instance_manager.object_manager.nobjects,
		scene->instance_manager.object_manager.objects, &ret);
	cl_error(program, &program->clp, ret);

	program->triangles = clCreateBuffer(cntx, ro,
		sizeof(t_triangle) * (scene->instance_manager.object_manager.ntriangles + 1),
		scene->instance_manager.object_manager.triangles, &ret);
	cl_error(program, &program->clp, ret);

	program->matrices = clCreateBuffer(cntx, ro,
		sizeof(t_matrix) * scene->instance_manager.matrix_manager.nmatrices,
		scene->instance_manager.matrix_manager.matrices, &ret);
	cl_error(program, &program->clp, ret);

	program->lights = clCreateBuffer(cntx, ro, sizeof(t_light) * scene->nlights, scene->lights, &ret);
	cl_error(program, &program->clp, ret);

	program->samplers = clCreateBuffer(cntx, ro, sizeof(t_sampler) * sampler_manager->count, sampler_manager->samplers, &ret);
	cl_error(program, &program->clp, ret);

	program->samples = clCreateBuffer(cntx, ro, sizeof(cl_float2) * sampler_manager->samples_size, sampler_manager->samples, &ret);
	cl_error(program, &program->clp, ret);

	program->disk_samples = clCreateBuffer(cntx, ro, sizeof(cl_float2) * sampler_manager->samples_size, sampler_manager->disk_samples, &ret);
	cl_error(program, &program->clp, ret);

	program->hemisphere_samples = clCreateBuffer(cntx, ro, sizeof(cl_float3) * sampler_manager->samples_size, sampler_manager->hemisphere_samples, &ret);

	cl_error(program, &program->clp, ret);
}

void init_options(t_render_options *options, t_sampler_manager *sampler_manager)
{
	options->shadows = TRUE;
	options->ambient_occlusion = TRUE;
	options->area_lightning = FALSE;
	// options->backgorund_color.value = 0x000000af;
	options->background_color.value = 0x000505af;
	options->depth = 5;
	options->sampler_id = new_sampler(sampler_manager, rand_jitter, NUM_SAMPLES, DEFAULT_SAMPLES); //Anti-aliasing
}

/**
** @brief
** allocate memory for buffers
** compile opencl program
** @param cl_program
** @return ** int
*/
int init_kernel(t_cl_program *program, t_scene *scene, t_sampler_manager *sampler_manager)
{
	int ret = 0;


	program->program = create_program(program->clp.context);
	/* build kernel program */
	ret = clBuildProgram(program->program, 1, &program->clp.de_id,
						 DEFAULT_KERNEL_INCLUDE, NULL, NULL);
	cl_error(program, &program->clp, ret);
	/* create kernel */
	program->new_kernel = clCreateKernel(program->program, DEFAULT_KERNEL_NAME,
									 &ret);
	cl_error(program, &program->clp, ret);
	// program->kernel = clCreateKernel(program->program, "del", &ret);
	cl_error(program, &program->clp, ret);
	program->help_kernel = clCreateKernel(program->program, "translate_image", &ret);
	cl_error(program, &program->clp, ret);
	ft_clerror(program->clp.ret);

	/*init buffers for kernel*/
	init_buffers(program, scene, sampler_manager);
	cl_error(program, &program->clp, ret);
	return (0);
}

/**
** @brief
** default initialization
** @param window
** @param cl_program
** @return ** int
*/
int init_rt(t_rt *rt, char *scene_file)
{
	init_cl(&rt->program.clp);
	init_sampler_manager(&rt->sampler_manager);
	init_window(&rt->window);
	rt->program.work_size = DEFAULT_WORK_SIZE;
	rt->program.work_group_size = WORK_GROUP_SIZE;
	init_options(&rt->options, &rt->sampler_manager);
	// init_sampler(&rt->sampler);
	read_data(&rt->scene, &rt->sampler_manager, scene_file); //split to init default scene and read file
	init_kernel(&rt->program, &rt->scene, &rt->sampler_manager);

	rt->options.ambient_occluder_sampler = rt->sampler_manager.samplers[rt->scene.ambient_occluder.sampler_id];
	return (0);
}
