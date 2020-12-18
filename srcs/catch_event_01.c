/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_event_01.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 11:00:55 by jvoor             #+#    #+#             */
/*   Updated: 2020/12/14 11:00:56 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "rt.h"
#include "gui.h"
#include "ocl_err_handl.h"

static int			catch_keydown_03(t_rt *rt, t_interface *interface,
									SDL_Event event)
{
	if (event.key.keysym.sym == SDLK_q)
	{
		rotate_camera(&rt->scene.camera, 2, -1.0f);
		rt->options.reset = 1;
		rt->options.spp = NUM_SAMPLES;
	}
	if (event.key.keysym.sym == SDLK_e)
	{
		rotate_camera(&rt->scene.camera, 2, 1.0f);
		rt->options.reset = 1;
		rt->options.spp = NUM_SAMPLES;
	}
	if (event.key.keysym.sym == SDLK_F10)
		SDL_SetRelativeMouseMode(SDL_TRUE);
	if (event.key.keysym.sym == SDLK_F11)
		SDL_SetRelativeMouseMode(SDL_FALSE);
	if (event.key.keysym.sym == SDLK_TAB)
	{
		if (g_objects_tab_pressed)
			interface->current_instance_id++;
		if (g_camera_tab_pressed)
			interface->current_light_id++;
	}
	return (0);
}

static int			catch_keydown_02(t_rt *rt, t_interface *interface,
									SDL_Event event)
{
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
	return (catch_keydown_03(rt, interface, event));
}

int					catch_keydown_01(t_rt *rt, t_interface *interface,
							SDL_Event event)
{
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
	return (catch_keydown_02(rt, interface, event));
}
