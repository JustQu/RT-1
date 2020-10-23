/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_button.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 10:52:14 by alex              #+#    #+#             */
/*   Updated: 2020/10/21 17:24:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "rt.h"

void	draw_is_pressed_button(t_window *win, SDL_Rect *rect, char *str, t_colors *color)
{
	SDL_Texture *text;
	SDL_Rect	button;
	int w;
	int h;

	button.x = rect->x + MARGIN;
	button.y = rect->y;
	button.w = rect->w - MARGIN * 2 - 150;
	button.h = rect->h;
	SDL_SetRenderDrawColor(win->renderer, color->border_color.r, color->border_color.g, color->border_color.b, color->border_color.a);
	SDL_RenderFillRect(win->renderer, &button);
	SDL_SetRenderDrawColor(win->renderer, color->border_color.r, color->border_color.g, color->border_color.b, color->border_color.a);
	SDL_RenderDrawRect(win->renderer, &button);
	text = render_text(str, "font/Title.ttf",
		color->text_color, FONT_TEXT, win->renderer);
	SDL_QueryTexture(text, NULL, NULL, &w, &h);
	render_rect(text, win->renderer, button.x + button.w / 2 - w / 2,
		button.y + button.h / 2 - h / 2, w, h);
}

void	draw_button_rect(t_window *win, SDL_Rect *rect, char *str, t_colors *color)
{
	SDL_Texture *text;
	// SDL_Rect	border;
	int w;
	int h;

	// border.x = rect->x + 1;
	// border.y = rect->y + 1;
	// border.h = rect->h;
	// border.w = rect->w;
	SDL_SetRenderDrawColor(win->renderer, color->inside_color.r, color->inside_color.g, color->inside_color.b, color->inside_color.a);
	SDL_RenderFillRect(win->renderer, rect);
	SDL_SetRenderDrawColor(win->renderer, color->border_color.r, color->border_color.g, color->border_color.b, color->border_color.a);
	SDL_RenderDrawRect(win->renderer, rect);
	// int i = 0;
	// while(i < 1)
	// {
	// 	SDL_SetRenderDrawColor(win->renderer, 0, 0, 0, 255);
	// 	SDL_RenderDrawRect(win->renderer, &border);
	// 	border.x += 1;
	// 	border.y += 1;
	// 	border.h -= 2;
	// 	border.w -= 2;
	// 	i += 1;
	// }
	text = render_text(str, "font/Title.ttf",
		color->text_color, FONT_TEXT, win->renderer);
	SDL_QueryTexture(text, NULL, NULL, &w, &h);
	render_rect(text, win->renderer, rect->x + rect->w / 2 - w / 2,
		rect->y + rect->h / 2 - h / 2, w, h);
}

/**
** @brief draw text with parametrs
**
** @param str - text
** @param rect - rectangle of text
** @param color - color text
** @return ** void
*/
void	draw_text(t_window *win, SDL_Rect *rect, char *str, t_colors *color)
{
	SDL_Texture *text;
	int w;
	int h;

	text = render_text(str, "font/Title.ttf",
		color->text_color, FONT_TEXT, win->renderer);
	SDL_QueryTexture(text, NULL, NULL, &w, &h);
	render_rect(text, win->renderer, rect->x + MARGIN, rect->y + rect->h / 2 - h / 2, w, h);
}

void	draw_button_choise(t_window *win, SDL_Rect *rect, char **str_xyz, t_colors *color, int size)
{
	SDL_Rect	button;
	int i;

	button.x = rect->x;
	button.y = rect->y;
	button.w = rect->w;
	button.h = rect->h / size;
	i = 0;
	while (i < size)
	{
		draw_button_rect(win, &button, str_xyz[i],color);
		button.y += button.h - 1;
		button.h = rect->h / size + 1;
		i++;
	}
}

void	draw_button_xyz(t_window *win, SDL_Rect *rect, char *str, char **str_xyz, t_colors *color)
{
	SDL_Texture *text;
	SDL_Rect	button;
	int w;
	int h;

	if (str != 0)
	{
		text = render_text(str, "font/Title.ttf",
		color->text_color, FONT_SUBTITLE_SIZE, win->renderer);
		SDL_QueryTexture(text, NULL, NULL, &w, &h);
		render_rect(text, win->renderer, win->width - win->width / 4 + MARGIN, rect->y, w, h);
	}
	button.x = win->width - win->width / 4 + MARGIN;
	button.y = rect->y + h;
	button.w = (rect->w - MARGIN * 2) / 3;
	button.h = rect->h;
	draw_button_rect(win, &button, str_xyz[0], color);
	draw_text(win, &button, "x :", color);
	button.x += button.w + MARGIN;
	button.w = (rect->w - MARGIN * 4) / 3;
	draw_button_rect(win, &button, str_xyz[1], color);
	draw_text(win, &button, "y :", color);
	button.x += button.w + MARGIN;
	button.w = (rect->w - MARGIN * 6) / 3;
	draw_button_rect(win, &button, str_xyz[2], color);
	draw_text(win, &button, "z :", color);
}

void	draw_button(t_rt *rt, t_window *win, SDL_Rect *rect, char *str, t_colors *color)
{
	rt = rt; // change;
	SDL_Texture *text;
	SDL_Rect	button;
	int w;
	int h;

	if (str != 0)
	{
		text = render_text(str, "font/Title.ttf",
		color->text_color, FONT_SUBTITLE_SIZE, win->renderer);
		SDL_QueryTexture(text, NULL, NULL, &w, &h);
		render_rect(text, win->renderer, win->width - win->width / 4 + MARGIN, rect->y, w, h);
		SDL_DestroyTexture(text);
	}
	if (w <= win->width)
	{
		button.x = rect->x + MARGIN;
		button.y = rect->y;
		button.w = rect->w - MARGIN * 2 - 150;
		button.h = rect->h;
		draw_button_rect(win, &button, "Your text", color);
	}
}
