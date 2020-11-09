/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qjulia_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 18:39:46 by alex              #+#    #+#             */
/*   Updated: 2020/11/09 18:44:35 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "julia.h"

void				create_texture(t_texture2 *texture)
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

int					origin_region(t_compute *compute)
{
	size_t			origin[3];
	size_t			region[3];
	int				err;

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

void				gl_render_init(t_texture2 *texture)
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

SDL_Window			*qjulia_sdl_init(void)
{
	SDL_Window		*window;
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
