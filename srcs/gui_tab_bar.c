/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_tab_bar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 18:03:59 by user              #+#    #+#             */
/*   Updated: 2020/08/23 18:53:51 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "rt.h"

SDL_Texture	*create_tab_subtitles(t_rt *rt, char *str, SDL_Color *color)
{
	SDL_Texture *text;

	text = render_text(str, "font/Title.ttf",
	*color, FONT_TITLE_SIZE, rt->sdl.render);
	return (text);
}

void	render_tab_bar(t_rt *rt, SDL_Color *color, SDL_Rect *rect, int x, char *str)
{
	SDL_Texture *text;
	int w;
	int h;

	text = create_tab_subtitles(rt, str, color);
	SDL_QueryTexture(text, NULL, NULL, &w, &h);
	render_texture(text, rt->sdl.render, x - w / 2, rect->h - h);
}

void	gui_tab_bar(t_rt *rt, t_all_rect *rect, t_colors *color)
{
	roundedBoxRGBA(rt->sdl.render, rect->tab_main_button.x, rect->tab_main_button.y, rect->tab_main_button.w, rect->tab_main_button.h, 1, color->background_color.r, color->background_color.r, color->background_color.r, 255);
	roundedBoxRGBA(rt->sdl.render, rect->tab_render_button.x, rect->tab_render_button.y, rect->tab_render_button.w, rect->tab_render_button.h, 1, color->background_color.r, color->background_color.r, color->background_color.r, 255);

	render_tab_bar(rt, &color->title_text_color, &rect->tab_main_button, WIDTH - WIDTH_MENU / 2 - WIDTH_MENU / 4, "MAIN");
	render_tab_bar(rt, &color->title_text_color, &rect->tab_render_button, WIDTH - WIDTH_MENU / 2 + WIDTH_MENU / 4, "RENDER");

	// text = create_tab_subtitles(rt, "RENDERER", &color->subtitle_xyz_color);
	// SDL_QueryTexture(text, NULL, NULL, &w, &h);
	// render_texture(text, rt->sdl.render, WIDTH - WIDTH_MENU / 2 + WIDTH_MENU / 4 - w / 2, rect->tab_main_button.h - h);

	// create_tab_subtitles(rt, &rect->tab_main_button, "Main", &color->subtitle_xyz_color);
	// create_tab_subtitles(rt, &rect->tab_render_button, "Render", &color->subtitle_xyz_color);
	// create_tab_subtitles(rt, &rect->tab_other_button, "Other", &color->subtitle_xyz_color);
}
