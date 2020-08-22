/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 10:51:39 by alex              #+#    #+#             */
/*   Updated: 2020/08/22 21:24:24 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "gui.h"

int		is_press_button(t_rt *rt, SDL_Rect *rect)
{
	if (rt->sdl.event.type == SDL_MOUSEBUTTONDOWN && rt->sdl.event.motion.y >= rect->y
		&& rt->sdl.event.motion.y <= rect->h
		&& rt->sdl.event.motion.x >= rect->x && rt->sdl.event.motion.x <= rect->w)
		return (1);
	else
		return (0);
}

void	mouse_move(t_rt *rt, t_all_rect *all_rect, t_colors *color)
{
	// t_sdl color_picker;
	SDL_Texture *check_box_texture;

	if (rt->sdl.event.type == SDL_MOUSEMOTION)
	{
		rt->direction.x = rt->sdl.event.motion.x;
		rt->direction.y = rt->sdl.event.motion.y;
		main_gui(rt,all_rect, color);
	}
	if (is_press_button(rt, &all_rect->color_picker_button))
	{
		// color_picker.win = SDL_CreateWindow("Color Picker", 0, HEIGHT - all_rect->color_picker.h, all_rect->color_picker.w, all_rect->color_picker.h, SDL_WINDOW_BORDERLESS);
		// if (color_picker.win == NULL)
		// 	printf("Error");
		// color_picker.render = SDL_CreateRenderer(color_picker.win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		// if (color_picker.render == NULL)
		// 	printf("Error");
		draw_gradient(rt->sdl.render, &all_rect->color_picker, color->preground, color->title_text_color);
		// SDL_RenderPresent(color_picker.render);
	}
	if (is_press_button(rt, &all_rect->checkbox_button))
	{
		check_box_texture = IMG_LoadTexture(rt->sdl.render, "images/checkbox.png");
		SDL_RenderCopy(rt->sdl.render, check_box_texture, NULL, NULL);;
		SDL_RenderPresent(rt->sdl.render);
	}
}
