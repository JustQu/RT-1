/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_utils_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 09:49:42 by alex              #+#    #+#             */
/*   Updated: 2020/12/06 16:34:45 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "rt.h"

void			draw_line(t_window *win, t_colors *color,
					SDL_Rect rect, SDL_Rect rect_2)
{
	if (win == NULL || color == NULL)
		rt_error("draw_line(): given NULL pointer");
	if (SDL_SetRenderDrawColor(win->renderer, color->text_color.r,
	color->text_color.g, color->text_color.b, color->text_color.a))
		rt_error("draw_line(): SDL_SetRenderDrawColor() error");
	if (SDL_RenderDrawLine(win->renderer, rect.x,
		rect_2.y - MARGIN_Y,
		rect_2.x + rect_2.w,
		rect_2.y - MARGIN_Y))
		rt_error("draw_line(): SDL_RenderDrawLine() error");
}

void			minimum_rect_size(int w, int h, SDL_Rect *rect, SDL_Rect *ptr)
{
	if (rect == NULL || ptr == NULL)
		rt_error("minimum_rect_size(): given NULL pointer");
	if (w <= rect->w)
	{
		ptr->x = rect->x + rect->w / 2 - w / 2;
		ptr->y = rect->y + rect->h / 2 - h / 2;
		ptr->w = w;
		ptr->h = h;
	}
	else
	{
		ptr->x = rect->x + 1;
		ptr->y = rect->y;
		ptr->w = rect->w - 2;
		ptr->h = rect->h / 2 + h;
	}
}

void			type_ambien_il(t_window *win, t_rt *rt,
					t_all_rect *rect, t_colors *color)
{
	char *str[4];

	if (win == NULL || rt == NULL || rect == NULL || color == NULL)
		rt_error("type_ambien_il(): given NULL pointer");
	if (rt->scene.ambient_light.type == 0)
	{
		get_float_data(1, "coefficient", str); // ambient coef
		draw_button(win, &rect->sixth_button, str, color);
		free_str(str);
	}
	if (rt->scene.ambient_light.type == 1)
	{
		get_float_data(1, "min_amount", str); // min amount
		draw_button(win, &rect->sixth_button, str, color);
		free_str(str);
	}
}

SDL_Texture		*create_tab_subtitles(t_window *win, char *str,
					SDL_Color *color)
{
	SDL_Texture	*text;

	if (win == NULL || str == NULL || color == NULL)
		rt_error("create_tab_subtitles(): given NULL pointer");
	g_font_size = FONT_SUBTITLE_SIZE;
	safe_call_ptr((text = render_text(str, "font/Title.ttf",
	*color, win->renderer)), "create_tab_subtitles(): text is NULL");
	return (text);
}

void			draw_button_rect_xyz(t_window *win, SDL_Rect *rect,
				char *str, t_colors *color)
{
	SDL_Texture	*text;
	SDL_Rect	ptr;
	int			w;
	int			h;

	if (win == NULL || rect == NULL || str == NULL || color == NULL)
		rt_error("draw_button_rect_xyz(): given NULL pointer");
	if (SDL_SetRenderDrawColor(win->renderer, color->inside_color.r,
	color->inside_color.g, color->inside_color.b, color->inside_color.a))
		rt_error("draw_button_rect_xyz(): SDL_SetRenderDrawColor() error");
	if (SDL_RenderFillRect(win->renderer, rect))
		rt_error("draw_button_rect_xyz(): SDL_RenderFillRect() error");
	if (SDL_SetRenderDrawColor(win->renderer, color->border_color.r,
	color->border_color.g, color->border_color.b, color->border_color.a))
		rt_error("draw_button_rect_xyz(): SDL_SetRenderDrawColor() error");
	if (SDL_RenderDrawRect(win->renderer, rect))
		rt_error("draw_button_rect_xyz(): SDL_RenderDrawRect() error");
	g_font_size = FONT_TEXT;
	safe_call_ptr((text = render_text(str, "font/Title.ttf",
		color->text_color, win->renderer)),
		"draw_button_rect_xyz(): text is NULL");
	if (SDL_QueryTexture(text, NULL, NULL, &w, &h))
		rt_error("draw_button_rect_xyz(): SDL_QueryTexture() error");
	ptr.x = rect->x + rect->w / 2 - w / 4;
	ptr.y = rect->y + rect->h / 2 - h / 2;
	ptr.w = w;
	ptr.h = h;
	render_rect(text, win->renderer, &ptr);
}
