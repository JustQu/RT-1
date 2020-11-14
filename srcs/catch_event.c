/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 23:21:28 by dmelessa          #+#    #+#             */
/*   Updated: 2020/11/14 03:15:23 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "interface.h"
# include "rt.h"

int catch_event(t_rt *rt)
{
	SDL_Event event;

	if (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
		{
			return 1;
		}
		if (event.type == SDL_WINDOWEVENT)
		{
			switch (event.window.event)
			{
			case SDL_WINDOWEVENT_SHOWN:
			case SDL_WINDOWEVENT_HIDDEN:
			case SDL_WINDOWEVENT_EXPOSED:
			case SDL_WINDOWEVENT_MOVED:
			case SDL_WINDOWEVENT_SIZE_CHANGED:
			case SDL_WINDOWEVENT_MINIMIZED:
			case SDL_WINDOWEVENT_MAXIMIZED:
				break;
			case SDL_WINDOWEVENT_CLOSE:
				return 1;

			case SDL_WINDOWEVENT_RESIZED:
			{
				printf("Window size changed to %dx%d\n",
					   event.window.data1, event.window.data2);
			}
			break;
			}
		}
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
				return 1;
			if (event.key.keysym.sym == SDLK_p)
			{
				rt->options.shadows = !rt->options.shadows;
			}
			if (event.key.keysym.sym == SDLK_r)
			{
				rt->options.reset = 1;
				rt->options.spp = NUM_SAMPLES;
			}
			if (event.key.keysym.sym == SDLK_w)
			{
				move_camera(&rt->scene.camera, 2, 0.1f);
				rt->options.reset = 1;
				rt->options.spp = NUM_SAMPLES;
			}
			if (event.key.keysym.sym == SDLK_s)
			{
				move_camera(&rt->scene.camera, 2, -0.1f);
				rt->options.reset = 1;
				rt->options.spp = NUM_SAMPLES;
			}
			if (event.key.keysym.sym == SDLK_a)
			{
				move_camera(&rt->scene.camera, 0, -0.1f);
				rt->options.reset = 1;
				rt->options.spp = NUM_SAMPLES;
			}
			if (event.key.keysym.sym == SDLK_d)
			{
				move_camera(&rt->scene.camera, 0, 0.1f);
				rt->options.reset = 1;
				rt->options.spp = NUM_SAMPLES;
			}
			if (event.key.keysym.sym == SDLK_LSHIFT)
			{
				move_camera(&rt->scene.camera, 1, 0.1f);
				rt->options.reset = 1;
				rt->options.spp = NUM_SAMPLES;
			}
			if (event.key.keysym.sym == SDLK_LCTRL)
			{
				move_camera(&rt->scene.camera, 1, -0.1f);
				rt->options.reset = 1;
				rt->options.spp = NUM_SAMPLES;
			}
			if (event.key.keysym.sym == SDLK_DOWN)
			{
				rotate_camera(&rt->scene.camera, 0, 1.0f);
				rt->options.reset = 1;
				rt->options.spp = NUM_SAMPLES;
			}
			if (event.key.keysym.sym == SDLK_UP)
			{
				rotate_camera(&rt->scene.camera, 0, -1.0f);
				rt->options.reset = 1;
				rt->options.spp = NUM_SAMPLES;
			}
			if (event.key.keysym.sym == SDLK_LEFT)
			{
				rotate_camera(&rt->scene.camera, 1, -1.0f);
				rt->options.reset = 1;
				rt->options.spp = NUM_SAMPLES;
			}
			if (event.key.keysym.sym == SDLK_RIGHT)
			{
				rotate_camera(&rt->scene.camera, 1, 1.0f);
				rt->options.reset = 1;
				rt->options.spp = NUM_SAMPLES;
			}
			if (event.key.keysym.sym == SDLK_q)
			{
				rotate_camera(&rt->scene.camera, 2, 1.0f);
				rt->options.reset = 1;
				rt->options.spp = NUM_SAMPLES;
			}
			if (event.key.keysym.sym == SDLK_e)
			{
				rotate_camera(&rt->scene.camera, 2, -1.0f);
				rt->options.reset = 1;
				rt->options.spp = NUM_SAMPLES;
			}
		}
		if (event.type == SDL_KEYUP)
		{
		}
		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			//todo: translate window coordinates in image coordinates,
			//e.g. windos is 1200x600 and image is 1920x1080
			//then we need x * IMG_W/WIN_W and y * IMG_H/WIN_H
			printf("Mouse press at %d %d", event.button.x, event.button.y);
			rt->options.x = event.button.x;
			rt->options.y = event.button.y;

		}
		if (event.type == SDL_MOUSEBUTTONUP)
		{
		}

		//check input
		//switch kernel here?
		return -1;
	}
	return 0;
}
