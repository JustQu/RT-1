/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 19:54:03 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/06 17:04:32 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "app.h"

static void	set_kernel_args(t_rt rt, int step)
{
	static uint32_t	a;
	cl_kernel		k;
	int				err;

	k = rt.ocl_program.new_kernel;
	err = 0;
	err |= clSetKernelArg(k, 0, sizeof(cl_mem), &rt.ocl_program.rgb_image);
	err |= clSetKernelArg(k, 1, sizeof(cl_int), &step);
	err |= clSetKernelArg(k, 2, sizeof(cl_mem), &rt.ocl_program.instances);
	err |= clSetKernelArg(k, 3, sizeof(cl_int),
							&rt.scene.instance_mngr.ninstances);
	err |= clSetKernelArg(k, 4, sizeof(cl_mem), &rt.ocl_program.objects);
	err |= clSetKernelArg(k, 5, sizeof(cl_int),
							&rt.scene.instance_mngr.nobjects);
	err |= clSetKernelArg(k, 6, sizeof(cl_mem), &rt.ocl_program.triangles);
	err |= clSetKernelArg(k, 7, sizeof(cl_int),
							&rt.scene.instance_mngr.ntriangles);
	err |= clSetKernelArg(k, 8, sizeof(cl_mem), &rt.ocl_program.matrices);
	err |= clSetKernelArg(k, 9, sizeof(cl_int),
							&rt.scene.instance_mngr.nmatrices);
	err |= clSetKernelArg(k, 10, sizeof(cl_mem), &rt.ocl_program.lights);
	err |= clSetKernelArg(k, 11, sizeof(cl_int),
							&rt.scene.light_manager.nlights);
	err |= clSetKernelArg(k, 12, sizeof(t_camera), &rt.scene.camera);
	err |= clSetKernelArg(k, 13, sizeof(t_light), &rt.scene.ambient_light);
	err |= clSetKernelArg(k, 14, sizeof(t_ambient_occluder),
							&rt.scene.ambient_occluder);
	err |= clSetKernelArg(k, 15, sizeof(cl_mem), &rt.ocl_program.bvh);
	err |= clSetKernelArg(k, 16, sizeof(t_rt_options), &rt.options);
	err |= clSetKernelArg(k, 17, sizeof(cl_mem), &rt.ocl_program.samplers);
	err |= clSetKernelArg(k, 18, sizeof(cl_mem), &rt.ocl_program.samples);
	err |= clSetKernelArg(k, 19, sizeof(cl_mem), &rt.ocl_program.disk_samples);
	err |= clSetKernelArg(k, 20, sizeof(cl_mem),
							&rt.ocl_program.hemisphere_samples);
	err |= clSetKernelArg(k, 21, sizeof(uint32_t), &a);
	err |= clSetKernelArg(k, 22, sizeof(cl_mem), &rt.ocl_program.textures);
	err |= clSetKernelArg(k, 23, sizeof(cl_mem), &rt.ocl_program.ranvec);
	err |= clSetKernelArg(k, 24, sizeof(cl_mem), &rt.ocl_program.perm_x);
	err |= clSetKernelArg(k, 25, sizeof(cl_mem), &rt.ocl_program.perm_y);
	err |= clSetKernelArg(k, 26, sizeof(cl_mem), &rt.ocl_program.perm_z);
	a++;
	assert(!err);
}

void		render_scene(t_rt rt)
{
	int	err;
	int	i;

	i = 0;
	while (i < NUM_SAMPLES)
	{
		set_kernel_args(rt, i);
		err = clEnqueueNDRangeKernel(rt.ocl_program.info.queue,
									rt.ocl_program.new_kernel,
									1, NULL,
									&rt.ocl_program.work_size,
									NULL,
									0, NULL, NULL);
		cl_error(&rt.ocl_program, &rt.ocl_program.info, err);
		assert(!err);
		i++;
	}
}

int			init_rt(t_rt *rt, char *scene_file, t_res_mngr *resource_manager)
{
	init_sampler_manager(&rt->sampler_manager);
	init_default_options(resource_manager->rt_options, &rt->sampler_manager);
	if (scene_file != NULL)
	{
		if (init_parsed_scene(&rt->scene, &rt->sampler_manager, resource_manager, scene_file) < 0)
			init_default_scene(&rt->scene, &rt->sampler_manager, resource_manager);
		rt->scene.bvh = build_bvh(&rt->scene);
		init_ocl(&rt->ocl_program, &rt->scene, &rt->sampler_manager, rt);
	}
	else
	{
		init_default_scene(&rt->scene, &rt->sampler_manager, resource_manager);
		rt->scene.bvh = build_bvh(&rt->scene);
		init_ocl(&rt->ocl_program, &rt->scene, &rt->sampler_manager, rt);
	}
	return (SUCCESS);
}
