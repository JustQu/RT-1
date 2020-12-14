/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 23:21:28 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/13 20:54:42 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "rt.h"
#include "gui.h"
#include "keydown.h"

int				is_press_button(SDL_Event *event, SDL_Rect *rect)
{
	if (event->motion.y >= rect->y
		&& event->motion.y <= rect->y + rect->h
		&& event->motion.x >= rect->x && event->motion.x <= rect->x + rect->w)
		return (1);
	else
		return (0);
}

void			catch_tab_bar(SDL_Event *event, t_all_rect *rect)
{
	if (is_press_button(event, &rect->title_button)
		|| event->key.keysym.sym == SDLK_m)
		g_show_gui ^= 1;
	if (is_press_button(event, &rect->save_img_button)
		&& g_camera_tab_pressed == 1)
		g_save_image = 1;
	if (is_press_button(event, &rect->tab_camera_button))
	{
		g_camera_tab_pressed = 1;
		g_objects_tab_pressed = 0;
		g_options_tab_pressed = 0;
	}
	if (is_press_button(event, &rect->tab_objects_button))
	{
		g_camera_tab_pressed = 0;
		g_objects_tab_pressed = 1;
		g_options_tab_pressed = 0;
	}
	if (is_press_button(event, &rect->tab_options_button))
	{
		g_camera_tab_pressed = 0;
		g_objects_tab_pressed = 0;
		g_options_tab_pressed = 1;
	}
}

static int		catch_window_event(t_rt *rt, t_window *win, SDL_Event event)
{
	if (rt->options.shadows >= 0)
		printf("unused parametre (rt)\n");
	if (event.window.event == SDL_WINDOWEVENT_SHOWN)
		;
	else if (event.window.event == SDL_WINDOWEVENT_HIDDEN)
		;
	else if (event.window.event == SDL_WINDOWEVENT_EXPOSED)
		;
	else if (event.window.event == SDL_WINDOWEVENT_MOVED)
		;
	else if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
		;
	else if (event.window.event == SDL_WINDOWEVENT_MINIMIZED)
		;
	else if (event.window.event == SDL_WINDOWEVENT_MAXIMIZED)
		;
	else if (event.window.event == SDL_WINDOWEVENT_CLOSE)
		return (1);
	else if (event.window.event == SDL_WINDOWEVENT_RESIZED)
	{
		win->width = event.window.data1;
		win->height = event.window.data2;
	}
	return (0);
}

static int		catch_keydown(t_rt *rt, t_interface *interface,
							SDL_Event event)
{
	if (event.key.keysym.sym == SDLK_ESCAPE)
		return (1);
	if (event.key.keysym.sym == SDLK_p)
		rt->options.shadows = !rt->options.shadows;
	if (event.key.keysym.sym == SDLK_r)
	{
		rt->options.reset = 1;
		rt->options.spp = NUM_SAMPLES;
	}
	if (event.key.keysym.sym == SDLK_w)
	{
		move_camera(&rt->scene.camera, 2, -0.1f);
		rt->options.reset = 1;
		rt->options.spp = NUM_SAMPLES;
	}
	if (event.key.keysym.sym == SDLK_s)
	{
		move_camera(&rt->scene.camera, 2, 0.1f);
		rt->options.reset = 1;
		rt->options.spp = NUM_SAMPLES;
	}
	return (catch_keydown_01(rt, interface, event));
}

int				catch_event(t_rt *rt, t_window *win, t_interface *interface)
{
	SDL_Event	event;

	if (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
			return (1);
		if (event.type == SDL_WINDOWEVENT)
			return (catch_window_event(rt, win, event));
		if (event.type == SDL_KEYDOWN)
		{
			return (catch_keydown(rt, interface, event));
		}
		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			//todo: translate window coordinates in image coordinates,
			//e.g. windos is 1200x600 and image is 1920x1080
			//then we need x * IMG_W/WIN_W and y * IMG_H/WIN_H
			catch_tab_bar(&event, &interface->gui.all_rect);
			printf("Mouse press at %d %d", event.button.x, event.button.y);
		}
		return (-1);
	}
	return (0);
}

//todo: translate window coordinates in image coordinates,
//e.g. windos is 1200x600 and image is 1920x1080
//then we need x * IMG_W/WIN_W and y * IMG_H/WIN_H
