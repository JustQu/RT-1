/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 17:10:47 by alex              #+#    #+#             */
/*   Updated: 2020/08/22 18:51:06 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef RT_GUI_H
# define RT_GUI_H

# include <SDL2/SDL_render.h>
# include <SDL2/SDL_image.h>
# include <SDL2/SDL_ttf.h>
# include <SDL2/SDL2_gfxPrimitives.h>

# define WIDTH_MENU WIDTH / 4
# define WIDTH_OFFSET WIDTH - WIDTH / 4
# define MARGIN 10
# define MARGIN_Y 10
# define FONT_TITLE_SIZE 15
# define FONT_SUBTITLE_SIZE 12
# define COLOR_STEP 100
# define HEIGHT_BUTTON 30

typedef struct s_rt t_rt;
typedef struct s_vector t_vector;

typedef struct	s_all_rect
{
	SDL_Rect	color_picker_button;
	SDL_Rect	color_picker;
	SDL_Rect	background;
	SDL_Rect	checkbox_button;
}				t_all_rect;

typedef struct 	s_colors
{
	SDL_Color	preground;
	SDL_Color	border_color;
	SDL_Color	title_text_color;
	SDL_Color	xyz_text_color;
	SDL_Color	subtitle_xyz_color;
	SDL_Color	background_color;
}				t_colors;

int					main_gui(t_rt *rt, t_all_rect *all_rect, t_colors *color);
void				draw_background(t_rt *rt);
void 				render_texture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);
SDL_Texture*		load_texture(char *str, SDL_Renderer *renderer);
void				render_rect(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y, int w, int h);
void				xyz_text(t_rt *rt, float *xyz, SDL_Color *text_color, int y, int x);
void				draw_titles(t_rt *rt, SDL_Color *color);
void				draw_xyz(t_rt *rt, int y, t_vector *vector, t_colors *color);
void				draw_fill_rect(t_rt *rt, SDL_Rect *background, SDL_Color *color);
SDL_Texture*		render_text(char *message, char *fontFile,
									SDL_Color color, int fontSize, SDL_Renderer *renderer);
void				draw_button(t_rt *rt, SDL_Rect *rect, char *str, t_colors *color);
void				draw_gradient(SDL_Renderer * renderer,
									SDL_Rect *back_rect, const SDL_Color c1, const SDL_Color c2);
void				keyboard(t_rt *rt, t_all_rect *all_rect, t_colors *color);
void				mouse_move(t_rt *rt, t_all_rect *all_rect, t_colors *color);

#endif
