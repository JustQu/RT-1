/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 16:58:26 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/12 23:08:36 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_H
# define IMAGE_H

# include "rt_types.h"
# include "color.h"

# define DEFAULT_IMAGE_WIDTH 800
# define DEFAULT_IMAGE_HEIGHT 640

typedef struct s_rendered_image	t_image;

struct	s_rendered_image
{
	t_u32	*pixels;
	t_color	*rgb;
	t_u32	width;
	t_u32	height;
};

// int		init_image(t_image *const image);

int		init_image(t_image  *const image, t_u32 width, t_u32 height);

int		save_image_to_file(t_image *image);


#endif
