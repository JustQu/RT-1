/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 23:21:28 by dmelessa          #+#    #+#             */
/*   Updated: 2020/10/18 18:03:55 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "interface.h"
# include "rt.h"
#include "gui.h"

int		is_press_button(SDL_Event *event, SDL_Rect *rect)
{
	if (event->motion.y >= rect->y
		&& event->motion.y <= rect->y + rect->h
		&& event->motion.x >= rect->x && event->motion.x <= rect->x + rect->w)
		return (1);
	else
		return (0);
}

void	catch_is_pressed(SDL_Event *event, SDL_Rect *rect, int size)
{
	SDL_Rect	button;
	int i;

	button.x = rect->x;
	button.y = rect->y;
	button.w = rect->w;
	button.h = rect->h / size;
	i = 0;
	while(i < size)
	{
		if (is_press_button(event, &button))
		{
			inside_is_pressed = i;
			printf("\n%d position\n", i);
		}
		button.y += button.h;
		button.h = rect->h / size;
		i++;
	}
}

void	catch_tab_bar(SDL_Event *event, t_all_rect *rect)
{
	if (is_press_button(event, &rect->type_button) && objects_tab_pressed == 1)
	{
		type_pressed ^= 1;
	}
	else if ((type_pressed == 1 && is_press_button(event, &rect->type_choise_rect)) && objects_tab_pressed == 1)
	{
		catch_is_pressed(event, &rect->type_choise_rect, 3);
	}
	else if (is_press_button(event, &rect->type_button) && options_tab_pressed == 1)
	{
		type_pressed ^= 1;
	}
	else if ((type_pressed == 1 && is_press_button(event, &rect->type_choise_rect)) && options_tab_pressed == 1)
	{
		catch_is_pressed(event, &rect->type_choise_rect, 2);
	}
	else if (is_press_button(event, &rect->type_button) && camera_tab_pressed == 1)
	{
		type_pressed ^= 1;
	}
	else if ((type_pressed == 1 && is_press_button(event, &rect->type_choise_rect)) && camera_tab_pressed == 1)
	{
		catch_is_pressed(event, &rect->type_choise_rect, 4);
	}
	else if (type_pressed == 1)
	{
		type_pressed = 0;
	}
	else
	{
		if (is_press_button(event, &rect->tab_camera_button))
		{
			camera_tab_pressed = 1;
			objects_tab_pressed = 0;
			options_tab_pressed = 0;
		}
		if (is_press_button(event, &rect->tab_objects_button))
		{
			camera_tab_pressed = 0;
			objects_tab_pressed = 1;
			options_tab_pressed = 0;
		}
		if (is_press_button(event, &rect->tab_options_button))
		{
			camera_tab_pressed = 0;
			objects_tab_pressed = 0;
			options_tab_pressed = 1;
		}
	}
}

int catch_event(t_rt *rt, t_window *win, t_all_rect *rect, t_colors *color)
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
				// win->width = event.window.data1;
				// win->height = event.window.data2;
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
			else if (event.key.keysym.sym == SDLK_p)
			{
				rt->options.shadows = !rt->options.shadows;
			}
		}
		if (event.type == SDL_KEYUP)
		{
		}
		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			catch_tab_bar(&event, rect);
			printf("Mouse press at %d %d", event.button.x, event.button.y);
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
