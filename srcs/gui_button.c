/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_button.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 10:52:14 by alex              #+#    #+#             */
/*   Updated: 2020/10/13 11:03:26 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "rt.h"

void	draw_button_rect(t_window *win, SDL_Rect *rect, char *str, t_colors *color)
{
	SDL_Texture *text;
	int w;
	int h;

	SDL_SetRenderDrawColor(win->renderer, 100, 100, 100, 255);
	SDL_RenderFillRect(win->renderer, rect);
	SDL_SetRenderDrawColor(win->renderer, 255, 0, 0, 255);
	SDL_RenderDrawRect(win->renderer, rect);
	text = render_text(str, "font/Title.ttf",
		color->black_color, FONT_TEXT, win->renderer);
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
		color->black_color, FONT_TEXT, win->renderer);
	SDL_QueryTexture(text, NULL, NULL, &w, &h);
	render_rect(text, win->renderer, rect->x + MARGIN, rect->y + rect->h / 2 - h / 2, w, h);
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
		color->black_color, FONT_SUBTITLE_SIZE, win->renderer);
		SDL_QueryTexture(text, NULL, NULL, &w, &h);
		render_rect(text, win->renderer, rect->x + MARGIN, rect->y, w, h);
	}
	button.x = rect->x + MARGIN;
	button.y = rect->y + h;
	button.w = (rect->w - MARGIN * 2) / 3;
	button.h = rect->h;
	draw_button_rect(win, &button, "2.30",color);
	draw_text(win, &button, "x:", color);
	button.x += button.w + MARGIN;
	button.w = (rect->w - MARGIN * 4) / 3;
	draw_button_rect(win, &button, "3.43",color);
	draw_text(win, &button, "y:", color);
	button.x += button.w + MARGIN;
	button.w = (rect->w - MARGIN * 6) / 3;
	draw_button_rect(win, &button, "4.54",color);
	draw_text(win, &button, "z:", color);
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
		color->black_color, FONT_SUBTITLE_SIZE, win->renderer);
		SDL_QueryTexture(text, NULL, NULL, &w, &h);
		render_rect(text, win->renderer, rect->x + MARGIN, rect->y, w, h);
		SDL_DestroyTexture(text);
	}
	button.x = rect->x + w + MARGIN + 50;
	button.y = rect->y;
	button.w = rect->w - w - MARGIN * 2 - 50;
	button.h = rect->h;
	draw_button_rect(win, &button, "fish eye", color);
}
