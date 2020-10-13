/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 17:10:47 by alex              #+#    #+#             */
/*   Updated: 2020/10/13 15:21:22 by user             ###   ########.fr       */
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

typedef struct s_rt		t_rt;
typedef struct s_vector	t_vector;

int	camera_tab_pressed;
int	objects_tab_pressed;
int	options_tab_pressed;
int	type_pressed;

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
}				t_all_rect;

typedef struct 	s_colors
{
	SDL_Color	preground;
	SDL_Color	border_color;
	SDL_Color	title_text_color;
	SDL_Color	xyz_text_color;
	SDL_Color	subtitle_xyz_color;
	SDL_Color	background_color;
	SDL_Color	tab_pressed_color;
	SDL_Color	green_color;
	SDL_Color	red_color;
	SDL_Color	black_color;
}				t_colors;

// int				init_gui(t_gui *gui);

/* primirives */
void	draw_hline(t_window *win, int x1, int x2, int y, SDL_Color *color);
void	draw_vline(t_window *win, int x1, int x2, int y, SDL_Color *color);

/* end primitives */
int				main_gui(t_window *win, t_rt *rt, t_all_rect *all_rect, t_colors *color);
void			draw_background(t_rt *rt);
void 			render_texture(SDL_Texture *tex, SDL_Renderer *ren,
								int x, int y);
SDL_Texture*	load_texture(char *str, SDL_Renderer *renderer);
void			render_rect(SDL_Texture *texture, SDL_Renderer *renderer,
							int x, int y, int w, int h);
void			xyz_text(t_rt *rt, float *xyz, SDL_Color *text_color,
							int y, int x);
void			draw_titles_xyz(t_rt *rt, SDL_Color *color);
void			draw_xyz(t_rt *rt, int y, t_vector *vector, t_colors *color);
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
					char *str, char **str_xyz, t_colors *color);
/* end gui_button.c */

void			draw_gradient(SDL_Renderer * renderer,
									SDL_Rect *back_rect, const SDL_Color c1, const SDL_Color c2);
void			keyboard(t_rt *rt, t_all_rect *all_rect, t_colors *color);
void			mouse_move(t_rt *rt, t_all_rect *all_rect, t_colors *color);
void			create_xyz_subtitles(t_rt *rt, int x, int y, char *str,
											t_colors *color);
void			gui_tab_bar(t_window *win, t_rt *rt, t_all_rect *rect, t_colors *color);
void			render_tab_bar(t_window *win, SDL_Color *color,
								SDL_Rect *rect, char *str);
void			draw_main_tab(t_rt *rt, t_all_rect *all_rect, t_colors *color);
void			draw_render_tab(t_rt *rt, t_all_rect *all_rect, t_colors *color);
void			progress_bar(t_rt *rt, t_colors *color, t_all_rect *all_rect);
void			draw_title_ray_tracing(t_window *win, SDL_Color *color);
void			draw_ispressed_checkbox(t_rt *rt, SDL_Rect *rect,
										char *str, t_colors *color);
void			draw_render_checkbox(t_rt *rt, SDL_Rect *all_rect,
										t_colors *color, char **str, int count);

#endif
