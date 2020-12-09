/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:54:26 by alex              #+#    #+#             */
/*   Updated: 2020/12/08 18:29:15 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "libft.h"
#include "rt.h"

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
	char		*tmp;
	int			ptr;
	int			aftd;

	ptr = num;
	aftd = (num - ptr) * 1000;
	str1 = ft_itoa(ptr);
	str2 = ft_itoa(aftd);
	tmp = ft_strjoin(str1, ".");
	free(str1);
	str1 = ft_strjoin(tmp, str2);
	free(tmp);
	free(str2);
	return (str1);
}

void			draw_title_ray_tracing(t_window *win, SDL_Color *color)
{
	SDL_Texture	*rt_text;
	SDL_Rect	rect;
	int			w;
	int			h;

	if (win == NULL || color == NULL)
		rt_error("draw_title_ray_tracing(): given NULL pointer");
	g_font_size = FONT_TITLE_SIZE * 2;
	safe_call_ptr((rt_text = render_text("Ray Tracing", "font/Title_font_CAT.ttf",
		*color, win->renderer)),
		"draw_title_ray_tracing(): render_text() returned NULL");
	if (SDL_QueryTexture(rt_text, NULL, NULL, &w, &h))
		rt_error("draw_title_ray_tracing(): SDL_QueryTexture() error");
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

void			free_str(char *str[4])
{
	int i;

	i = 0;
	while (i <= 3)
	{
		if (str[i] != NULL)
			free(str[i]);
		i++;
	}
}

void			gui_disk_vision(t_window *win, t_rt *rt,
					t_all_rect *rect, t_colors *color)
{
	char		*str[4];

	if (win == NULL || rt == NULL || rect == NULL || color == NULL)
		rt_error("gui_disk_vision(): given NULL pointer");
	get_float_data(1,
		"Radius", str); // radius disk
	draw_button(win, &rect->fifth_button, str, color);
	free_str(str);
}
