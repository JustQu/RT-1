/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_program.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 16:19:38 by marvin            #+#    #+#             */
/*   Updated: 2020/10/01 20:18:41 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rt_ocl.h"

#include <fcntl.h>
#include <assert.h>

#define BUFF 100000

static const char *files[] = {
	"rt_types.h",
	"color.h",
	"camera.h",
	"aabb.h",
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
	"camera.cl",
	"intersection.cl",
	"normal.cl",
	"light.cl",
	"brdf.cl",
	"ambient_occlusion.cl",
	"shade.cl",
	"area_light_shade.cl",
	"ray_tracer.cl",
	"path_tracer.cl",
	"main_kernel.cl",
	"util_kernels.cl",
};
static int		g_num_files = sizeof(files) / sizeof(char *);

static void		read_file(const char *file_name, char *str)
{
	char	full_file_name[128];
	int		ret;
	int		fd;

	ft_strcpy(full_file_name, DEFAULT_KERNEL_DIR);
	ft_strcpy(full_file_name + sizeof(DEFAULT_KERNEL_DIR) - 1, file_name);

	fd = open(full_file_name, O_RDONLY);
	if (fd == -1)
	{
		ft_strcpy(full_file_name, "./include/");
		ft_strcpy(full_file_name + sizeof("./include/") - 1, file_name);
		fd = open(full_file_name, O_RDONLY);
		assert(fd != -1);
	}
	assert(fd != -1);
	ret = read(fd, str, BUFF);
	str[ret] = '\0';
	close(fd);
}

extern FILE *f;

cl_program	create_program(cl_context context)
{
	int ret;
	int i;
	int fd;
	char **str;
	cl_program program;

	i = 0;
	str = malloc(sizeof(char *) * g_num_files);
	ret = 0;
	while (i < g_num_files)
	{
		str[i] = malloc(sizeof(char) * BUFF);
		read_file(files[i], str[i]);
		// fprintf(f, "%s\n", str[i]);
		i++;
	}
	program = clCreateProgramWithSource(context, g_num_files, str, NULL, &ret);
	assert(!ret);
	while (i--)
		free(str[i]);
	free(str);
	return (program);
}
