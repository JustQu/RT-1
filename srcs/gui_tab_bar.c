/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_tab_bar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 18:03:59 by user              #+#    #+#             */
/*   Updated: 2020/10/15 13:27:10 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "rt.h"

SDL_Texture	*create_tab_subtitles(t_window *win, char *str, SDL_Color *color)
{
	SDL_Texture *text;

	text = render_text(str, "font/Title.ttf",
	*color, FONT_SUBTITLE_SIZE, win->renderer);
	return (text);
}

void	render_tab_bar(t_window *win, SDL_Color *color, SDL_Rect *rect, char *str)
{
	SDL_Texture *text;
	int w;
	int h;

	SDL_SetRenderDrawColor(win->renderer, 240, 240, 240, 255);
	SDL_RenderFillRect(win->renderer, rect);
	text = create_tab_subtitles(win, str, color);
	SDL_QueryTexture(text, NULL, NULL, &w, &h);
	if (w <= rect->w)
		render_rect(text, win->renderer, rect->x + (rect->w - w) / 2, rect->y + rect->h - h, w, h);
	else
		render_rect(text, win->renderer, rect->x, rect->y, rect->w, rect->h);

}

void	camera_tab(t_window *win, t_rt *rt, t_all_rect *rect, t_colors *color)
{
	char *str[2];

	str[0] = "3.12"; //change on data rt
	str[1] = "2.32";
	str[2] = "4.32";
	render_tab_bar(win, &color->border_color, &rect->tab_camera_button, "Camera");
	draw_hline(win, rect->tab_camera_button.x, rect->tab_camera_button.w,
		rect->tab_camera_button.y + rect->tab_camera_button.h, &color->border_color);
	draw_button(rt, win, &rect->type_button, "Type camera", color);
	if (type_pressed)
		draw_is_pressed_button(win, &rect->type_button, "Your text", color); //rt-type_camera
	draw_button_xyz(win, &rect->position_button, "Position", str, color);
	draw_button_xyz(win, &rect->direction_button, "Direction", str, color);
}

void	objects_tab(t_window *win, t_rt *rt, t_all_rect *rect, t_colors *color)
{
	char *str[2];

	str[0] = "3.12"; //change on data rt
	str[1] = "2.32";
	str[2] = "4.32";
	render_tab_bar(win, &color->border_color, &rect->tab_objects_button, "Objects");
	draw_hline(win, rect->tab_objects_button.x, rect->tab_objects_button.w,
		rect->tab_objects_button.y + rect->tab_objects_button.h, &color->border_color);
	draw_button(rt, win, &rect->type_button, "Material", color);
	draw_button_xyz(win, &rect->position_button, "Position", str, color);
	draw_button_xyz(win, &rect->direction_button, "Direction", str, color);
	draw_button(rt, win, &rect->radius_button, "Radius", color);
	draw_button(rt, win, &rect->rotate_button, "Rotate", color);
	draw_button(rt, win, &rect->color_button, "Color", color);
	draw_button(rt, win, &rect->diffuse_button, "Diffuse", color);
	draw_button(rt, win, &rect->reflection_button, "Reflection", color);
	draw_button(rt, win, &rect->alpha_button, "Alpha", color);
}

void	option_tab(t_window *win, t_rt *rt, t_all_rect *rect, t_colors *color)
{
	render_tab_bar(win, &color->border_color, &rect->tab_options_button, "Options");
	draw_hline(win, rect->tab_options_button.x, rect->tab_options_button.w,
		rect->tab_options_button.y + rect->tab_options_button.h, &color->border_color);
	draw_button(rt, win, &rect->type_button, "Type RT", color);
	draw_button(rt, win, &rect->samplers_button, "Samplers", color);
	draw_button(rt, win, &rect->deep_button, "Deep", color);
	draw_button(rt, win, &rect->background_button, "Background", color);
	draw_button(rt, win, &rect->resolution_button, "Resolution", color);
}

//todo: change rect on buttons, create button press inside
void	draw_inside_button(t_window *win, t_rt *rt, t_all_rect *rect, t_colors *color)
{
	char *str[4];

	str[0] = "type1"; //change on data rt
	str[1] = "type2";
	str[2] = "type3";
	str[3] = "type4";
	str[4] = NULL;
	if (type_pressed == 1)
	{
		SDL_SetRenderDrawColor(win->renderer, 250, 100, 100, 255);
		SDL_RenderFillRect(win->renderer, &rect->type_choise_rect);
		draw_button_choise(win, &rect->type_choise_rect, str, color, 4);
	}
}

void	gui_tab_bar(t_window *win, t_rt *rt, t_all_rect *rect, t_colors *color)
{
	draw_hline(win, rect->tab_camera_button.x, rect->tab_options_button.x + rect->tab_options_button.w,
				rect->tab_options_button.y + rect->tab_options_button.h, &color->inside_color);
	if (camera_tab_pressed == 1)
		camera_tab(win, rt, rect, color);
	else
		render_tab_bar(win, &color->text_color, &rect->tab_camera_button, "Camera");
	if (objects_tab_pressed == 1)
		objects_tab(win, rt, rect, color);
	else
		render_tab_bar(win, &color->text_color, &rect->tab_objects_button, "Objects");
	if (options_tab_pressed == 1)
		option_tab(win, rt, rect, color);
	else
		render_tab_bar(win, &color->text_color, &rect->tab_options_button, "Options");
	draw_inside_button(win, rt, rect, color);
}
