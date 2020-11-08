/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qjulia.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 15:28:34 by user              #+#    #+#             */
/*   Updated: 2020/11/08 16:26:06 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "julia.h"
#include "gui.h"
#include "rt.h"

void	create_texture(t_texture2 *texture)
{
	if (texture->id)
		glDeleteTextures(1, &texture->id);
	texture->id = 0;
	glActiveTextureARB(texture->active_uint);
	glGenTextures(1, &texture->id);
	glBindTexture(texture->target, texture->id);
	glTexParameteri(texture->target, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(texture->target, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(texture->target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(texture->target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(texture->target, 0, texture->internal, J_WIDTH, J_HEIGHT, 0,
				texture->format, texture->type, 0);
	glBindTexture(texture->target, 0);
}

int		setup_graphics(t_texture2 *texture)
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

int			setup_compute_device(t_compute *compute)
{
	int		err;
	size_t	return_size;
	compute->device_type = CL_DEVICE_TYPE_GPU;

	CGLContextObj kcgl_context = CGLGetCurrentContext();
	CGLShareGroupObj kcgl_shape_group = CGLGetShareGroup(kcgl_context);

	cl_context_properties properties[] = {
		CL_CONTEXT_PROPERTY_USE_CGL_SHAREGROUP_APPLE,
		(cl_context_properties)kcgl_shape_group, 0
	};

	compute->context = clCreateContext(properties, 0, 0,
		clLogMessagesToStderrAPPLE, 0, 0);
	if (!compute->context)
		printf("Error: Failed to create a compute context!\n");

	unsigned int device_count;
	cl_device_id device_ids[16];

	err = clGetContextInfo(compute->context, CL_CONTEXT_DEVICES,
		sizeof(device_ids), device_ids, &return_size);
	if (err)
		printf("Error: Failed to retrieve compute devices for context!\n");

	device_count = return_size / sizeof(cl_device_id);

	unsigned int i = 0;
	int device_found = 0;
	cl_device_type device_type;
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

	compute->commands = clCreateCommandQueue(compute->context,
		compute->device_id, 0, &err);
	if (!compute->commands)
		printf("Error: Failed to create a command queue!\n");

	cl_char vendor_name[1024] = {0};
	cl_char device_name[1024] = {0};
	err = clGetDeviceInfo(compute->device_id, CL_DEVICE_VENDOR,
		sizeof(vendor_name), vendor_name, &return_size);
	err |= clGetDeviceInfo(compute->device_id, CL_DEVICE_NAME,
		sizeof(device_name), device_name, &return_size);
	if (err != CL_SUCCESS)
		printf("Error: Failed to retrieve device info!\n");
	return (CL_SUCCESS);
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

void		setup_preprocessor(t_compute *compute, char *source)
{
	char	*preprocess;
	int		err;

	preprocess = (char*)malloc(strlen(source) + 1024);
	sprintf(preprocess, "\n%s (%d)\n%s (%d)\n%s", "#define J_WIDTH",
		J_WIDTH, "#define J_HEIGHT", J_HEIGHT, source);
	compute->program = clCreateProgramWithSource(compute->context, 1,
		(const char **)&preprocess, NULL, &err);
	if (!compute->program || err != CL_SUCCESS)
		printf("Error: Failed to create compute program!\n");
	free(source);
	free(preprocess);
}

void		compute_build_program(int err, t_compute *compute)
{
	size_t	len;
	char	buffer[2048];

	if (err != CL_SUCCESS)
	{
		printf("Error: Failed to build program executable!\n");
		clGetProgramBuildInfo(compute->program, compute->device_id,
			CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, &len);
		printf("%s\n", buffer);
	}
}

int			setup_compute_kernel(t_compute *compute)
{
	int err;
	char *source;
	size_t lenght;

	// err = 0;
	// source = 0;
	// lenght = 0;
	if (compute->kernel)
		clReleaseKernel(compute->kernel);
	compute->kernel = 0;
	if (compute->program)
		clReleaseProgram(compute->program);
	compute->program = 0;
	err = load_text_from_file(COMPUTE_KERNEL_FILENAME, &source, &lenght);
	setup_preprocessor(compute, source);
	err = clBuildProgram(compute->program, 0, NULL, NULL, NULL, NULL);
	compute_build_program(err, compute);
	compute->kernel = clCreateKernel(compute->program,
		COMPUTE_KERNEL_METHOD_NAME, &err);
	err = clGetKernelWorkGroupInfo(compute->kernel, compute->device_id,
			CL_KERNEL_WORK_GROUP_SIZE, sizeof(size_t),
			&compute->max_work_group_size, NULL);
	compute->work_group_size[0] = (compute->max_work_group_size > 1)
		? (compute->max_work_group_size
		/ compute->work_group_items) : compute->max_work_group_size;
	compute->work_group_size[1] = compute->max_work_group_size
		/ compute->work_group_size[0];
	return (CL_SUCCESS);
}

int		create_compute_result(t_texture2 *texture, t_compute *compute)
{
	int err;

	err = 0;
	if (compute->image)
		clReleaseMemObject(compute->image);
	compute->image = 0;
	compute->image = clCreateFromGLTexture2D(compute->context,
		CL_MEM_WRITE_ONLY, texture->target, 0, texture->id, &err);
	if (!compute->image || err != CL_SUCCESS)
		printf("Failed to create OpenGL texture reference! %d\n", err);
	if (compute->result)
		clReleaseMemObject(compute->result);
	compute->result = 0;
	compute->result = clCreateBuffer(compute->context, CL_MEM_WRITE_ONLY,
		texture->type_size * 4 * J_WIDTH * J_HEIGHT, NULL, NULL);
	if (!compute->result)
		printf("Failed to create OpenCL array!\n");
	return (CL_SUCCESS);
}

void				ft_values(t_compute *compute, t_julia_color *color)
{
	void			*values[10];
	size_t			sizes[10];
	unsigned int	v;
	unsigned int	s;
	unsigned int	a;

	v = 0;
	s = 0;
	a = 0;
	values[v++] = &compute->result;
	values[v++] = color->muc;
	values[v++] = color->color_c;
	values[v++] = &color->epsilon;
	sizes[s++] = sizeof(cl_mem);
	sizes[s++] = 4 * (sizeof(float));
	sizes[s++] = 4 * (sizeof(float));
	sizes[s++] = sizeof(float);
	if (compute->animated || compute->update)
	{
		compute->update = 0;
		a = 0;
		while (a < s)
			clSetKernelArg(compute->kernel, a, sizes[a], values[a++]);
	}
}

int			origin_region(t_compute *compute)
{
	size_t	origin[3];
	size_t	region[3];
	int		err;

	origin[0] = 0;
	origin[1] = 0;
	origin[2] = 0;
	region[0] = J_WIDTH;
	region[1] = J_HEIGHT;
	region[2] = 1;
	err = clEnqueueCopyBufferToImage(compute->commands, compute->result,
		compute->image, 0, origin, region, 0, NULL, 0);
	if (err != CL_SUCCESS)
		printf("Failed to copy buffer to image! %d\n", err);
	err = clEnqueueReleaseGLObjects(compute->commands, 1,
		&compute->image, 0, 0, 0);
	if (err != CL_SUCCESS)
		printf("Failed to release GL object! %d\n", err);
	return (err);
}

int			recompute(t_compute *compute, t_julia_color *color)
{
	size_t	global[2];
	size_t	local[2];
	int		err;

	if (!compute->kernel || !compute->result)
		return (CL_SUCCESS);
	err = 0;
	ft_values(compute, color);
	global[0] = divide_up(J_WIDTH, compute->work_group_size[0])
		* compute->work_group_size[0];
	global[1] = divide_up(J_HEIGHT, compute->work_group_size[1])
		* compute->work_group_size[1];
	local[0] = compute->work_group_size[0];
	local[1] = compute->work_group_size[1];
	err = clEnqueueNDRangeKernel(compute->commands, compute->kernel, 2,
		NULL, global, local, 0, NULL, NULL);
	if (err)
		printf("Failed to enqueue kernel! %d\n", err);
	err = clEnqueueAcquireGLObjects(compute->commands, 1,
		&compute->image, 0, 0, 0);
	if (err != CL_SUCCESS)
		printf("Failed to acquire GL object! %d\n", err);
	origin_region(compute);
	return (CL_SUCCESS);
}

void	gl_render_init(t_texture2 *texture)
{
	glDisable(GL_LIGHTING);
	glViewport(0, 0, J_WIDTH, J_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(texture->target);
	glBindTexture(texture->target, texture->id);
}

void	qjulia_render_texture(t_texture2 *texture)
{
	gl_render_init(texture);
	if (texture->host_image_buffer)
		glTexSubImage2D(texture->target, 0, 0, 0, J_WIDTH,
		J_HEIGHT, texture->format, texture->type, texture->host_image_buffer);
	glTexParameteri(texture->target, GL_TEXTURE_COMPARE_MODE, GL_NONE);
	glBegin(GL_QUADS);
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 0.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, 0.0f);
	}
	glEnd();
	glBindTexture(texture->target, 0);
	glDisable(texture->target);
}

void		display(t_texture *texture, t_compute *compute,
				t_julia_color *color)
{
	int		err;

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	if (compute->animated)
	{
		update_mu(&color->mut, color->mua, color->mub);
		interpolate(color->muc, color->mut, color->mua, color->mub);
		update_color(&color->color_t, color->color_a, color->color_b);
		interpolate(color->color_c, color->color_t,
			color->color_a, color->color_b);
	}
	err = recompute(compute, color);
	if (err != 0)
		printf("Error %d from Recompute!\n", err);
	qjulia_render_texture(texture);
	glFinish();
}

void	error_julia(int err, char *str)
{
	printf("%s\n", str);
	exit(err);
}

void	cleanup(t_compute *compute)
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

void	shutdown(t_compute *compute)
{
	printf("Shutting down...\n");
	cleanup(compute);
	exit(0);
}

void		setup_color(float color[4], SDL_Color *colors)
{
	color[0] = colors->r;
	color[1] = colors->g;
	color[2] = colors->b;
	color[3] = colors->a;
}

SDL_Window				*qjulia_sdl_init()
{
	SDL_Window *window;
	SDL_GLContext	glcontext;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		printf("error");
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 6);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
	window = SDL_CreateWindow("sdl_julia", 100, 100, J_WIDTH,
		J_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	glcontext = SDL_GL_CreateContext(window);
	if (window == NULL)
		printf("error window");
	return (window);
}

void				qjulia_main_loop(t_compute *compute,
						t_texture2 *texture, t_julia_color *color)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT ||
			event.key.keysym.sym == SDLK_ESCAPE)
		{
			exit(0);
		}
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_SPACE)
				compute->animated ^= 1;
		}
	}
}

void				main_qjulia(void)
{
	t_compute		compute;
	t_texture		texture;
	t_julia_color	color;
	SDL_Window		*window;
	int loop;

	loop = 1;
	init_texture_cl(&texture);
	init_compute_cl(&compute);
	init_julia_color(&color);
	window = qjulia_sdl_init(window);
	if (init_cl(&texture, &compute, &color) == GL_NO_ERROR)
	{
		while (loop)
		{
			qjulia_main_loop(&compute, &texture, &color);
			display(&texture, &compute, &color);
			SDL_GL_SwapWindow(window);
		}
	}
}
