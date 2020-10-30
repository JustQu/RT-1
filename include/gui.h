/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 17:10:47 by alex              #+#    #+#             */
/*   Updated: 2020/10/30 21:15:22 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_H
# define GUI_H

# ifndef __DARWIN__
#  include <SDL2/SDL_render.h>
#  include <SDL2/SDL_image.h>
#  include <SDL2/SDL_ttf.h>
#  include <SDL2/SDL2_gfxPrimitives.h>
# else
#  include <SDL_render.h>
#  include <SDL_image.h>
#  include <SDL_ttf.h>
#  include <SDL2_gfxPrimitives.h>
# endif

# include "instance_manager.h"
# include "window.h"

# define WIDTH_MENU DEFAULT_WIDTH / 4
# define WIDTH_OFFSET DEFAULT_WIDTH - DEFAULT_WIDTH / 4
# define MARGIN 5
# define MARGIN_Y 10
# define FONT_TITLE_SIZE 22
# define FONT_SUBTITLE_SIZE 20
# define FONT_TEXT 12
# define COLOR_STEP 100
# define HEIGHT_BUTTON 30
# define SPACER		150

typedef struct s_rt		t_rt;
typedef struct s_vector	t_vector;

int				g_camera_tab_pressed;
int				g_objects_tab_pressed;
int				g_options_tab_pressed;
int				g_type_pressed;
int				g_inside_is_pressed;
int				g_save_image;
int				g_size;
int				g_font_size;

typedef struct	s_all_rect
{
	SDL_Rect	background;
	SDL_Rect	tab_camera_button;
	SDL_Rect	tab_objects_button;
	SDL_Rect	tab_options_button;
	SDL_Rect	type_button;
	SDL_Rect	position_button;
	SDL_Rect	direction_button;
	SDL_Rect	radius_button;
	SDL_Rect	rotate_button;
	SDL_Rect	color_button;
	SDL_Rect	diffuse_button;
	SDL_Rect	reflection_button;
	SDL_Rect	alpha_button;
	SDL_Rect	samplers_button;
	SDL_Rect	deep_button;
	SDL_Rect	background_button;
	SDL_Rect	resolution_button;
	SDL_Rect	type_choise_rect;
	SDL_Rect	save_img_button;
}				t_all_rect;

typedef struct	s_colors
{
	SDL_Color	background_color;
	SDL_Color	border_color;
	SDL_Color	inside_color;
	SDL_Color	text_color;
}				t_colors;

void			init_colors(t_colors *color);
void			init_rect(t_all_rect *rect, t_window *win);
void			gui(t_window *win, t_rt *rt, t_all_rect *all_rect,
					t_colors *color);
void			render_texture(SDL_Texture *tex, SDL_Renderer *ren,
								int x, int y);
SDL_Texture		*load_texture(char *str, SDL_Renderer *renderer);
void			render_rect(SDL_Texture *texture, SDL_Renderer *renderer,
							SDL_Rect *rect);
void			draw_fill_rect(t_window *win, SDL_Rect *background,
					SDL_Color *color);
SDL_Texture		*render_text(char *message, char *font_file, SDL_Color color,
							SDL_Renderer *renderer);
void			draw_button(t_window *win,
				SDL_Rect *rect, char **str, t_colors *color);
void			draw_button_xyz(t_window *win, SDL_Rect *rect,
					char **str_xyz, t_colors *color);
void			draw_checkbox(t_rt *rt, SDL_Rect *rect, char *str,
								t_colors *color);
void			draw_button_choise(t_window *win, SDL_Rect *rect,
					char **str_xyz, t_colors *color);
void			draw_is_pressed_button(t_window *win, SDL_Rect *rect,
					char *str, t_colors *color);
void			gui_tab_bar(t_window *win, t_rt *rt, t_all_rect *rect,
					t_colors *color);
void			draw_title_ray_tracing(t_window *win, SDL_Color *color);
void			render_tab_bar(t_window *win, SDL_Color *color,
					SDL_Rect *rect, char *str);
SDL_Rect		init_rect_size(int x, int y, int w, int h);
SDL_Color		init_color(int r, int g, int b, int a);
void			save_image_func(t_window *win);
SDL_Texture		*create_tab_subtitles(t_window *win, char *str,
					SDL_Color *color);
char			*itoa_float(float num);
void			get_material_data(int ptr, char *string,
					char **str);
void			get_camera_type_data(int ptr, char *string,
					char **str);
void			get_str_data(char *str1, char *string, char **str);
void			get_float_data(float ptr, char *string, char **str);
void			get_float4_data(cl_float4 ptr, char *string, char **str);

#endif
