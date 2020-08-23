/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 10:51:39 by alex              #+#    #+#             */
/*   Updated: 2020/08/23 19:09:29 by user             ###   ########.fr       */
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

	// if (rt->sdl.event.type == SDL_MOUSEMOTION)
	// {
	// 	rt->direction.x = rt->sdl.event.motion.x;
	// 	rt->direction.y = rt->sdl.event.motion.y;
	// 	main_gui(rt,all_rect, color);
	// }
	if (is_press_button(rt, &all_rect->tab_main_button))
	{
		main_gui(rt, all_rect, color);
		draw_main(rt, all_rect, color);

		render_tab_bar(rt, &color->tab_pressed_color, &all_rect->tab_main_button, WIDTH - WIDTH_MENU / 2 - WIDTH_MENU / 4, "MAIN");
		render_tab_bar(rt, &color->title_text_color, &all_rect->tab_render_button, WIDTH - WIDTH_MENU / 2 + WIDTH_MENU / 4, "RENDER");
		hlineRGBA(rt->sdl.render, WIDTH_OFFSET + MARGIN, WIDTH - WIDTH_MENU / 2, (FONT_TITLE_SIZE + MARGIN_Y) * 4 - MARGIN_Y,
		color->tab_pressed_color.r, color->tab_pressed_color.g, color->tab_pressed_color.b, 255);
		hlineRGBA(rt->sdl.render, WIDTH - WIDTH_MENU / 2, WIDTH - MARGIN, (FONT_TITLE_SIZE + MARGIN_Y) * 4 - MARGIN_Y, 217, 217, 217, 255);
	}
	if (is_press_button(rt, &all_rect->tab_render_button))
	{
		main_gui(rt,all_rect, color);

		render_tab_bar(rt, &color->title_text_color, &all_rect->tab_main_button, WIDTH - WIDTH_MENU / 2 - WIDTH_MENU / 4, "MAIN");
		render_tab_bar(rt, &color->tab_pressed_color, &all_rect->tab_render_button, WIDTH - WIDTH_MENU / 2 + WIDTH_MENU / 4, "RENDER");
		hlineRGBA(rt->sdl.render, WIDTH - WIDTH_MENU / 2, WIDTH - MARGIN, (FONT_TITLE_SIZE + MARGIN_Y) * 4 - MARGIN_Y,
		color->tab_pressed_color.r, color->tab_pressed_color.g, color->tab_pressed_color.b, 255);
		hlineRGBA(rt->sdl.render, WIDTH_OFFSET + MARGIN, WIDTH - WIDTH_MENU / 2, (FONT_TITLE_SIZE + MARGIN_Y) * 4 - MARGIN_Y, 217, 217, 217, 255);
	}
	if (is_press_button(rt, &all_rect->color_picker_button))
	{
		main_gui(rt,all_rect, color);
		draw_gradient(rt->sdl.render, &all_rect->color_picker, color->preground, color->title_text_color);
	}
	if (is_press_button(rt, &all_rect->checkbox_button))
	{
		check_box_texture = IMG_LoadTexture(rt->sdl.render, "images/checkbox.png");
		SDL_RenderCopy(rt->sdl.render, check_box_texture, NULL, NULL);;
		SDL_RenderPresent(rt->sdl.render);
	}
}
