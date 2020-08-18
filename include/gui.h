/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 17:10:47 by alex              #+#    #+#             */
/*   Updated: 2020/08/18 17:16:02 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_GUI_H
# define RT_GUI_H

int					main_gui(t_rt *rt);
void				draw_background(t_rt *rt);
void 				render_texture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);
SDL_Texture*		load_texture(char *str, SDL_Renderer *renderer);
void				render_rect(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y, int w, int h);

#endif
