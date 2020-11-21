/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 00:05:29 by dmelessa          #+#    #+#             */
/*   Updated: 2020/11/21 22:35:34 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "material.h"
# include "objects.h"
# include "light.h"
# include "texture.h"
# include "libft/libft.h"
# include "camera.h"
// # include "scene.h"
// # include "instance_manager.h"
// # include "resource_manager.h"
// # include "light_manager.h"
# include <math.h>

typedef enum e_block_type			t_block_type;

// enum	e_block_type
// {
// 	// ambient_light = -1,
// 	object,
// 	light,
// 	camera,
// 	options
// };

typedef enum	e_parsed_type
{
	object,
	light,
	camera,
	options,
}				t_parsed_type;

typedef struct s_parsed_object
{
	t_material	material;
	t_texture	texture;
	cl_float4	origin;
	cl_float4	vector1;
	cl_float4	vector2;
	cl_float4	direction;
	cl_float3	rotation;
	cl_float3	scaling;
	cl_float	minm;
	cl_float	maxm;
	cl_float	r;
	cl_float	r2;
	t_type		type;
	cl_int		boolean;
}				t_parsed_object;

typedef struct	s_parsed_light
{
	cl_float4		origin;
	cl_float4		direction;
	t_color			color;
	cl_float		ls;
	t_light_type	type;
	cl_float		pdf; //computed value
}				t_parsed_light;

typedef union	u_parsed_data
{
	t_parsed_object	object;
	t_parsed_light	light;
	// t_camera		camera;
}				t_parsed_data;

typedef struct	u_parsed_info
{
	t_parsed_type	type;
	t_parsed_data	data;
}				t_parsed_info;

int				str_len(char *str);
char			*get_key(char **str);
char			*get_value(char **str);
t_parsed_object	get_default_obj();
t_light			get_default_light();
t_camera		get_default_camera();
// t_rt_options	get_default_options();
void			get_default_material(t_material *material);
void			get_default_texture(t_texture *texture);
void		pars_light(char *str);
// void		pars_camera(char *str, t_scene *scene);
int			get_log_fd(char *str);

#endif
