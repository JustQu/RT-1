/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_button.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 10:52:14 by alex              #+#    #+#             */
/*   Updated: 2020/11/28 11:27:22 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "rt.h"

void			draw_is_pressed_button(t_window *win, SDL_Rect *rect,
					char *str, t_colors *color)
{
	SDL_Texture	*text;
	SDL_Rect	button;
	SDL_Rect	ptr;
	int			w;
	int			h;

	button.x = rect->x + MARGIN;
	button.y = rect->y;
	button.w = rect->w - MARGIN * 2 - 150;
	button.h = rect->h;
	SDL_SetRenderDrawColor(win->renderer, color->border_color.r,
		color->border_color.g, color->border_color.b, color->border_color.a);
	SDL_RenderFillRect(win->renderer, &button);
	SDL_SetRenderDrawColor(win->renderer, color->border_color.r,
		color->border_color.g, color->border_color.b, color->border_color.a);
	SDL_RenderDrawRect(win->renderer, &button);
	g_font_size = FONT_TEXT;
	text = render_text(str, "font/Title.ttf",
		color->text_color, win->renderer);
	SDL_QueryTexture(text, NULL, NULL, &w, &h);
	ptr.x = button.x + button.w / 2 - w / 2;
	ptr.y = button.y + button.h / 2 - h / 2;
	ptr.w = w;
	ptr.h = h;
	render_rect(text, win->renderer, &ptr);
}

void			draw_button_rect(t_window *win, SDL_Rect *rect,
				char *str, t_colors *color)
{
	SDL_Texture	*text;
	SDL_Rect	ptr;
	int			w;
	int			h;

	SDL_SetRenderDrawColor(win->renderer, color->inside_color.r,
	color->inside_color.g, color->inside_color.b, color->inside_color.a);
	SDL_RenderFillRect(win->renderer, rect);
	SDL_SetRenderDrawColor(win->renderer, color->border_color.r,
	color->border_color.g, color->border_color.b, color->border_color.a);
	SDL_RenderDrawRect(win->renderer, rect);
	g_font_size = FONT_TEXT;
	text = render_text(str, "font/Title.ttf",
		color->text_color, win->renderer);
	SDL_QueryTexture(text, NULL, NULL, &w, &h);
	minimum_rect_size(w, h, rect, &ptr);
	render_rect(text, win->renderer, &ptr);
}

void			draw_button_rgb(t_window *win, SDL_Rect *rect,
					char **str_xyz, t_colors *color)
{
	SDL_Texture	*text;
	SDL_Rect	button;
	SDL_Rect	ptr;
	int			w;
	int			h;

	g_font_size = FONT_SUBTITLE_SIZE;
	text = render_text(str_xyz[0], "font/Title.ttf",
	color->text_color, win->renderer);
	SDL_QueryTexture(text, NULL, NULL, &w, &h);
	ptr = init_rect_size(win->width - win->width / 4 + MARGIN,
		rect->y, w, h);
	render_rect(text, win->renderer, &ptr);
	button = init_rect_size(win->width - win->width / 4 + MARGIN,
		rect->y + h, (rect->w - MARGIN * 2) / 3, rect->h);
	draw_button_rect(win, &button, str_xyz[1], color);
	draw_text(win, &button, "r :", color);
	button.x += button.w + MARGIN;
	button.w = (rect->w - MARGIN * 4) / 3;
	draw_button_rect(win, &button, str_xyz[2], color);
	draw_text(win, &button, "g :", color);
	button.x += button.w + MARGIN;
	button.w = (rect->w - MARGIN * 6) / 3;
	draw_button_rect(win, &button, str_xyz[3], color);
	draw_text(win, &button, "b :", color);
}

void			draw_button_xyz(t_window *win, SDL_Rect *rect,
					char **str_xyz, t_colors *color)
{
	SDL_Texture	*text;
	SDL_Rect	button;
	SDL_Rect	ptr;
	int			w;
	int			h;

	g_font_size = FONT_SUBTITLE_SIZE;
	text = render_text(str_xyz[0], "font/Title.ttf",
	color->text_color, win->renderer);
	SDL_QueryTexture(text, NULL, NULL, &w, &h);
	ptr = init_rect_size(win->width - win->width / 4 + MARGIN,
		rect->y, w, h);
	render_rect(text, win->renderer, &ptr);
	button = init_rect_size(win->width - win->width / 4 + MARGIN,
		rect->y + h, (rect->w - MARGIN * 2) / 3, rect->h);
	draw_button_rect_xyz(win, &button, str_xyz[1], color);
	draw_text(win, &button, "x :", color);
	button.x += button.w + MARGIN;
	button.w = (rect->w - MARGIN * 4) / 3;
	draw_button_rect_xyz(win, &button, str_xyz[2], color);
	draw_text(win, &button, "y :", color);
	button.x += button.w + MARGIN;
	button.w = (rect->w - MARGIN * 6) / 3;
	draw_button_rect_xyz(win, &button, str_xyz[3], color);
	draw_text(win, &button, "z :", color);
}

void			draw_button(t_window *win, SDL_Rect *rect,
					char **str, t_colors *color)
{
	SDL_Texture	*text;
	SDL_Rect	button;
	SDL_Rect	ptr;
	int			w;
	int			h;

	if (str != 0)
	{
		g_font_size = FONT_SUBTITLE_SIZE;
		text = render_text(str[0], "font/Title.ttf",
		color->text_color, win->renderer);
		SDL_QueryTexture(text, NULL, NULL, &w, &h);
		ptr = init_rect_size(win->width - win->width / 4 + MARGIN,
			rect->y, w, h);
		render_rect(text, win->renderer, &ptr);
		SDL_DestroyTexture(text);
	}
	if (w <= win->width && str[1] != NULL)
	{
		button = init_rect_size(rect->x + MARGIN, rect->y,
			rect->w - MARGIN * 2 - 150, rect->h);
		draw_button_rect(win, &button, str[1], color);
	}
}
