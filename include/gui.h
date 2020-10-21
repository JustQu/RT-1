/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 17:10:47 by alex              #+#    #+#             */
/*   Updated: 2020/10/21 15:27:12 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef GUI_H
# define GUI_H

#ifndef __DARWIN__
# include <SDL2/SDL_render.h>
# include <SDL2/SDL_image.h>
# include <SDL2/SDL_ttf.h>
# include <SDL2/SDL2_gfxPrimitives.h>
#else
# include <SDL_render.h>
# include <SDL_image.h>
# include <SDL_ttf.h>
# include <SDL2_gfxPrimitives.h>
#endif

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

int	camera_tab_pressed;
int	objects_tab_pressed;
int	options_tab_pressed;
int	type_pressed;
int	inside_is_pressed;
int	save_image;

typedef struct		s_vector
{
	float			x;
	float			y;
	float			z;
	float			l;
}					t_vector;

typedef struct		s_sdl
{
	SDL_Window		*win;
	SDL_Renderer	*render;
	SDL_Event		event;
}					t_sdl;

typedef struct      s_rect
{
    SDL_Rect        rect;
    int             min_width;
    int             min_height;
    int             max_width;
    int             max_height;
}                   t_rect;

typedef struct      s_gui
{
    SDL_Texture     *texture;
    t_rect          rect;
    SDL_Color       color;
	t_object_info	*current_object;
}                   t_gui;

// typedef struct	s_pressed
// {
// 	int 		shadow;
// 	int			ambient;
// 	int			specular;
// 	int			and_more;
// 	int			render_tab;
// 	int			main_tab;
// }				t_pressed;

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

typedef struct 	s_colors
{
	SDL_Color	background_color;
	SDL_Color	border_color;
	SDL_Color	inside_color;
	SDL_Color	text_color;
}				t_colors;

/* gui_init */
void	init_colors(t_colors *color);
void	init_rect(t_all_rect *rect, t_window *win);

/* gui_init end */

/* primirives */
void	draw_hline(t_window *win, int x1, int x2, int y, SDL_Color *color);
void	draw_vline(t_window *win, int x1, int y2, int y, SDL_Color *color);

/* end primitives */
int				main_gui(t_window *win, t_rt *rt, t_all_rect *all_rect, t_colors *color);
void 			render_texture(SDL_Texture *tex, SDL_Renderer *ren,
								int x, int y);
SDL_Texture*	load_texture(char *str, SDL_Renderer *renderer);
void			render_rect(SDL_Texture *texture, SDL_Renderer *renderer,
							int x, int y, int w, int h);
void			draw_fill_rect(t_window *win, SDL_Rect *background, SDL_Color *color);
SDL_Texture*	render_text(char *message, char *fontFile, SDL_Color color,
							int fontSize,	SDL_Renderer *renderer);
/* gui_button.c */
void	draw_button(t_rt *rt, t_window *win,
			SDL_Rect *rect, char *str, t_colors *color);
void			draw_button_xyz(t_window *win, SDL_Rect *rect,
					char *str, char **str_xyz, t_colors *color);
void			draw_checkbox(t_rt *rt, SDL_Rect *rect, char *str,
								t_colors *color);
void			draw_button_choise(t_window *win, SDL_Rect *rect,
					char **str_xyz, t_colors *color, int size);
void			draw_is_pressed_button(t_window *win, SDL_Rect *rect,
					char *str, t_colors *color);
/* end gui_button.c */

void			gui_tab_bar(t_window *win, t_rt *rt, t_all_rect *rect, t_colors *color);
void			draw_title_ray_tracing(t_window *win, SDL_Color *color);
/* gui_utils */

SDL_Rect		init_rect_size(int x, int y, int w, int h);
SDL_Color		init_color(int r, int g, int b, int a);
void			save_image_func(t_window *win);

/* gui_utils end */
#endif
