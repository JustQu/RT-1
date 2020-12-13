/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_program.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 16:19:38 by marvin            #+#    #+#             */
/*   Updated: 2020/12/04 23:18:27 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rt_ocl.h"
#include "rt_err.h"
#include <fcntl.h>
#include <assert.h>

#define BUFF 100000

static const char	*g_files[] = {
	"rt_types.h",
	"color.h",
	"aabb.h",
	"camera.h",
	"texture.h",
	"material.h",
	"objects.h",
	"light.h",
	"sampler.h",
	"instance.h",
	"bvh.h",
	"rt_options.h",
	"cl_rt.h",
	"utils.cl",
	"print.cl",
	"solver.cl",
	"random.cl",
	"color.cl",
	"sampler.cl",
	"sampler_manager.cl",
	"matrix.cl",
	"normal.cl",
	"intersection.cl",
	"light.cl",
	"brdf.cl",
	"ambient_occlusion.cl",
	"perlin.cl",
	"material.cl",
	"shade.cl",
	"area_light_shade.cl",
	"ray_tracer.cl",
	"path_tracer.cl",
	"trace.cl",
	"area_light_tracer.cl",
	"camera.cl",
	"main_kernel.cl",
	"util_kernels.cl",
};

static int		g_num_files = sizeof(g_files) / sizeof(char *);

static void		read_file(const char *file_name, char *str)
{
	char	full_file_name[128];
	int		ret;
	int		fd;

	if (file_name == NULL)
		rt_error("read_file(): given NULL pointer");
	if (ft_strcpy(full_file_name, DEFAULT_KERNEL_DIR) == NULL)
		rt_error("read_file(): ft_strcpy error");
	if (ft_strcpy(full_file_name + sizeof(DEFAULT_KERNEL_DIR) - 1, file_name) == NULL)
		rt_error("read_file(): ft_strcpy error");
	fd = open(full_file_name, O_RDONLY);
	if (fd == -1)
	{
		if (ft_strcpy(full_file_name, "./include/") == NULL)
			rt_error("read_file(): ft_strcpy error");
		if (ft_strcpy(full_file_name + sizeof("./include/") - 1, file_name) == NULL)
			rt_error("read_file(): ft_strcpy error");
		fd = open(full_file_name, O_RDONLY);
		if (fd < 3)
			rt_error("read_file(): open error, wrong fd");
	}
	if (fd < 3)
		rt_error("read_file(): open error, wrong fd");
	ret = read(fd, str, BUFF);
	if (ret < 0)
		rt_error("read_file(): read error");
	str[ret] = '\0';
	if (close(fd))
		rt_error("read_file(): close error");
}

extern FILE		*f;

cl_program		create_program(cl_context context)
{
	int			ret;
	int			i;
	int			fd;
	char		**str;
	cl_program	program;

	i = 0;
	if ((str = ft_memalloc(sizeof(char *) * g_num_files)) == NULL)
		rt_error("create_program(): malloc error");
	ret = 0;
	while (i < g_num_files)
	{
		if ((str[i] = ft_memalloc(sizeof(char) * BUFF)) == NULL)
			rt_error("create_program(): malloc error");
		read_file(g_files[i], str[i]);
		fprintf(f, "%s\n", str[i]);
		i++;
	}
	program = clCreateProgramWithSource(context, g_num_files, str, NULL, &ret);
	if (ret)
		rt_error("create_program(): clCreateProgramWithSource error");
	while (i--)
		ft_strdel(&str[i]);
	ft_strdel(&str);
	return (program);
}
