/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qjulia_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 18:33:21 by alex              #+#    #+#             */
/*   Updated: 2020/11/09 18:38:04 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "julia.h"

void			error_julia(int err, char *str)
{
	printf("%s\n", str);
	exit(err);
}

void			cleanup(t_compute *compute)
{
	clFinish(compute->commands);
	clReleaseKernel(compute->kernel);
	clReleaseProgram(compute->program);
	clReleaseCommandQueue(compute->commands);
	clRetainMemObject(compute->result);
	clReleaseMemObject(compute->image);
	compute->commands = 0;
	compute->kernel = 0;
	compute->result = 0;
	compute->program = 0;
	compute->image = 0;
	compute->context = 0;
}

void			shutdown(t_compute *compute)
{
	printf("Shutting down...\n");
	cleanup(compute);
	exit(0);
}

void			setup_color(float color[4], SDL_Color *colors)
{
	color[0] = colors->r;
	color[1] = colors->g;
	color[2] = colors->b;
	color[3] = colors->a;
}

int				load_text_from_file(
		const char *file_name, char **result_string, size_t *string_len)
{
	int			fd;
	unsigned	file_len;
	struct stat	file_status;
	int			ret;

	*string_len = 0;
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (-1);
	if ((fstat(fd, &file_status)))
		return (-1);
	file_len = file_status.st_size;
	*result_string = (char*)calloc(file_len + 1, sizeof(char));
	ret = read(fd, *result_string, file_len);
	if (!ret)
		return (-1);
	close(fd);
	*string_len = file_len;
	return (0);
}
