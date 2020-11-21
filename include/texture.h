/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 22:49:19 by dmelessa          #+#    #+#             */
/*   Updated: 2020/11/11 00:05:42 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H

# ifndef __OPENCL_C_VERSION__
#  include "rt_types.h"
#  include "color.h"
# endif

typedef enum e_texture_type			t_texture_type;
typedef struct s_texture			t_texture; //32 bytes

enum	e_texture_type
{
	solid,
	checker,
	checker2d,
	transparent_checker,
	reflective_checker,
	perlin,
	smooth_perlin,
	turbulence_perlin,
	wave_perlin,
	image
};

struct		s_solid_texture
{
	t_color	color;
};

struct		s_checker_texture
{
	t_color	odd;
	t_color	even;
};

struct			s_smooth_perlin_texture
{
	cl_float	scale;
};

struct	s_image_texture
{
	int	offset;
	int	width;
	int	height;
};

union							u_texture_data
{
	struct	s_solid_texture			solid;
	struct	s_checker_texture		checker;
	struct	s_smooth_perlin_texture	smooth_perlin;
};

/**
** move ?
** scale ?
*/
struct						s_texture		//32bytes
{
	union u_texture_data	data;		//16 bytes
	t_texture_type			type;		//4 bytes
	char					gap[12];	//12 byte gap
};

#endif
