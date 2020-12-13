/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_ocl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 18:59:58 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/13 13:24:14 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "rt_ocl.h"
#include "app.h"
#include "rt_error.h"
#include "image.h"

#include <assert.h>

static int	init_clp(t_clp *clp, cl_device_type dev_type)
{
	cl_platform_id	pl_id;
	cl_uint			nde;

	pl_id = NULL;
	clp->de_id = NULL;
	clp->ret = clGetPlatformIDs(1, &pl_id, NULL);
	rt_is_dead(opencl_err, cl_get_platform_id_error, clp->ret, "");
	clp->ret = clGetDeviceIDs(pl_id, dev_type, 1, &clp->de_id, &nde);
	rt_is_dead(opencl_err, cl_get_device_id_error, clp->ret, "");
	clp->context = clCreateContext(NULL, 1, &clp->de_id, NULL, NULL, &clp->ret);
	rt_is_dead(opencl_err, cl_create_context_error, clp->ret, "");
	clp->queue = clCreateCommandQueue(clp->context, clp->de_id, 0, &clp->ret);
	rt_is_dead(opencl_err, cl_create_command_queue_error, clp->ret, "");
	return (0);
}

void CL_CALLBACK pfn_notify(cl_program program, void *data)
{
	int	*state;

	state = data;
	printf("ready");
	*state = 1;
}

static int state = 0;


int		test_thread(void *ptr)
{
	t_cl_program *p;

	p = ptr;

	int r;
	r = clBuildProgram(p->program, 1, &p->info.de_id,
					   "-cl-std=CL2.0", pfn_notify, &state);
	return (r);
}


static int	init_kernel(t_cl_program *p, t_window *window, t_image *image)
{
	int		r;
	size_t	a;

	r = 0;
	p->work_size = image->width * image->height;
	p->work_group_size = WORK_GROUP_SIZE;
	p->program = create_program(p->info.context);

	SDL_Thread *thread;
	int threadReturnValue;

	SDL_Surface *sur = SDL_LoadBMP("image.bmp");
	if (sur == NULL)
		printf("sur bad");
	// SDL_Texture *tex = SDL_CreateTextureFromSurface(window->renderer, sur);
	// SDL_RenderClear(window->renderer);
	// SDL_UpdateTexture(tex, NULL, window->image, sizeof(uint32_t) * IMG_WIDTH);
	// SDL_RenderCopy(window->renderer, tex, NULL, NULL);
	// SDL_RenderPresent(window->renderer);

	printf("Simple SDL_CreateThread test:\n");

	/* Simply create a thread */
	thread = SDL_CreateThread(test_thread, "TestThread", (void *)p);

	if (NULL == thread)
	{
		printf("SDL_CreateThread failed: %s\n", SDL_GetError());
	}
	else
	{
		int j = 0;

		while (state != 1)
		{
			SDL_Event e;
			if (SDL_PollEvent(&e))
			{
				if (e.type == SDL_QUIT)
				{
					break;
				}
			}
			if (SDL_RenderCopy(window->renderer, window->texture, NULL, NULL)
				 == -1)
				printf("%s\n", SDL_GetError());

			SDL_RenderPresent(window->renderer);

			printf("%d\n", j++);
		}
		SDL_WaitThread(thread, &threadReturnValue);
		// SDL_FreeSurface(sur);
		printf("Thread returned value: %d\n", threadReturnValue);
	}

	rt_is_dead(opencl_err, cl_build_program_error, threadReturnValue, "");
	p->new_kernel = clCreateKernel(p->program, KERNEL_NAME, &r);
	rt_is_dead(opencl_err, cl_create_kernel_error, r, "");
	p->help_kernel = clCreateKernel(p->program, "translate_image", &r);
	rt_is_dead(opencl_err, cl_create_kernel_error, r, "");
	clGetKernelWorkGroupInfo(p->new_kernel, p->info.de_id,
						CL_KERNEL_WORK_GROUP_SIZE, sizeof(size_t), &a, NULL);
	fprintf(stdout, "Work group kernel - %zd\n", a);
	return (r);
}

/*
** @brief
** @todo: deal with  case when there is no objects
** @param program
** @param scene
** @param sampler_manager
** @param rt
** @return ** void
*/

void		init_buffers(t_cl_program *program, t_scene *scene,
						t_sampler_manager *sampler_manager)
{
	int			ret;
	int			ro;
	cl_context	cntx;

	ro = CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR;
	cntx = program->info.context;
	program->rgb_image = clCreateBuffer(cntx, CL_MEM_READ_WRITE,
							sizeof(t_color) * program->work_size, NULL, &ret);
	rt_is_dead(opencl_err, cl_create_buffer_error, ret, "");
	program->output_image = clCreateBuffer(cntx, CL_MEM_READ_WRITE,
							sizeof(uint32_t) * program->work_size, NULL, &ret);
	rt_is_dead(opencl_err, cl_create_buffer_error, ret, "");

	program->instances = clCreateBuffer(cntx, ro, sizeof(t_instance) *
		scene->instance_mngr.ninstances, scene->instance_mngr.instances, &ret);
	rt_is_dead(opencl_err, cl_create_buffer_error, ret, "");

	program->objects = clCreateBuffer(cntx, ro, sizeof(t_obj) *
	(scene->instance_mngr.nobjects + 1), scene->instance_mngr.objects, &ret);
	rt_is_dead(opencl_err, cl_create_buffer_error, ret, "");

	program->triangles = clCreateBuffer(cntx, ro, sizeof(t_triangle) * (scene->
	instance_mngr.ntriangles + 1), scene->instance_mngr.triangles, &ret);
	rt_is_dead(opencl_err, cl_create_buffer_error, ret, "");

	program->matrices = clCreateBuffer(cntx, ro, sizeof(t_matrix) *
		(scene->instance_mngr.nmatrices), scene->instance_mngr.matrices, &ret);
	rt_is_dead(opencl_err, cl_create_buffer_error, ret, "");

	program->bvh = clCreateBuffer(cntx, ro, sizeof(t_bvh_node) *
		(scene->instance_mngr.ninstances * 2), scene->bvh, &ret);
	rt_is_dead(opencl_err, cl_create_buffer_error, ret, "");

	program->lights = clCreateBuffer(cntx, ro, sizeof(t_light) *
		(scene->light_manager.nlights + 1), scene->light_manager.lights, &ret);
	rt_is_dead(opencl_err, cl_create_buffer_error, ret, "");

	program->samplers = clCreateBuffer(cntx, ro, sizeof(t_sampler) *
					sampler_manager->count, sampler_manager->samplers, &ret);
	rt_is_dead(opencl_err, cl_create_buffer_error, ret, "");

	program->samples = clCreateBuffer(cntx, ro, sampler_manager->samples_size,
										 sampler_manager->samples, &ret);
	rt_is_dead(opencl_err, cl_create_buffer_error, ret, "");

	program->disk_samples = clCreateBuffer(cntx, ro, sampler_manager->
		disk_samples_size, sampler_manager->disk_samples, &ret);
	rt_is_dead(opencl_err, cl_create_buffer_error, ret, "");

	program->hemisphere_samples = clCreateBuffer(cntx, ro, sampler_manager->
		hemisphere_samples_size, sampler_manager->hemisphere_samples, &ret);
	rt_is_dead(opencl_err, cl_create_buffer_error, ret, "");

	program->textures = clCreateBuffer(cntx, ro, sizeof(t_texture) *
		scene->instance_mngr.texture_manager.ntextures,
		scene->instance_mngr.texture_manager.textures, &ret);
	rt_is_dead(opencl_err, cl_create_buffer_error, ret, "");

	program->ranvec = clCreateBuffer(cntx, ro,
		sizeof(*scene->instance_mngr.texture_manager.ranvec) * PERLIN_SIZE,
		scene->instance_mngr.texture_manager.ranvec, &ret);
	rt_is_dead(opencl_err, cl_create_buffer_error, ret, "");

	program->perm_x = clCreateBuffer(cntx, ro, sizeof(cl_int) * PERLIN_SIZE,
		scene->instance_mngr.texture_manager.perm_x, &ret);
	rt_is_dead(opencl_err, cl_create_buffer_error, ret, "");

	program->perm_y = clCreateBuffer(cntx, ro, sizeof(cl_int) * PERLIN_SIZE,
		scene->instance_mngr.texture_manager.perm_y, &ret);
	rt_is_dead(opencl_err, cl_create_buffer_error, ret, "");

	program->perm_z = clCreateBuffer(cntx, ro, sizeof(cl_int) * PERLIN_SIZE,
		scene->instance_mngr.texture_manager.perm_z, &ret);
	rt_is_dead(opencl_err, cl_create_buffer_error, ret, "");
}

int			init_ocl(t_cl_program *const program, t_scene *const scene,
					t_sampler_manager *const sampler_manager,
					t_window const *const window,
					t_image *const image,
					cl_device_type device_type)
{
	init_clp(&program->info, device_type);
	init_kernel(program, window, image);
	// init_buffers(program, scene, sampler_manager);
	return (SUCCESS);
}
