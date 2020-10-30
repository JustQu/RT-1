/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:54:26 by alex              #+#    #+#             */
/*   Updated: 2020/10/30 19:49:00 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "libft.h"

void			draw_text(t_window *win, SDL_Rect *rect,
					char *str, t_colors *color)
{
	SDL_Texture	*text;
	SDL_Rect	ptr;
	int			w;
	int			h;

	g_font_size = FONT_TEXT;
	text = render_text(str, "font/Title.ttf",
		color->text_color, win->renderer);
	SDL_QueryTexture(text, NULL, NULL, &w, &h);
	ptr.x = rect->x + MARGIN;
	ptr.y = rect->y + rect->h / 2 - h / 2;
	ptr.w = w;
	ptr.h = h;
	render_rect(text, win->renderer, &ptr);
}

char			*itoa_float(float num)
{
	char		*str1;
	char		*str2;
	char		*res;
	int			ptr;
	int			aftd;

	ptr = num;
	aftd = (num - ptr) * 1000;
	str1 = ft_itoa(ptr);
	str2 = ft_itoa(aftd);
	str1 = ft_strcat(str1, ".");
	res = ft_strcat(str1, str2);
	return (res);
}

void			draw_title_ray_tracing(t_window *win, SDL_Color *color)
{
	SDL_Texture	*rt_text;
	SDL_Rect	rect;
	int			w;
	int			h;

	g_font_size = FONT_TITLE_SIZE * 2;
	rt_text = render_text("Ray Tracing", "font/Title_font_CAT.ttf",
			*color, win->renderer);
	SDL_QueryTexture(rt_text, NULL, NULL, &w, &h);
	if (win->width / 4 >= w)
	{
		rect.x = (win->width - win->width / 4) + (win->width / 4 - w) / 2;
		rect.y = MARGIN_Y;
		rect.w = w;
		rect.h = h;
		render_rect(rt_text, win->renderer, &rect);
	}
	else
	{
		rect.x = (win->width - win->width / 4) + MARGIN;
		rect.y = MARGIN_Y;
		rect.w = win->width / 4 - MARGIN * 2;
		rect.h = h;
		render_rect(rt_text, win->renderer, &rect);
	}
}
