/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_tab_bar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 18:03:59 by user              #+#    #+#             */
/*   Updated: 2020/10/10 14:59:27 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "rt.h"

void	color_tab_render(t_window *win, t_colors *color, t_all_rect *all_rect)
{
	// render_tab_bar(win, &color->title_text_color, &all_rect->tab_main_button, WIDTH - WIDTH_MENU / 2 - WIDTH_MENU / 4, "MAIN");
	// render_tab_bar(win, &color->tab_pressed_color, &all_rect->tab_render_button, WIDTH - WIDTH_MENU / 2 + WIDTH_MENU / 4, "RENDER");
	// hlineRGBA(rt->sdl.render, WIDTH - WIDTH_MENU / 2, WIDTH - MARGIN, (FONT_TITLE_SIZE + MARGIN_Y) * 4 - MARGIN_Y,
	// color->tab_pressed_color.r, color->tab_pressed_color.g, color->tab_pressed_color.b, 255);
	// hlineRGBA(rt->sdl.render, WIDTH_OFFSET + MARGIN, WIDTH - WIDTH_MENU / 2, (FONT_TITLE_SIZE + MARGIN_Y) * 4 - MARGIN_Y, 217, 217, 217, 255);
}

void	color_tab_main(t_window *win, t_colors *color, t_all_rect *all_rect)
{
	// render_tab_bar(win, &color->tab_pressed_color, &all_rect->tab_main_button, WIDTH - WIDTH_MENU / 2 - WIDTH_MENU / 4, "MAIN");
	// render_tab_bar(win, &color->title_text_color, &all_rect->tab_render_button, WIDTH - WIDTH_MENU / 2 + WIDTH_MENU / 4, "RENDER");
	// hlineRGBA(rt->sdl.render, WIDTH_OFFSET + MARGIN, WIDTH - WIDTH_MENU / 2, (FONT_TITLE_SIZE + MARGIN_Y) * 4 - MARGIN_Y,
	// color->tab_pressed_color.r, color->tab_pressed_color.g, color->tab_pressed_color.b, 255);
	// hlineRGBA(rt->sdl.render, WIDTH - WIDTH_MENU / 2, WIDTH - MARGIN, (FONT_TITLE_SIZE + MARGIN_Y) * 4 - MARGIN_Y, 217, 217, 217, 255);
}

SDL_Texture	*create_tab_subtitles(t_window *win, char *str, SDL_Color *color)
{
	SDL_Texture *text;

	text = render_text(str, "font/Lato-Bold.ttf",
	*color, FONT_SUBTITLE_SIZE, win->renderer);
	return (text);
}

void	render_tab_bar(t_window *win, SDL_Color *color, SDL_Rect *rect, char *str)
{
	SDL_Texture *text;
	int w;
	int h;

	SDL_SetRenderDrawColor(win->renderer, 0, 0, 0, 255);
	SDL_RenderFillRect(win->renderer, rect);
	text = create_tab_subtitles(win, str, color);
	SDL_QueryTexture(text, NULL, NULL, &w, &h);
	if (w <= rect->w)
		render_rect(text, win->renderer, rect->x + (rect->w - w) / 2, rect->y + rect->h - h, w, h);
	else
		render_rect(text, win->renderer, rect->x, rect->y, rect->w, rect->h);

}


/**
** @brief draw horizontal line
**
** @param x1 - start hline
** @param x2 - end hline (x1 + x2)
** @param y
** @return ** void
*/
void	draw_hline(t_window *win, int x1, int x2, int y, SDL_Color *color)
{
	SDL_SetRenderDrawColor(win->renderer, color->r, color->g, color->b, color->a);
	SDL_RenderDrawLine(win->renderer, x1, y,
			x1 + x2, y);
}

// todo - create camera, objects, options inside tab
void	gui_tab_bar(t_window *win, t_all_rect *rect, t_colors *color)
{
	if (camera_tab_pressed == 1)
	{
		render_tab_bar(win, &color->green_color, &rect->tab_camera_button, "Camera");
		draw_hline(win, rect->tab_camera_button.x, rect->tab_camera_button.w,
			rect->tab_camera_button.y + rect->tab_camera_button.h, &color->green_color);
	}
	else
		render_tab_bar(win, &color->border_color, &rect->tab_camera_button, "Camera");
	if (objects_tab_pressed == 1)
	{
		render_tab_bar(win, &color->green_color, &rect->tab_objects_button, "Objects");
		draw_hline(win, rect->tab_objects_button.x, rect->tab_objects_button.w,
			rect->tab_objects_button.y + rect->tab_objects_button.h, &color->green_color);
	}
	else
		render_tab_bar(win, &color->border_color, &rect->tab_objects_button, "Objects");
	if (options_tab_pressed == 1)
	{
		render_tab_bar(win, &color->green_color, &rect->tab_options_button, "Options");
		draw_hline(win, rect->tab_options_button.x, rect->tab_options_button.w,
			rect->tab_options_button.y + rect->tab_options_button.h, &color->green_color);
	}
	else
		render_tab_bar(win, &color->border_color, &rect->tab_options_button, "Options");
}
