/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_ocl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 18:59:58 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/13 12:05:20 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "rt_ocl.h"
#include "app.h"
#include "gui.h"

#include <assert.h>

static char		*load_arr[20] = {
	"./load/0001.png", "./load/0002.png", "./load/0003.png", "./load/0004.png", "./load/0005.png",
	"./load/0006.png", "./load/0007.png", "./load/0008.png", "./load/0009.png", "./load/0010.png",
	"./load/0011.png", "./load/0012.png", "./load/0013.png", "./load/0014.png", "./load/0015.png",
	"./load/0016.png", "./load/0017.png", "./load/0018.png", "./load/0019.png", "./load/0020.png"
};

static char		*text_arr[32] = {
	"./load_text/1001.png", "./load_text/1002.png", "./load_text/1003.png", "./load_text/1004.png", "./load_text/1005.png",
	"./load_text/1006.png", "./load_text/1007.png", "./load_text/1008.png", "./load_text/1009.png", "./load_text/1010.png",
	"./load_text/1011.png", "./load_text/1012.png", "./load_text/1013.png", "./load_text/1014.png", "./load_text/1015.png",
	"./load_text/1016.png", "./load_text/1017.png", "./load_text/1018.png", "./load_text/1019.png", "./load_text/1020.png",
	"./load_text/1021.png", "./load_text/1022.png", "./load_text/1023.png", "./load_text/1024.png", "./load_text/1025.png",
	"./load_text/1026.png", "./load_text/1027.png", "./load_text/1028.png", "./load_text/1029.png", "./load_text/1030.png",
	"./load_text/1031.png", "./load_text/1032.png"
};

static int	init_clp(t_clp *clp)
{
	cl_platform_id	pl_id;
	cl_uint			nde;

	pl_id = NULL;
	clp->de_id = NULL;
	if ((clp->ret = clGetPlatformIDs(1, &pl_id, NULL)))
		rt_error("init_clp(): clGetPlatformIDs error");
	if ((clp->ret = clGetDeviceIDs(pl_id, CL_DEVICE_TYPE_GPU, 1, &clp->de_id, &nde)))
		rt_error("init_clp(): clGetDeviceIDs error");
	clp->context = clCreateContext(NULL, 1, &clp->de_id, NULL, NULL, &clp->ret);
	if (clp->ret)
		rt_error("init_clp(): clCreateContext error");
	clp->queue = clCreateCommandQueue(clp->context, clp->de_id,
		0, &clp->ret);
	if (clp->ret)
		rt_error("init_clp(): clCreateCommandQueue error");
	return (0);
}

void CL_CALLBACK pfn_notify(cl_program program, void *data)
{
    int    *state;

	if (program == NULL)
		ft_putendl("pfn_notify");
    state = data;
    ft_putstr("ready");
    *state = 1;
}
static int state = 0;


int        test_thread(void *ptr)
{
    t_cl_program *p;

    p = ptr;

    int r;
    r = clBuildProgram(p->program, 1, &p->info.de_id,
                       "-cl-std=CL2.0", pfn_notify, &state);
    return (r);
}

void			resize_imgs(t_window *window, SDL_Event e, SDL_Rect *rect, SDL_Rect *mes_rec)
{
	window->width = e.window.data1;
	window->height = e.window.data2;
	*rect = (SDL_Rect){window->width / 2 - 500 * window->height / 658 / 2 ,0 ,500 * window->height / 658, 658 * window->height / 658};
	*mes_rec = (SDL_Rect){0, 0, 800 * window->width / 800 / 5, 600 * window->width / 800 / 5};
	printf("Window size changed to %dx%d\n", e.window.data1, e.window.data2);
}

void			add_img_to_screen(t_window *window, SDL_Surface *sur, SDL_Rect rect)
{
	SDL_Texture	*tex;

	tex = SDL_CreateTextureFromSurface(window->renderer, sur);
	SDL_RenderCopy(window->renderer, tex, NULL, &rect);
	SDL_FreeSurface(sur);
	SDL_DestroyTexture(tex);
	SDL_Delay(25);
}

void			loading_cycle(t_window *window, SDL_Rect rect, SDL_Rect mes_rec)
{
	int			i;
	int			j;
	SDL_Surface *sur;
	SDL_Event	e;

	i = 0;
	j = 0;
	while (state != 1)
	{
    	if (SDL_PollEvent(&e))
    		if (e.type == SDL_QUIT)
        		break;
		if (e.window.event == SDL_WINDOWEVENT_RESIZED)
			resize_imgs(window, e, &rect, &mes_rec);
		SDL_RenderFillRect(window->renderer, NULL);
		sur = IMG_Load(load_arr[j]);
		add_img_to_screen(window, sur, rect);
		sur= IMG_Load(text_arr[i]);
		add_img_to_screen(window, sur, mes_rec);
		SDL_RenderPresent(window->renderer);
		i = i == 31 ? 0 : i + 1;
		j = j == 19 ? 0 : j + 1;
	}
}

void			loading_screen(t_cl_program *p, t_window *window)
{
	SDL_Thread	*thread;
	int			threadReturnValue;
	SDL_Rect	mes_rec;
	SDL_Rect	rect;

	mes_rec = (SDL_Rect){0, 0, 800 * window->width / 800 / 5,
	600 * window->width / 800 / 5};
	rect = (SDL_Rect){window->width / 2 - 500 * window->height / 658 / 2 ,
	0 ,500 * window->height / 658, 658 * window->height / 658};
	thread = SDL_CreateThread(test_thread, "TestThread", (void *)p);
	SDL_SetRenderDrawColor(window->renderer, 255, 255, 255, 0);
	if (NULL == thread)
		printf("SDL_CreateThread failed: %s\n", SDL_GetError());
	else
	{
		loading_cycle(window, rect, mes_rec);
		SDL_WaitThread(thread, &threadReturnValue);
	}
}

static int    init_kernel(t_cl_program *p, t_window *window)
{
    int        r;
    size_t    a;

    r = 0;
    p->work_size = IMG_WIDTH * IMG_HEIGHT;
    p->work_group_size = WORK_GROUP_SIZE;
    p->program = create_program(p->info.context);

	loading_screen(p, window);
    printf("4\n");
    cl_error(p, &p->info, r);
    assert(!r);
    p->new_kernel = clCreateKernel(p->program, KERNEL_NAME, &r);
    cl_error(p, &p->info, r);
    assert(!r);
    p->help_kernel = clCreateKernel(p->program, "translate_image", &r);
    assert(!r);
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
	cl_error(program, &program->info, ret);
	program->output_image = clCreateBuffer(cntx, CL_MEM_READ_WRITE,
							sizeof(uint32_t) * program->work_size, NULL, &ret);
	cl_error(program, &program->info, ret);

	program->instances = clCreateBuffer(cntx, ro, sizeof(t_instance) *
	(scene->instance_mngr.ninstances), scene->instance_mngr.instances, &ret);
	cl_error(program, &program->info, ret);

	program->objects = clCreateBuffer(cntx, ro, sizeof(t_obj) *
	(scene->instance_mngr.nobjects + 1), scene->instance_mngr.objects, &ret);
	cl_error(program, &program->info, ret);

	program->triangles = clCreateBuffer(cntx, ro, sizeof(t_triangle) * (scene->
	instance_mngr.ntriangles + 1), scene->instance_mngr.triangles, &ret);
	cl_error(program, &program->info, ret);

	program->matrices = clCreateBuffer(cntx, ro, sizeof(t_matrix) *
		(scene->instance_mngr.nmatrices), scene->instance_mngr.matrices, &ret);
	cl_error(program, &program->info, ret);

	program->bvh = clCreateBuffer(cntx, ro, sizeof(t_bvh_node) *
		(scene->instance_mngr.ninstances * 2), scene->bvh, &ret);
	cl_error(program, &program->info, ret);

	program->lights = clCreateBuffer(cntx, ro, sizeof(t_light) *
		(scene->light_manager.nlights + 1), scene->light_manager.lights, &ret);
	cl_error(program, &program->info, ret);

	program->samplers = clCreateBuffer(cntx, ro, sizeof(t_sampler) *
					sampler_manager->count, sampler_manager->samplers, &ret);
	cl_error(program, &program->info, ret);

	program->samples = clCreateBuffer(cntx, ro, sampler_manager->samples_size,
										 sampler_manager->samples, &ret);
	cl_error(program, &program->info, ret);

	program->disk_samples = clCreateBuffer(cntx, ro, sampler_manager->
		disk_samples_size, sampler_manager->disk_samples, &ret);
	cl_error(program, &program->info, ret);

	program->hemisphere_samples = clCreateBuffer(cntx, ro, sampler_manager->
		hemisphere_samples_size, sampler_manager->hemisphere_samples, &ret);

	cl_error(program, &program->info, ret);

	program->textures = clCreateBuffer(cntx, ro, sizeof(t_texture) *
		scene->instance_mngr.texture_manager.ntextures,
		scene->instance_mngr.texture_manager.textures, &ret);
	cl_error(program, &program->info, ret);

	program->ranvec = clCreateBuffer(cntx, ro,
		sizeof(*scene->instance_mngr.texture_manager.ranvec) * PERLIN_SIZE,
		scene->instance_mngr.texture_manager.ranvec, &ret);
	cl_error(program, &program->info, ret);

	program->perm_x = clCreateBuffer(cntx, ro, sizeof(cl_int) * PERLIN_SIZE,
		scene->instance_mngr.texture_manager.perm_x, &ret);
	cl_error(program, &program->info, ret);

	program->perm_y = clCreateBuffer(cntx, ro, sizeof(cl_int) * PERLIN_SIZE,
		scene->instance_mngr.texture_manager.perm_y, &ret);
	cl_error(program, &program->info, ret);

	program->perm_z = clCreateBuffer(cntx, ro, sizeof(cl_int) * PERLIN_SIZE,
		scene->instance_mngr.texture_manager.perm_z, &ret);
	cl_error(program, &program->info, ret);
}

int			init_ocl(t_cl_program *program, t_scene *scene,
					t_sampler_manager *sampler_manager, t_window *window)
{
	init_clp(&program->info);
	init_kernel(program, window);
	init_buffers(program, scene, sampler_manager);
	return (SUCCESS);
}
