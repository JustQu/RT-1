/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qjulia_compute.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 18:26:58 by alex              #+#    #+#             */
/*   Updated: 2020/11/09 18:29:56 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "julia.h"

int							setup_graphics(t_texture2 *texture)
{
	create_texture(texture);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glDisable(GL_DEPTH_TEST);
	glActiveTexture(GL_TEXTURE0);
	glViewport(0, 0, J_WIDTH, J_HEIGHT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	return (GL_NO_ERROR);
}

void						ft_cgl_context(t_compute *compute)
{
	CGLContextObj			kcgl_context;
	CGLShareGroupObj		kcgl_shape_group;
	cl_context_properties	properties[3];

	kcgl_context = CGLGetCurrentContext();
	kcgl_shape_group = CGLGetShareGroup(kcgl_context);
	properties[0] = CL_CONTEXT_PROPERTY_USE_CGL_SHAREGROUP_APPLE;
	properties[1] = (cl_context_properties)kcgl_shape_group;
	properties[2] = 0;
	compute->context = clCreateContext(properties, 0, 0,
		clLogMessagesToStderrAPPLE, 0, 0);
	if (!compute->context)
		printf("Error: Failed to create a compute context!\n");
}

void						ft_device_type(int device_count,
				cl_device_id **device_ids, t_compute *compute)
{
	unsigned int			i;
	int						device_found;
	cl_device_type			device_type;

	i = 0;
	device_found = 0;
	while (i < device_count)
	{
		clGetDeviceInfo(device_ids[i], CL_DEVICE_TYPE,
			sizeof(cl_device_type), &device_type, NULL);
		if (device_type == compute->device_type)
		{
			compute->device_id = device_ids[i];
			device_found = 1;
			break ;
		}
		i++;
	}
	if (!device_found)
		printf("Error: Failed to locate compute device!\n");
}

void						ft_get_device_info(t_compute *compute,
								size_t return_size)
{
	cl_char					vendor_name[1024];
	cl_char					device_name[1024];
	int						err;

	err = clGetDeviceInfo(compute->device_id, CL_DEVICE_VENDOR,
		sizeof(vendor_name), vendor_name, &return_size);
	err |= clGetDeviceInfo(compute->device_id, CL_DEVICE_NAME,
		sizeof(device_name), device_name, &return_size);
	if (err != CL_SUCCESS)
		printf("Error: Failed to retrieve device info!\n");
}

int							setup_compute_device(t_compute *compute)
{
	int						err;
	size_t					return_size;
	unsigned int			device_count;
	cl_device_id			device_ids[16];

	compute->device_type = CL_DEVICE_TYPE_GPU;
	ft_cgl_context(compute);
	err = clGetContextInfo(compute->context, CL_CONTEXT_DEVICES,
		sizeof(device_ids), device_ids, &return_size);
	if (err)
		printf("Error: Failed to retrieve compute devices for context!\n");
	device_count = return_size / sizeof(cl_device_id);
	ft_device_type(device_count, device_ids, compute);
	compute->commands = clCreateCommandQueue(compute->context,
		compute->device_id, 0, &err);
	if (!compute->commands)
		printf("Error: Failed to create a command queue!\n");
	ft_get_device_info(compute, return_size);
	return (CL_SUCCESS);
}
