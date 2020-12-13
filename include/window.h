/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 17:05:43 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/13 12:17:31 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

# ifdef __APPLE__
#  include <SDL.h>
# elif __unix__
#  include <SDL2/SDL.h>
# else
#  include <SDL.h>
# endif

# ifndef __OPENCL_C_VERSION__
#  include "rt_types.h"
# endif
# include "color.h"

/*
** @brief
** to manipulate sdl windows
*/

typedef struct s_window	t_window;

struct	s_window
{
	SDL_Window		*ptr;
	SDL_Renderer	*renderer;
	SDL_Texture		*texture;
	t_color			*rgb_image;
	t_uint			*image;
	int			width;
	int			height;
};

/*
** @brief
** init sdl window and image buffer
** @param window
** @return ** int
*/

int		init_window(t_window *window);
void	display_image(t_window *window);
void	free_window(t_window *window);

#endif
