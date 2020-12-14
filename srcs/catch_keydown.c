/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_keydown.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 08:22:49 by alex              #+#    #+#             */
/*   Updated: 2020/12/13 13:33:43 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "rt.h"
#include "gui.h"

//static int		catch_keydown_6(t_rt *rt, t_window *win, SDL_Event event)
//{
//	return (0);
//}
//
//static int		catch_keydown_5(t_rt *rt, t_window *win, SDL_Event event)
//{
//	return (0);
//}
//
//static int		catch_keydown_4(t_rt *rt, t_window *win, SDL_Event event)
//{
//	if (win->height >= 0)
//		printf("unused param catch keydown 4\n");
//	if (event.key.keysym.sym == SDLK_LEFT)
//	{
//		rotate_camera(&rt->scene.camera, 1, -1.0f);
//		rt->options.reset = 1;
//		rt->options.spp = NUM_SAMPLES;
//	}
//	if (event.key.keysym.sym == SDLK_RIGHT)
//	{
//		rotate_camera(&rt->scene.camera, 1, 1.0f);
//		rt->options.reset = 1;
//		rt->options.spp = NUM_SAMPLES;
//	}
//	if (event.key.keysym.sym == SDLK_q)
//	{
//		rotate_camera(&rt->scene.camera, 2, -1.0f);
//		rt->options.reset = 1;
//		rt->options.spp = NUM_SAMPLES;
//	}
//	if (event.key.keysym.sym == SDLK_e)
//	{
//		rotate_camera(&rt->scene.camera, 2, 1.0f);
//		rt->options.reset = 1;
//		rt->options.spp = NUM_SAMPLES;
//	}
//	return (0);
//}
//
//static int		catch_keydown_3(t_rt *rt, t_window *win, SDL_Event event)
//{
//	if (event.key.keysym.sym == SDLK_LCTRL)
//	{
//		move_camera(&rt->scene.camera, 1, -0.1f);
//		rt->options.reset = 1;
//		rt->options.spp = NUM_SAMPLES;
//	}
//	if (event.key.keysym.sym == SDLK_DOWN)
//	{
//		rotate_camera(&rt->scene.camera, 0, 1.0f);
//		rt->options.reset = 1;
//		rt->options.spp = NUM_SAMPLES;
//	}
//	if (event.key.keysym.sym == SDLK_UP)
//	{
//		rotate_camera(&rt->scene.camera, 0, -1.0f);
//		rt->options.reset = 1;
//		rt->options.spp = NUM_SAMPLES;
//	}
//	catch_keydown_4(rt, win, event);
//	return (0);
//}
//
//int				catch_keydown_2(t_rt *rt, t_window *win, SDL_Event event)
//{
//	if (event.key.keysym.sym == SDLK_a)
//	{
//		move_camera(&rt->scene.camera, 0, -0.1f);
//		rt->options.reset = 1;
//		rt->options.spp = NUM_SAMPLES;
//	}
//	if (event.key.keysym.sym == SDLK_d)
//	{
//		move_camera(&rt->scene.camera, 0, 0.1f);
//		rt->options.reset = 1;
//		rt->options.spp = NUM_SAMPLES;
//	}
//	if (event.key.keysym.sym == SDLK_LSHIFT)
//	{
//		move_camera(&rt->scene.camera, 1, 0.1f);
//		rt->options.reset = 1;
//		rt->options.spp = NUM_SAMPLES;
//	}
//	if (event.key.keysym.sym == SDLK_F10)
//		SDL_SetRelativeMouseMode(SDL_TRUE);
//	if (event.key.keysym.sym == SDLK_F11)
//		SDL_SetRelativeMouseMode(SDL_FALSE);
//	catch_keydown_3(rt, win, event);
//	return (0);
//}
