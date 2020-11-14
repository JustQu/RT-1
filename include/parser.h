/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 00:05:29 by dmelessa          #+#    #+#             */
/*   Updated: 2020/11/14 19:02:14 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "material.h"
# include "objects.h"
# include "light.h"
# include "texture.h"

typedef enum	e_parsed_type
{
	object,
	light,
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

#endif
