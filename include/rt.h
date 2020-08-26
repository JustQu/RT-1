/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 13:10:59 by maximka           #+#    #+#             */
/*   Updated: 2020/08/26 19:07:02 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <SDL2/SDL.h>
#define WIDTH 1200
#define HEIGHT 800

#include "libft.h"

enum    e_types
{
    cone,
    cylinder,
    paraboloid,
    plane,
    sphere,
    torus,
    triangle,
    box,
    disk,
    rectangle
};

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
}                   t_gui;

typedef struct		s_rt
{
    SDL_Renderer    *render_menu;
	t_sdl			sdl;
    t_gui           gui;
    t_vector        direction;
    t_vector        center;
    t_vector        rotate;
}					t_rt;
// struct                s_light
// {
//     cl_float4        origin;
//     cl_float4        direction;
//     t_color            color;
//     cl_float        ls; //radiance scaling factor [0, inf)
//     t_light_type    type;

//     cl_int            object_id; //for area lights
// };

// struct                    s_obj
// {
//     t_type                type;
//     t_material            material;
//     t_bbox                bounding_box;
//     cl_float4            origin;
//     cl_float4            direction;
//     cl_float4            dir2;
//     cl_float4            normal;
//     cl_float            r;
//     cl_float            r2;
//     cl_float            angle;
//     cl_float            maxm;
//     cl_float            minm;
//     cl_int                shadows;
//     cl_int                sampler_id;
// };

