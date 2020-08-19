/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 17:10:47 by alex              #+#    #+#             */
/*   Updated: 2020/08/19 09:46:42 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef RT_GUI_H
# define RT_GUI_H

# include <SDL2/SDL_render.h>
# include <SDL2/SDL_image.h>
# include <SDL2/SDL_ttf.h>

# define WIDTH_MENU WIDTH / 4
# define WIDTH_OFFSET WIDTH - WIDTH / 4
# define MARGIN 10
# define FONT_SIZE 25
# define COLOR_STEP 100

typedef struct s_rt t_rt;
typedef struct s_vector t_vector;

int					main_gui(t_rt *rt);
void				draw_background(t_rt *rt);
void 				render_texture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);
SDL_Texture*		load_texture(char *str, SDL_Renderer *renderer);
void				render_rect(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y, int w, int h);
void				xyz_text(t_rt *rt, float xyz, SDL_Color *text_color, int y, int x);
void				draw_titles(t_rt *rt, SDL_Color *color);
void				draw_xyz(t_rt *rt, int y, SDL_Color *color, t_vector *vector, SDL_Color *text_color);
void				draw_fill_rect(t_rt *rt, SDL_Rect *background, SDL_Color *color);
SDL_Texture*		render_text(char *message, char *fontFile,
									SDL_Color color, int fontSize, SDL_Renderer *renderer);

#endif
