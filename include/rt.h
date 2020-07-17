/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 13:10:59 by maximka           #+#    #+#             */
/*   Updated: 2020/07/17 19:10:39 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifdef __unix__
#  include "SDL2/SDL.h"
# else
#  include "SDL.h"
# endif

#include "CL/cl.h"

#ifdef __OPENCL_C_VERSION__
#define cl_float4 float4
#define cl_float3 float3
#define cl_float float
#define cl_int4 int4
#define cl_int3 int3
#define cl_int int
#define cl_char char
#define cl_uchar uchar
#define cl_bool bool
#define cl_uint unsigned int
#endif

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

typedef int t_color;
typedef int t_light_type;
typedef int t_type;
typedef int t_material;
typedef int t_bbox;


struct		s_light
{
	cl_float4		origin;
	cl_float4		direction;
	t_color			color;
	cl_float		ls; //radiance scaling factor [0, inf)
	t_light_type	type;

	cl_int			object_id; //for area lights
};

struct                    s_obj
{
    t_type                type;
    t_material            material;
    t_bbox                bounding_box;
    cl_float4            origin;
    cl_float4            direction;
    cl_float4            dir2;
    cl_float4            normal;
    cl_float            r;
    cl_float            r2;
    cl_float            angle;
    cl_float            maxm;
    cl_float            minm;
    cl_int                shadows;
    cl_int                sampler_id;
};


struct		s_ray
{
	cl_float4	origin;
	cl_float4	direction;
};

/**
** @brief
** информация о opencl
*/
typedef struct			s_clp
{
	cl_platform_id		pl_id;
	cl_device_id		de_id;
	cl_uint				ret_num_devices;
	cl_uint				ret_num_platforms;
	cl_int				ret;
	cl_context			context;
	cl_command_queue	queue;
}						t_clp;

/**
** @brief
** to manipulate sdl windos
*/
typedef struct			s_window
{
	SDL_Window			*ptr;
	SDL_Renderer		*renderer;
	SDL_Texture			*texture;
	uint32_t			*image; // TODO(dmelessa): change to cl_image later
	int					width;
	int					height;
}						t_window;

typedef struct s_cl_program	t_cl_program;
struct	s_cl_program
{
	cl_program	program;
	cl_kernel	kernel;
	cl_mem		image;
};
