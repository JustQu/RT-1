/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_types.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 17:57:17 by dmelessa          #+#    #+#             */
/*   Updated: 2020/09/26 21:44:24 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_TYPES_H
# define RT_TYPES_H

# define OPEN_CL __OPENCL_C_VERSION__

/**
** @brief Host code
**
*/
# ifndef __OPENCL_C_VERSION__
#  include "inttypes.h"
#  include "bool.h"
#  ifdef __APPLE__
#   include "OpenCL/opencl.h"
#  else
#   include "CL/cl.h"
#  endif

typedef uint32_t	t_uint;
typedef int32_t		t_int;

# endif

# define SUCCESS	0
# define ERROR	-1

# ifndef M_PI
#  define M_PI 3.14159265358979323846264338327950288
# endif

# ifdef __OPENCL_C_VERSION__
#  define cl_float16 float16
#  define cl_float4 float4
#  define cl_float3 float3
#  define cl_float float
#  define cl_int4 int4
#  define cl_int3 int3
#  define cl_int int
#  define cl_char char
#  define cl_uchar uchar
#  define cl_bool bool
#  define cl_uint unsigned int
# endif

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 17:51:48 by dmelessa          #+#    #+#             */
/*   Updated: 2020/09/28 13:48:21 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# ifndef __OPENCL_C_VERSION__
#  include "rt_types.h"
# endif

typedef struct s_color	t_color;

/**
** @brief store color in rgb float compnents.
** Components are normolized [0.0f, 1.0f]
**
*/
struct			s_color
{
	cl_float	r;
	cl_float	g;
	cl_float	b;
	cl_float	a;
};

# ifndef __OPENCL_C_VERSION__
void	set_color_int(t_color *color, int value);
void	set_color_uchar(t_color *color, uint8_t r, uint8_t g, uint8_t b);
void	set_color_float(t_color *color, float r, float g, float b);
# endif

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 23:23:28 by dmelessa          #+#    #+#             */
/*   Updated: 2020/09/28 13:56:37 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AABB_H
# define AABB_H

# ifndef __OPENCL_C_VERSION__
#  include "rt_types.h"
# endif

/**
** @brief Axis-aligned bounding box
**
*/

typedef struct s_aabb	t_aabb;
typedef struct s_aabb	t_bbox;

struct					s_aabb
{
	cl_float4			min;
	cl_float4			max;
};

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 17:46:35 by dmelessa          #+#    #+#             */
/*   Updated: 2020/09/29 18:30:24 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

#include "rt_types.h"

typedef enum e_camera_type	t_camera_type;
typedef struct s_camera		t_camera; //160
typedef struct s_viewplane	t_viewplane;

/**
** @brief Набор типов камеры
**
** orthographic - ортографическая проекция
** perspective - перспектива
** thin_lens - эффект тонкой линзы
** fisheye - эффект рыбьего глаза
** spherical - сферическая проекция
** stereo - стерео изображение
*/
enum	e_camera_type
{
		orthographic,
		perspective,
		thin_lens,
		fisheye,
		spherical,
		stereo
};

/**
** @brief Плоскость проецирования
** pixel_size - размер пикселя, по умолчанию 1
** width - ширина плоскости
** height - высота плоскости
*/
struct s_viewplane
{
	cl_float	pixel_size;
	cl_int		width;
	cl_int		height;
};

/**
** @TODO: make transformation matrix
** TODO: singularity paragraph 9.9
**
*/

/**
** @brief Класс камеры
**
** viewplane - плоскоть проецирования
** origin - местоположение камеры
** direction - напралвние взгляда
** up -вектор вверх
** u, v, w - внутренняя система координат камеры
** d - расстояние до viewplane, плоскости проецирования
** zoom - коэффициент приближения
** exposure_time - экспозиция
** type - тип камеры
** sampler_id - идентификатор сэмплера для тонкой линзы
** normalized - флаг остоянияЮ указывающий на нормализованные координаты
** l - Радиус тонкой линзы, либо коэффициент в сферической камере, либо расстояние между изображениями в стерео камере
** f - расстояние до фокальной плоскости тонкой линзы, либо максимальное угловое поле в рыбьем глазе.
*/
struct	s_camera
{
	cl_float4			origin; // eye
	cl_float4			direction; // lookat - eye
	cl_float4			up; // (0, 1, 0)
	cl_float4			u;
	cl_float4			v; // actually we need only th3 vectors. the up vector could be hardcodeded and w = -direction
	cl_float4			w;
	t_viewplane			viewplane;
	cl_float			d; //the view-plane distance
	cl_float			zoom; //zoom factor
	cl_float			exposure_time; //using somewhere later
	t_camera_type		type;
	cl_int				sampler_id; //thin_camera
	cl_int				normalized;
	//thin-lens camera
	cl_float			l; //lens radius or lambda
	cl_float			f; //focal plane distance or psi_max in fisheye

//note: prob not needed
	cl_float			ratio;
	cl_float			inv_w;
	cl_float			inv_h;
	cl_float			angle;
	cl_int				fov;
};

void	compute_uvw(t_camera *camera);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 22:49:19 by dmelessa          #+#    #+#             */
/*   Updated: 2020/10/19 00:05:54 by dmelessa         ###   ########.fr       */
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

struct						s_texture_handler
{
	t_texture				*texture;
	void					(*new)();
	void					(*set_type)();
	void					(*set_kd)();

};

t_texture	create_solid_texture(t_color color);
//TODO(dmelessa): reflective and transparent
t_texture	create_checker_texture(t_color color1, t_color color2);
t_texture	create_perlin_texture();

# define TEXTURE_FROM_MEMORY 1 << 1
# define TEXTURE_FROM_FILE 2 << 1
/**
** @brief Create a img texture object
**
** @param mode
** @param data
** @return ** t_texture
*/
// t_texture	create_img_texture(int mode, void *data);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 00:07:37 by dmelessa          #+#    #+#             */
/*   Updated: 2020/10/19 13:29:19 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIAL_H
# define MATERIAL_H

# ifndef __OPENCL_C_VERSION__
#  include "rt_types.h"
#  include "color.h"
# endif

typedef enum e_material_type		t_material_type;
typedef struct s_material			t_material; //64 bytes

enum e_material_type
{
	matte, //kd, ka
	phong,
	emissive,
	reflective,
	metal,		//mirror
	dielectric,	//transparance

	diffuse_light
};

/**
** color					//16
** reflective color 		//16
** type						//4
** kd						//4 -- diffuse
** ka						//4 -- ambient
** ks						//4 -- specular
** kr						//4 -- reflective
** kt						//4 -- tranpsarente
** exp						//4
** uchar is_reflective		//1
** uchar is_transparent		//1
**
** uchar gap[8]				//8
*/

struct					s_material //kd + ks < 1.0
{
	t_color				reflective_color;					//16 bytes
	t_material_type		type;								//4		20
	cl_float			kd; //diffuse reflection[0, 1]		//4		24
	cl_float			ka; //ambient reflection			//4		28
	cl_float			ks; //specular reflection [0, 1]	//4		32
	cl_float			kr;	//reflective coefficient		//4		36
	cl_float			kt; //transparent coefficient		//4		40
	cl_float			exp;								//4		44
	cl_float			ls;									//4		48

	int					texture_id;							//4		52

	cl_uchar 			is_reflective;						//1		53
	cl_uchar			is_transparent;						//1		54
	cl_uchar			gap[10];								//2		64
};

int		create_material(t_material	type);
#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 00:07:20 by dmelessa          #+#    #+#             */
/*   Updated: 2020/09/28 13:48:48 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# ifndef __OPENCL_C_VERSION__
#  include "rt_types.h"
#  include "material.h"
#  include "aabb.h"
# endif

typedef enum e_types		t_type;
typedef struct s_obj		t_obj;
typedef struct s_triangle	t_triangle;
enum	e_types
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
	rectangle,
	generic_shere
	//todo(dmelessa): another generic types
};

/**
** TODO: change
**
*/
struct					s_obj
{
	t_bbox				bounding_box;
	cl_float4			origin;
	cl_float4			direction;
	cl_float4			dir2;
	cl_float4			normal;
	cl_float			r;
	cl_float			r2;
	cl_float			angle;
	cl_float			maxm;
	cl_float			minm;
	cl_int				shadows;
	cl_int				sampler_id;
	cl_int				gap;
};

struct					s_triangle
{
	cl_float4			vertex1;
	cl_float4			vertex2;
	cl_float4			vertex3;
	cl_float4			vector1; //vertex2 - vertex1
	cl_float4			vector2; // vertex3 - vertex1
	cl_float4			normal;
};

typedef struct			s_object_info
{
	t_material			material;
	cl_float4			origin;	//vertexe for triangle
	cl_float4			vector1;
	cl_float4			vector2;
	cl_float4			direction; //triangle or plane?
	cl_float3			rotation;	//object rotation about x, y, z axis
	cl_float3			scaling;	//scaling toward to axis
	t_bbox				bounding_box;
	cl_float			minm;
	cl_float			maxm;
	cl_float			r;	//torus radius1
	cl_float			r2; // torus radius2
	t_type				type;
	cl_int				transformed;
}						t_object_info;

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 17:35:29 by dmelessa          #+#    #+#             */
/*   Updated: 2020/09/28 13:49:35 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

# ifndef __OPENCL_C_VERSION__
#  include "rt_types.h"
#  include "color.h"
# endif

typedef enum e_light_types			t_light_type;
typedef struct s_light				t_light;
typedef struct s_ambient_occluder	t_ambient_occluder;

//NOTE: some types will be removed from that list
enum	e_light_types
{
	ambient,
	ambient_occluder,
	directional,
	point,
	area,
	enviromental
};

struct				s_light
{
	cl_float4		origin;
	cl_float4		direction;
	t_color			color;
	cl_float		ls; //radiance scaling factor [0, inf)
	t_light_type	type;
	cl_int			object_id; //for area lights
	cl_int			gap;
};

struct				s_ambient_occluder
{
	cl_float4		u;
	cl_float4		v;
	cl_float4		w;
	t_color			color;
	t_color			min_amount;
	cl_float		ls; //radiance scaling factor [0, inf)
	cl_int			sampler_id;
	cl_int			gap[2];
};

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sampler.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 17:53:59 by dmelessa          #+#    #+#             */
/*   Updated: 2020/09/28 13:49:58 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SAMPLER_H
# define SAMPLER_H

# ifndef __OPENCL_C_VERSION__
#  include "rt_types.h"
# endif

typedef enum e_sampler_type			t_sampler_type;
typedef struct s_sampler			t_sampler;

enum	e_sampler_type
{
		none, //maybe we can replace it with regular grid where is onlu one sample per pixel
		regular_grid,
		jitter,
		rand_jitter,
		pure_random,
		nrooks
};

/*
** Sample types flags
*/
#define DEFAULT_SAMPLES		1 << 0
#define DISK_SAMPLES		1 << 1
#define HEMISPHERE_SAMPLES	1 << 2

// #ifdef _WIN64
// __declspec(align(4))
// # endif
struct				s_sampler
{
	t_sampler_type	type;
	cl_int			num_samples; /* the number of sample points in a pattern */
	cl_int			num_sets;	/* the number of sample sets(patterns) stores */
	cl_uint			count;		/* the currenct numer of sample points used */
	cl_int			jump;		// random index jump
	cl_int			samples_type; // default / disk / hemisphere
	// cl_int			shuffled_indices[NUM_SAMPLES * NUM_SETS];

	cl_int			offset;
	cl_int			disk_samples_offset;
	cl_int			hemisphere_samples_offset;
};


#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instance.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 20:05:10 by dmelessa          #+#    #+#             */
/*   Updated: 2020/09/28 13:50:45 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INSTANCE_H
# define INSTANCE_H

# ifndef __OPENCL_C_VERSION__
#  include "material.h"
#  include "objects.h"
# endif

typedef struct s_instance	t_instance;

struct	s_instance
{
	t_material			material;	// todo: сделать менеджер материалов. Зачем? чтобы не загружать полностью материал каждый раз
	cl_int				object_id; //triangle_id if type == triangle
	cl_int				matrix_id;
	t_type				type;
	cl_int				gap[5];
};

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 00:27:56 by dmelessa          #+#    #+#             */
/*   Updated: 2020/09/28 13:51:05 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BVH_H
# define BVH_H

# ifndef __OPENCL_C_VERSION__
#  include "rt_types.h"
#  include "aabb.h"
# endif

typedef struct s_bvh_node t_bvh_node;

/*
** array of nodes will represent the struct itself
*/
typedef struct s_bvh_node *t_bvh;

struct s_bvh_node //48
{
	t_bbox		aabb;
	cl_float3	center; //todo(dmelessa): delete this field
	int			instance_id;
	int			next;
	int			gap[2];
};

/* host prototypes */
# ifndef __OPENCL_C_VERSION__

// #  include "instance_manager.h"

// t_bbox	compute_aabb(t_instance_manager instance_mngr, int id);

# endif

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_options.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 21:34:36 by dmelessa          #+#    #+#             */
/*   Updated: 2020/10/16 19:16:14 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_OPTION_H
# define RT_OPTION_H

# ifndef __OPENCL_C_VERSION__
#  include "rt_types.h"
#  include "color.h"
#  include "sampler.h"
# endif

# define DEFAULT_WIDTH 1280
# define DEFAULT_HEIGHT 720

typedef struct s_rt_options		t_rt_options;

/*
** TODO(dmelessa): move seed to this struct
*/
struct				s_rt_options
{
	t_sampler		ambient_occluder_sampler;
	cl_int			ambient_occlusion;

	t_color			background_color;

	cl_int			depth;

	cl_int			shadows;

	cl_int			area_lightning;

	cl_float		spp; //samples per pixel
	cl_int			aa_id; //anti-aliasing sampler id

	cl_uchar		reset;
};

# ifndef __OPENCL_C_VERSION__

#  include "sampler_manager.h"

int	init_default_options(t_rt_options *options,
					t_sampler_manager *sampler_manager);

# endif

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_rt.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 00:29:53 by dmelessa          #+#    #+#             */
/*   Updated: 2020/10/06 22:00:53 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CL_RT_H
# define CL_RT_H

#define K_HUGE_VALUE 1e4f
#define EPSILON 1e-5f
#define SAMPLES 1
#define BOUNCES 2

typedef struct s_scene				t_scene;

typedef struct s_sampler_manager	t_sampler_manager;

typedef struct s_ray				t_ray;
typedef struct s_hit_information	t_hit_info;
typedef struct s_shade_rec			t_shade_rec;

typedef float16						t_matrix;

typedef struct				s_kernel_buffer
{
	__global t_ray			*rays;
	__global uchar4			*flags;
}							t_kernel_buffer;

typedef struct				s_texture_manager
{
	__global t_texture		*textures;
	__global float4			*perlin_noise;
	// __global float			*perlin_noise_float;
	__global int			*perm_x;
	__global int			*perm_y;
	__global int			*perm_z;
}							t_texture_manager;

typedef struct				s_instance_manager
{
	__constant t_instance	*instances;
	__global t_obj			*objects;
	__constant t_triangle	*triangles;
	__global t_matrix		*matrices;

	t_texture_manager		tex_mngr;

	int						ninstances;
	int						nobjects;
	int						ntriangles;
	int						nmatrices;
}							t_instance_manager;

struct						s_scene
{
	t_instance_manager		instance_manager;
	__constant t_light		*lights;
	__global t_bvh_node		*bvh;
	int						nlights;
	t_camera				camera;
	t_light					ambient_light;
	t_ambient_occluder		ambient_occluder;
};

struct					s_sampler_manager
{
	__global t_sampler	*samplers;
	__global float2		*samples;
	__global float2		*disk_samples;
	__global float3		*hemisphere_samples;
};

struct		s_ray
{
	float4	origin;
	float4	direction;
};

struct		s_hit_information
{
	float	t; //ray distance
	float	m;
	float	dv; //dot(ray.direction, object.direction)
	float	xv; //dot(ray.origin - object.origin, object.direction)
};

//TODO(dmelessa): change later
struct			s_shade_rec
{
	t_ray		ray;			//for specular highlights
	t_hit_info	hit_info;
	float4		hit_point;		//world coordinates of hit point
	float4		local_hit_point;//for attaching textures to objects
	float4		normal;			//normal at hit point
								//NOTE: maybe not needed here
								// and we can use local variable
	float4		direction;		//for area lights

	int			id;
};

float4 get_reflected_vector(float4 l, float4 n);
t_color area_light_shade(t_material material,
						 t_shade_rec shade_rec,
						 t_scene scene,
						 t_sampler_manager sampler_manager,
						 t_rt_options render_options,
						 uint2 *seed);

t_instance get_instance(t_instance_manager instance_manager, int id);

inline t_matrix get_instance_matrix(t_instance_manager instance_manager, t_instance instance);

inline t_obj get_object_info(t_instance_manager instance_manager, t_instance instance);

inline t_triangle get_triangle_info(t_instance_manager instance_manager, t_instance instance);

#endif

void	swap(float *a, float *b)
{
	float tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}


void	print_material(t_material material)
{
	printf("\t\tType:\t");
	if (material.type == phong)
		printf("phong");
	else if (material.type == matte)
		printf("matte");
	else
	{
		printf("\033[0;31m");
		printf("~ERROR~");
		printf("\033[0m");
	}
	printf("\n");
	// printf("\t\tColor:\t%f %f %f| %d\n", material.color.r,
	// 	material.color.g, material.color.b,
	// 	((int)(material.color.r * 255) << 16) + ((int)(material.color.g * 255) << 8) + material.color.b);
	printf("\t\tKd:\t%f\n", material.kd);
	printf("\t\tKa:\t%f\n", material.ka);
	if (material.type == phong)
	{
		printf("\t\tKs:\t%f\n", material.ks);
		printf("\t\tExp:\t%f\n", material.exp);
	}
}

void	print_vector(float4	vec)
{
	printf("Vector: (%f, %f, %f, %f)\n", vec.x, vec.y, vec.z, vec.w);
}

void	print_camera(t_camera camera)
{
	printf("Camera:\n");
	printf("\tViewplane:\n");
}

void	print_sampler(t_sampler sampler, int id)
{
	printf("Sampler #%d:", id);
	printf("\tType: %d\n", sampler.type);
	printf("\tnum_samples %d\n", sampler.num_sets);
	printf("\tnum_sets %d\n", sampler.count);
	printf("\tjump %d\n", sampler.jump);
	printf("\tsamples_type %d\n", sampler.samples_type);
	printf("\toffset %d\n", sampler.offset);
	printf("\tdisk samples offset %d\n", sampler.disk_samples_offset);
	printf("\themisphere samples offset %d\n", sampler.hemisphere_samples_offset);
}

void	print_samples(t_sampler_manager *sampler_manager, t_sampler sampler)
{
	int		offset;

	offset = sampler.num_samples * sampler.num_sets;

}


void	print_instance(t_instance instance)
{
	printf("\tType:\t");
	if (instance.type == sphere)
		printf("sphere");
	else if (instance.type == plane)
		printf("plane");
	else if (instance.type == cone)
		printf("cone");
	else if (instance.type == cylinder)
		printf("cylinder");
	else if (instance.type == torus)
		printf("torus");
	else if (instance.type == triangle)
		printf("triangle");
	else if (instance.type == disk)
		printf("disk");
	else if (instance.type == paraboloid)
		printf("paraboloid");
	else if (instance.type == box)
		printf("box");
	else if (instance.type == rectangle)
		printf("rectangle");
	else
	{
		printf("\033[0;31m");
		printf("~ERROR~");
		printf("\033[0m");
	}
	printf("\n");
	printf("\tObject id:\t%d\n", instance.object_id);
	printf("\tMatrix id:\t%d\n", instance.matrix_id);
	printf("\tMaterial:\t\n");
	print_material(instance.material);
}

void	print_object(t_obj object)
{
	// printf("\t\tBounding box:\t(%f, %f, %f, %f)\n", object.bounding_box.min.x,
	// 												object.bounding_box.min.y,
	// 												object.bounding_box.min.z,
	// 												object.bounding_box.min.w);
	// printf("\t\t\t\t(%f, %f, %f, %f)\n", object.bounding_box.max.x,
	// 									object.bounding_box.max.y,
	// 									object.bounding_box.max.z,
	// 									object.bounding_box.max.w);
	printf("\t\tOrigin:\t\t(%f, %f, %f, %f)\n", object.origin.x,
												object.origin.y,
												object.origin.z,
												object.origin.w);
	// printf("\t\tDirection:\t(%f, %f, %f, %f)\n", object.direction.x,
	// 											object.direction.y,
	// 											object.direction.z,
	// 											object.direction.w);
	// printf("\t\tDir2:\t\t(%f, %f, %f, %f)\n", object.dir2.x,
	// 										object.dir2.y,
	// 										object.dir2.z,
	// 										object.dir2.w);
	printf("\t\tNormal:\t\t(%f, %f, %f, %f)\n", object.normal.x,
												object.normal.y,
												object.normal.z,
												object.normal.w);
	printf("\t\tRadius:\t\t%f\n", object.r);
	printf("\t\tRadis2:\t\t%f\n", object.r2);
	printf("\t\tmaxm:\t\t%f\n", object.maxm);
	printf("\t\tminm:\t\t%f\n", object.minm);
	printf("\t\tshadows:\t%d\n", object.shadows);
	printf("\t\tsampler_id: %d\n", object.sampler_id);
}

void	print_matrix(t_matrix matrix)
{
	// if (get_global_id(0) != 0)
	// 	return ;
	printf("\t\t|%.6f %.6f %.6f %.6f|\n", matrix.s0, matrix.s1, matrix.s2, matrix.s3);
	printf("\t\t|%.6f %.6f %.6f %.6f|\n", matrix.s4, matrix.s5, matrix.s6, matrix.s7);
	printf("\t\t|%.6f %.6f %.6f %.6f|\n", matrix.s8, matrix.s9, matrix.sA, matrix.sB);
	printf("\t\t|%.6f %.6f %.6f %.6f|\n", matrix.sC, matrix.sD, matrix.sE, matrix.sF);
}

void	print_all(t_scene scene)
{
	t_instance	instance;

#if OPEN_CL
	printf("TEST\n");
#endif

	printf("Scene:\n");
	for (int i = 0; i < scene.instance_manager.ninstances; i++)
	{
		instance = scene.instance_manager.instances[i];
		printf("Instance #%d:\n", i);
		print_instance(instance);
		if (instance.type == triangle)
		{
		}
		else
		{
			printf("\tObject: \n");
			print_object(scene.instance_manager.objects[instance.object_id]);
		}
		if (instance.matrix_id > -1)
		{
			printf("\tMatrix:\n");
			print_matrix(scene.instance_manager.matrices[instance.matrix_id]);
		}
	}
}

/*
 *
 *  Utility functions to find cubic and quartic roots,
 *  coefficients are passed like this:
 *
 *      c[0] + c[1]*x + c[2]*x^2 + c[3]*x^3 + c[4]*x^4 = 0
 *
 *  The functions return the number of non-complex roots and
 *  put the values into the s array.
 *
 *  Author:         Jochen Schwarze (schwarze@isa.de)
 *
 *  Jan 26, 1990    Version for Graphics Gems
 *  Oct 11, 1990    Fixed sign problem for negative q's in SolveQuartic
 *  	    	    (reported by Mark Podlipec),
 *  	    	    Old-style function definitions,
 *  	    	    IsZero() as a macro
 *  Nov 23, 1990    Some systems do not declare acos() and cbrt() in
 *                  <math.h>, though the functions exist in the library.
 *                  If large coefficients are used, EQN_EPS should be
 *                  reduced considerably (e.g. to 1E-30), results will be
 *                  correct but multiple roots might be reported more
 *                  than once.
 */

/* epsilon surrounding for near zero values */

#define EQN_EPS 1e-9
#define IsZero(x) ((x) > -EQN_EPS && (x) < EQN_EPS)

int SolveQuadric(double c[3], double s[2])
{
	double p, q, D;

	/* normal form: x^2 + px + q = 0 */

	p = c[1] / (2 * c[2]);
	q = c[0] / c[2];

	D = p * p - q;

	if (IsZero(D))
	{
		s[0] = -p;
		return 1;
	}
	else if (D < 0)
	{
		return 0;
	}
	else /* if (D > 0) */
	{
		double sqrt_D = sqrt(D);

		s[0] = sqrt_D - p;
		s[1] = -sqrt_D - p;
		return 2;
	}
}

int SolveCubic(double c[4], double s[3])
{
	int i, num;
	double sub;
	double A, B, C;
	double sq_A, p, q;
	double cb_p, D;

	/* normal form: x^3 + Ax^2 + Bx + C = 0 */

	A = c[2] / c[3];
	B = c[1] / c[3];
	C = c[0] / c[3];

	/*  substitute x = y - A/3 to eliminate quadric term:
	x^3 +px + q = 0 */

	sq_A = A * A;
	p = 1.0 / 3 * (-1.0 / 3 * sq_A + B);
	q = 1.0 / 2 * (2.0 / 27 * A * sq_A - 1.0 / 3 * A * B + C);

	/* use Cardano's formula */

	cb_p = p * p * p;
	D = q * q + cb_p;

	if (IsZero(D))
	{
		if (IsZero(q)) /* one triple solution */
		{
			s[0] = 0;
			num = 1;
		}
		else /* one single and one double solution */
		{
			double u = cbrt(-q);
			s[0] = 2 * u;
			s[1] = -u;
			num = 2;
		}
	}
	else if (D < 0) /* Casus irreducibilis: three real solutions */
	{
		double phi = 1.0 / 3 * acos(-q / sqrt(-cb_p));
		double t = 2 * sqrt(-p);

		s[0] = t * cos(phi);
		s[1] = -t * cos(phi + M_PI / 3);
		s[2] = -t * cos(phi - M_PI / 3);
		num = 3;
	}
	else /* one real solution */
	{
		double sqrt_D = sqrt(D);
		double u = cbrt(sqrt_D - q);
		double v = -cbrt(sqrt_D + q);

		s[0] = u + v;
		num = 1;
	}

	/* resubstitute */

	sub = 1.0 / 3 * A;

	for (i = 0; i < num; ++i)
		s[i] -= sub;

	return num;
}

int SolveQuartic(double c[5], double s[4])
{
	double coeffs[4];
	double z, u, v, sub;
	double A, B, C, D;
	double sq_A, p, q, r;
	int i, num;

	/* normal form: x^4 + Ax^3 + Bx^2 + Cx + D = 0 */

	A = c[3] / c[4];
	B = c[2] / c[4];
	C = c[1] / c[4];
	D = c[0] / c[4];

	/*  substitute x = y - A/4 to eliminate cubic term:
	x^4 + px^2 + qx + r = 0 */

	sq_A = A * A;
	p = -3.0 / 8 * sq_A + B;
	q = 1.0 / 8 * sq_A * A - 1.0 / 2 * A * B + C;
	r = -3.0 / 256 * sq_A * sq_A + 1.0 / 16 * sq_A * B - 1.0 / 4 * A * C + D;

	if (IsZero(r))
	{
		/* no absolute term: y(y^3 + py + q) = 0 */

		coeffs[0] = q;
		coeffs[1] = p;
		coeffs[2] = 0;
		coeffs[3] = 1;

		num = SolveCubic(coeffs, s);

		s[num++] = 0;
	}
	else
	{
		/* solve the resolvent cubic ... */

		coeffs[0] = 1.0 / 2 * r * p - 1.0 / 8 * q * q;
		coeffs[1] = -r;
		coeffs[2] = -1.0 / 2 * p;
		coeffs[3] = 1;

		(void)SolveCubic(coeffs, s);

		/* ... and take the one real solution ... */

		z = s[0];

		/* ... to build two quadric equations */

		u = z * z - r;
		v = 2 * z - p;

		if (IsZero(u))
			u = 0;
		else if (u > 0)
			u = sqrt(u);
		else
			return 0;

		if (IsZero(v))
			v = 0;
		else if (v > 0)
			v = sqrt(v);
		else
			return 0;

		coeffs[0] = z - u;
		coeffs[1] = q < 0 ? -v : v;
		coeffs[2] = 1;

		num = SolveQuadric(coeffs, s);

		coeffs[0] = z + u;
		coeffs[1] = q < 0 ? v : -v;
		coeffs[2] = 1;

		num += SolveQuadric(coeffs, s + num);
	}

	/* resubstitute */

	sub = 1.0 / 4 * A;

	for (i = 0; i < num; ++i)
		s[i] -= sub;

	return num;
}

uint		random(uint2 *seed)
{
	enum { A=4294883355U };
	uint x = (*seed).x, c = (*seed).y;  // Unpack the state
	uint res = x^c;                     // Calculate the result
	uint hi = mul_hi(x, A);              // Step the RNG
	x = x * A + c;
	c = hi + (x < c);
	*seed = (uint2)(x, c);               // Pack the state back up
	return res;                       // Return the next result
}

float get_random(unsigned int *seed0, unsigned int *seed1) {

	/* hash the seeds using bitwise AND operations and bitshifts */
	*seed0 = 36969 * ((*seed0) & 65535) + ((*seed0) >> 16);
	*seed1 = 18000 * ((*seed1) & 65535) + ((*seed1) >> 16);

	unsigned int ires = ((*seed0) << 16) + (*seed1);

	/* use union struct to convert int to float */
	union {
		float f;
		unsigned int ui;
	} res;

	res.ui = (ires & 0x007fffff) | 0x40000000;  /* bitwise AND, bitwise OR */
	return (res.f - 2.0f) / 2.0f;
}

t_color	color_sum(t_color a, t_color b)
{
	t_color res;
	res.r = a.r + b.r;
	res.g = a.g + b.g;
	res.b = a.b + b.b;
	return (res);
}

t_color	color_multi(t_color a, t_color b)
{
	t_color	res;

	res.r = a.r * b.r;
	res.g = a.g * b.g;
	res.b = a.b * b.b;
	return (res);
}

t_color	float_color_multi(float	c, t_color color)
{
	t_color	res;

	res.r = c * color.r;
	res.g = c * color.g;
	res.b = c * color.b;
	return (res);
}

/*
** TODO: randomness §5
** ??????? ??? ????????(???????)
*/
float2	sample_unit_square(t_sampler *sampler, __global float2 *samples, uint2 *seed)
{
	if (sampler->count % sampler->num_samples == 0) // ?????? ?????? ???????
		sampler->jump = (random(seed) % sampler->num_sets) * sampler->num_samples;

	return ((samples + sampler->offset)[sampler->jump +  (random(seed) + sampler->count++) % sampler->num_samples]);

	// return (samples[sampler->jump + sampler->shuffled_indices[sampler->jump + sampler->count++ % sampler->num_samples]]);
}

/*
** ??????? ??? ?????
*/
float2	sample_unit_disk(t_sampler *sampler, __global float2 *disk_samples, uint2 *seed)
{
	if (sampler->count % sampler->num_samples == 0)
		sampler->jump = (random(seed) % sampler->num_sets) * sampler->num_samples;

	return ((disk_samples + sampler->offset)[sampler->jump + (random(seed) + sampler->count++) % sampler->num_samples]);;

	return ((disk_samples + sampler->offset)[sampler->jump + sampler->count++ % sampler->num_samples]);
}

/*
** ??????? ??? ?????????
*/
float3	sample_hemisphere(t_sampler *sampler, __global float3 *hemisphere_samples, uint2 *seed)
{
	if (sampler->count % sampler->num_samples == 0)
		sampler->jump = (random(seed) % sampler->num_sets) * sampler->num_samples;

	return ((hemisphere_samples + sampler->offset)[sampler->jump + sampler->count++ % sampler->num_samples]);
}

t_sampler	get_sampler(t_sampler_manager sampler_manager, int sampler_id)
{
	int			i;
	int			offset;
	t_sampler	tmp;

	// offset = 0;
	// for (i = 0; i < sampler_id; i++)
	// {
	// 	tmp = sampler_manager.samplers[i];
	// 	offset += tmp.num_sets * tmp.num_samples;
	// }
	tmp = sampler_manager.samplers[i];
	// tmp.offset = offset;
	return (tmp);
}

float4	vector_matrix_mul(float4 vector, t_matrix matrix)
{
	return (float4)(
		matrix.s0 * vector.x + matrix.s1 * vector.y + matrix.s2 * vector.z,
		matrix.s4 * vector.x + matrix.s5 * vector.y + matrix.s6 * vector.z,
		matrix.s8 * vector.x + matrix.s9 * vector.y + matrix.sA * vector.z,
		0.0f
	);
}

float4	point_matrix_mul(float4 point, t_matrix matrix)
{
	return (float4)(
		matrix.s0 * point.x + matrix.s1 * point.y + matrix.s2 * point.z + matrix.s3,
		matrix.s4 * point.x + matrix.s5 * point.y + matrix.s6 * point.z + matrix.s7,
		matrix.s8 * point.x + matrix.s9 * point.y + matrix.sA * point.z + matrix.sB,
		0.0f
	);
}

float4	get_sphere_normal(float4 point, t_obj sphere)
{
	return (normalize(point - sphere.origin));
}

float4	get_plane_normal(t_obj plane)
{
	return (float4)(0.0f, 1.0f, 0.0f, 0.0f);
}

float4	get_cylinder_normal(float4 point, t_obj cylinder)
{
	return (normalize(point - cylinder.origin - dot(cylinder.direction,
													(point - cylinder.origin))
						* cylinder.direction));
}

float4	get_cone_normal(float4 point, t_obj cone, t_hit_info hit_info)
{
	float m = hit_info.dv * hit_info.t + hit_info.xv;
	return (normalize(point - cone.origin - cone.r2 * cone.direction * m));
}

float4	get_paraboloid_normal(float4 point, t_obj paraboloid, t_hit_info hit_info)
{
	// if (paraboloid.maxm > 0.0f)
	// 	return (normalize(point - paraboloid.origin - paraboloid.direction *
	// 		(hit_info.m + paraboloid.r)));
	// float m = hit_info.dv * hit_info.t + hit_info.xv;
	// return (normalize(point - paraboloid.origin - paraboloid.direction * (m +
	// 	paraboloid.r)));
}

 float4	get_triangle_normal(t_triangle triangle)
{
	return (triangle.normal);
}

float4	get_torus_normal(float4 point, t_obj torus)
{
	float p = torus.r * torus.r + torus.r2 * torus.r2;
	float s = point.x * point.x + point.y * point.y + point.z * point.z;

	return normalize((float4)(
		4.0f * point.x * (s - p),
		4.0f * point.y * (s - p + 2.0f * torus.r * torus.r),
		4.0f * point.z * (s - p),
		0.0f));
}

float4	get_box_normal(float4 point, t_obj box, t_hit_info hit_info)
{
	if (hit_info.m == 0)
	{
		return ((float4)(-1.0f, 0.0f, 0.0f, 0.0f));
	}
	else if (hit_info.m == 1)
	{
		return ((float4)(0.0f, -1.0f, 0.0f, 0.0f));
	}
	else if (hit_info.m == 2)
	{
		return ((float4)(0.0f, 0.0f, -1.0f, 0.0f));
	}
	else if (hit_info.m == 3)
	{
		return ((float4)(1.0f, 0.0f, 0.0f, 0.0f));
	}
	else if (hit_info.m == 4)
	{
		return ((float4)(0.0f, 1.0f, 0.0f, 0.0f));
	}
	else if (hit_info.m == 5)
	{
		return ((float4)(0.0f, 0.0f, 1.0f, 0.0f));
	}
}

float4	get_object_normal(float4 point, t_obj object, t_hit_info hit_info, t_type type)
{
	if (type == sphere)
	{
		return get_sphere_normal(point, object);
	}
	else if (type == plane)
	{
		return (get_plane_normal(object));
	}
	else if (type == cylinder)
	{
		return (get_cylinder_normal(point, object));
	}
	else if (type == cone)
	{
		return (get_cone_normal(point, object, hit_info));
	}
	else if (type == paraboloid)
	{
		return (get_paraboloid_normal(point, object, hit_info));
	}
	else if (type == torus)
	{
		return (get_torus_normal(point, object));
	}
	else if (type == box)
	{
		return (get_box_normal(point, object, hit_info));
	}
	else if (type == disk)
	{
		return (get_plane_normal(object));
	}
	else if (type == rectangle)
		return object.normal;
}

float4	transform_normal(float4 normal, t_matrix matrix)
{
	return (float4)(
		matrix.s0 * normal.x + matrix.s4 * normal.y + matrix.s8 * normal.z,
		matrix.s1 * normal.x + matrix.s5 * normal.y + matrix.s9 * normal.z,
		matrix.s2 * normal.x + matrix.s6 * normal.y + matrix.sA * normal.z,
		0.0f);
}

float4	get_instance_normal(t_instance_manager instance_mngr,
							t_instance instance,
							t_shade_rec *shade_rec)
{
	float4		normal;

	if (instance.type == triangle)
		normal = get_triangle_normal(instance_mngr.triangles[instance.object_id]);
	else
		normal = get_object_normal(shade_rec->local_hit_point,
									instance_mngr.objects[instance.object_id],
									shade_rec->hit_info,
									instance.type);
	return (normal);
}

// #include "world.h"
// #include "cl_rt.h"

bool	bbox_intersection(t_ray ray, t_bbox bbox)
{
	float tmin = (bbox.min.x - ray.origin.x) / ray.direction.x;
	float tmax = (bbox.max.x - ray.origin.x) / ray.direction.x;

	if (tmin > tmax) swap(&tmin, &tmax);

	float tymin = (bbox.min.y - ray.origin.y) / ray.direction.y;
	float tymax = (bbox.max.y - ray.origin.y) / ray.direction.y;

	if (tymin > tymax) swap(&tymin, &tymax);

	if ((tmin > tymax) || (tymin > tmax))
		return false;

	if (tymin > tmin)
		tmin = tymin;

	if (tymax < tmax)
		tmax = tymax;

	float tzmin = (bbox.min.z - ray.origin.z) / ray.direction.z;
    float tzmax = (bbox.max.z - ray.origin.z) / ray.direction.z;

    if (tzmin > tzmax) swap(&tzmin, &tzmax);

    if ((tmin > tzmax) || (tzmin > tmax))
        return false;

    if (tzmin > tmin)
        tmin = tzmin;

    if (tzmax < tmax)
        tmax = tzmax;

    return true;

	float ox = ray.origin.x;
	float oy = ray.origin.y;
	float oz = ray.origin.z;
	float dx = ray.direction.x;
	float dy = ray.direction.y;
	float dz = ray.direction.z;
	float tx_min, ty_min, tz_min;
	float tx_max, ty_max, tz_max;
	float a = 1.0f / dx;

	if (a >= 0.0f)
	{
		tx_min = (bbox.min.x - ox) * a;
		tx_max = (bbox.max.x - ox) * a;
	}
	else
	{
		tx_min = (bbox.max.x - ox) * a;
		tx_max = (bbox.min.x - ox) * a;
	}
	float b = 1.0f / dy;
	if (b >= 0.0f)
	{
		ty_min = (bbox.min.y - oy) * b;
		ty_max = (bbox.max.y - oy) * b;
	}
	else
	{
		ty_min = (bbox.max.y - oy) * b;
		ty_max = (bbox.min.y - oy) * b;
	}

	float c = 1.0f / dz;
	if (c >= 0.0f)
	{
		tz_min = (bbox.min.z - oz) * c;
		tz_max = (bbox.max.z - oz) * c;
	}
	else
	{
		tz_min = (bbox.max.z - oz) * c;
		tz_max = (bbox.min.z - oz) * c;
	}
	float t0, t1;
	if (tx_min > ty_min)
		t0 = tx_min;
	else
		t0 = ty_min;

	if (tz_min > t0)
		t0 = tz_min;

	if (tx_max < ty_max)
		t1 = tx_max;
	else
		t1 = ty_max;
	if (tz_max < t1)
		t1 = tz_max;

	return (t0 < t1 && t1 > 0.0f);
}

bool	box_intersection(t_ray ray, t_obj box, t_shade_rec *const shade_rec,
						float *const tmin)
{
	float tx_min, ty_min, tz_min;
	float tx_max, ty_max, tz_max;
	float a = 1.0f / ray.direction.x;
	float b = 1.0f / ray.direction.y;
	float c = 1.0f / ray.direction.z;

	t_bbox bbox = box.bounding_box;

	if (a >= 0.0f)
	{
		tx_min = (bbox.min.x - ray.origin.x) * a;
		tx_max = (bbox.max.x - ray.origin.x) * a;
	}
	else
	{
		tx_min = (bbox.max.x - ray.origin.x) * a;
		tx_max = (bbox.min.x - ray.origin.x) * a;
	}
	if (b >= 0.0f)
	{
		ty_min = (bbox.min.y - ray.origin.y) * b;
		ty_max = (bbox.max.y - ray.origin.y) * b;
	}
	else
	{
		ty_min = (bbox.max.y - ray.origin.y) * b;
		ty_max = (bbox.min.y - ray.origin.y) * b;
	}
	if (c >= 0.0f)
	{
		tz_min = (bbox.min.z - ray.origin.z) * c;
		tz_max = (bbox.max.z - ray.origin.z) * c;
	}
	else
	{
		tz_min = (bbox.max.z - ray.origin.z) * c;
		tz_max = (bbox.min.z - ray.origin.z) * c;
	}

	float	t0, t1;
	float4 norm_in, norm_out;
	if (tx_min > ty_min)
	{
		t0 = tx_min;
		norm_in = (a >= 0.0f) ? (float4)(-1.0f, 0.0f, 0.0f, 0.0f)
							  : (float4)(1.0f, 0.0f, 0.0f, 0.0f);
	}
	else
	{
		t0 = ty_min;
		norm_in = (b >= 0.0f) ? (float4)(0.0f, -1.0f, 0.0f, 0.0f)
							  : (float4)(0.0f, 1.0f, 0.0f, 0.0f);
	}
	if (tz_min > t0)
	{
		t0 = tz_min;
		norm_in = (c >= 0.0f) ? (float4)(0.0f, 0.0f, -1.0f, 0.0f)
							  : (float4)(0.0f, 0.0f, 1.0f, 0.0f);
	}

	if (tx_max < ty_max)
	{
		t1 = tx_max;
		norm_out = (a > 0.0f) ? (float4)(1.0f, 0.0f, 0.0f, 0.0f)
							  : (float4)(-1.0f, 0.0f, 0.0f, 0.0f);
	}
	else
	{
		t1 = ty_max;
		norm_out = (b > 0.0f) ? (float4)(0.0f, 1.0f, 0.0f, 0.0f)
							  : (float4)(0.0f, -1.0f, 0.0f, 0.0f);
	}
	if (tz_max < t1)
	{
		t1 = tz_max;
		norm_out = (c > 0.0f) ? (float4)(0.0f, 0.0f, 1.0f, 0.0f)
							  : (float4)(0.0f, 0.0f, -1.0f, 0.0f);
	}

	if (t0 < t1 && t1 > EPSILON)
	{
		if (t0 > EPSILON && t0 < *tmin)
		{
			*tmin = t0;
			shade_rec->local_hit_point = ray.direction * t0 + ray.origin;
			shade_rec->normal = norm_in;
			return (true);
		}
		else if (t1 < *tmin)
		{
			*tmin = t1;
			shade_rec->local_hit_point = ray.direction * t1 + ray.origin;
			shade_rec->normal = norm_out;
			return (true);
		}
	}
	return (false);
}

inline bool	generic_sphere_instersection(t_ray ray, t_obj sphere,
										t_shade_rec *const shade_rec,
										float *const tmin)
{
	float a = dot(ray.direction, ray.direction);
	float b = 2.0f * dot(ray.direction,  ray.origin);
	float c = dot(ray.origin,  ray.origin) - 1.0f;
	c = b * b - 4.0f * a * c; // DISC = (b/2)^2-ac

	if (c < 0.0f)
		return (false);
	c = sqrt(c);
	float t = (-b - c) / (2.0f * a);
	if (t < 0.0f)
	{
		t = (-b + c) / (2.0f * a);
	}
	if (t > 0.0f && t < *tmin)
	{
		*tmin = t;
		shade_rec->local_hit_point = ray.direction * t + ray.origin;
		shade_rec->normal = get_sphere_normal(shade_rec->local_hit_point, sphere);
		return (true);
	}
	return (false);
}

bool	generic_plane_intersection(t_ray ray, float *const tmin)
{
	bool	ret = false;
	float	denom = ray.direction.y;
	float	t;

	if (denom != 0.0f)
	{
		t = -ray.origin.y;
		if (t * denom > 0.0f)
		{
			t = t / denom;
			if (t >= EPSILON && t < *tmin)
			{
				*tmin = t;
				ret = true;
			}
		}
	}
	return (ret);
}

bool	disk_intersection(t_ray ray, t_obj disk, t_hit_info *hit_info)
{
	float4	a;
	float	t;
	float	denom;
	bool	ret;

	ret = false;
	denom = dot(ray.direction, disk.direction);
	if (denom != 0)
	{
		a = disk.origin - ray.origin;
		t = dot(a, disk.direction);
		if (t * denom > 0.0f) //different signes
		{
			hit_info->t = t / denom;

			if (hit_info->t >= EPSILON)
			{
				float4 point = hit_info->t * ray.direction + ray.origin;
				if (dot(point - disk.origin, point - disk.origin) < disk.r2)
				{
					hit_info->dv = denom;
					ret = true;
				}
			}
		}
	}
	return (ret);
}

bool	rectangle_intersection(t_ray ray, t_obj rectangle,
							t_shade_rec *const shade_rec,
							float *const tmin)
{
	float4	d;
	float	t;
	float	denom;

	denom = ray.direction.z;
	if (denom != 0.0f)
	{
		d = -ray.origin;
		t = dot(d,(float4)(0.0f, 0.0f, 1.0f, 0.0f));
		if (t * denom > 0.0f)
		{
			t = t / denom;

			if (t >= EPSILON && t < *tmin)
			{
				float4 point =  t * ray.direction + ray.origin;
				d = point - rectangle.origin;

				float ddota = dot(d, rectangle.direction);
				if (ddota < 0.0f || ddota > rectangle.r)
					return (false);

				float ddotb = dot(d, rectangle.dir2);
				if (ddotb < 0.0f || ddotb > rectangle.r2)
					return (false);

				// printf("rt");
				shade_rec->local_hit_point = ray.direction * t + ray.origin;
				shade_rec->normal = (float4)(0.0f, 0.0f, 1.0f, 0.0f);
				return (true);
			}
		}
	}
	return (false);
}

/*
** TODO(dmelessa): cap cylinder with discs
*/
 bool cylinder_intersection(t_ray ray, t_obj cylinder, t_shade_rec *shade_rec, float *const tmin)
{
	float	a, b, c, disc;

	a = dot(ray.direction, ray.direction) - ray.direction.y * ray.direction.y;
	b = 2.0f * (dot(ray.direction, ray.origin) - ray.direction.y * ray.origin.y);
	c = dot(ray.origin, ray.origin) - ray.origin.y * ray.origin.y - 1.0f;
	disc = b * b - 4.0f * a * c;

	if (disc >= EPSILON)
	{
		a *= 2.0f;
		disc = sqrt(disc);
		float t = (-b - disc) / a;
			if (cylinder.maxm > 0.0f)
			{
				float m = ray.direction.y * t + ray.origin.y;
				if (t > EPSILON && t < *tmin && m < cylinder.maxm && m > EPSILON)
				{
					*tmin = t;
					shade_rec->local_hit_point = ray.direction * t + ray.origin;
					shade_rec->normal = get_cylinder_normal(shade_rec->local_hit_point, cylinder);
					return true;
				}
				t = (-b + disc) / a;
				m = ray.direction.y * t + ray.origin.y;
				if (t > EPSILON && t < *tmin && m > EPSILON && m < cylinder.maxm)
				{
					*tmin = t;
					shade_rec->local_hit_point = ray.direction * t + ray.origin;
					shade_rec->normal = get_cylinder_normal(shade_rec->local_hit_point, cylinder);
					return true;
				}
			}
	}
	return false;
}

/*
** TODO(dmelessa): cap cone with disc
*/
 bool	cone_intersection(t_ray ray, t_obj cone, t_hit_info *hit_info)
{
	float4	x;
	float	dv, xv, a, b, c, disc;

	x = ray.origin - cone.origin;
	dv = dot(ray.direction, cone.direction);
	xv = dot(x, cone.direction);
	a = dot(ray.direction, ray.direction) - cone.r2 * dv * dv;
	b = 2.0f * (dot(ray.direction, x) - cone.r2 * dv * xv);
	c = dot(x, x) - cone.r2 * xv * xv;
	disc = b * b - 4 * a * c;
	if (disc >= EPSILON)
	{
		a *= 2.0f;
		disc = sqrt(disc);
		hit_info->t = (-b - disc) / a;
		if (hit_info->t < EPSILON)
			hit_info->t = (-b + disc) / a;
		if (hit_info->t > EPSILON)
		{
			if (cone.maxm != 0.0f || cone.minm != 0)
			{
				hit_info->m = dv * hit_info->t + xv;
				if (hit_info->m >= cone.minm + EPSILON &&
					hit_info->m <= cone.maxm)
				{
					hit_info->dv = dv;
					hit_info->xv = xv;
					return true;
				}
				hit_info->t = (-b + disc) / a;
				hit_info->m = dv * hit_info->t + xv;
				if (hit_info->m >= cone.minm + EPSILON &&
					hit_info->m <= cone.maxm)
				{
					hit_info->dv = dv;
					hit_info->xv = xv;
					return true;
				}
			}
			else
			{
				hit_info->dv = dv;
				hit_info->xv = xv;
				return (true);
			}
		}
	}
	return (false);
}

 bool	paraboloid_intersection(t_ray ray, t_obj paraboloid, t_hit_info *hit_info)
{
	float4	x;
	float	a, b, c, dv, xv, disc;

	x = ray.origin - paraboloid.origin;
	dv = dot(ray.direction, paraboloid.direction);
	xv = dot(x, paraboloid.direction);
	a = 1.0f - dv * dv;
	b = 2.0f * (dot(ray.direction, x) - dv * (xv + 2.0f * paraboloid.r));
	c = dot(x, x) - xv * (xv + 4.0f * paraboloid.r);
	disc = b * b - 4.0f * a * c;
	if (disc >= EPSILON)
	{
		a *= 2;
		disc = sqrt(disc);
		hit_info->t = (-b - disc) / a;
		if (hit_info->t < EPSILON)
			hit_info->t = (-b + disc) / a;
		if (hit_info->t > EPSILON)
		{
			if (paraboloid.maxm > 0.0f)
			{
				hit_info->m = dv * hit_info->t + xv;
				if (hit_info->m >= paraboloid.minm &&
					hit_info->m <= paraboloid.maxm)
					return true;
				hit_info->t = (-b + disc) / a;
				hit_info->m = dv * hit_info->t + xv;
				if (hit_info->m >= paraboloid.minm &&
					hit_info->m <= paraboloid.maxm)
					return true;
			}
			else
			{
				hit_info->dv = dv;
				hit_info->xv = xv;
				return (true);
			}
		}
	}
	return (false);
}

 bool	torus_intersecion(t_ray ray, t_obj torus, t_shade_rec *shade_rec, float *const tmin)
{
	double	coeffs[5];
	double	roots[4];
	float	m, n, o, r2, R2;
	int		num_real_roots;

	m = dot(ray.direction, ray.direction);
	n = dot(ray.direction, ray.origin);
	o = dot(ray.origin, ray.origin);
	r2 = torus.r2 * torus.r2;
	R2 = torus.r * torus.r;

	coeffs[4] = m * m; //a
	coeffs[3] = 4.0f * n * m; //b
	coeffs[2] = 4.0f * n * n + 2.0f * m * o - 2.0f * (R2 + r2) * m + 4.0f * R2 * ray.direction.y * ray.direction.y;
	coeffs[1] = 4.0f * n * o - 4.0f * (R2 + r2) * n + 8.0f * R2 * ray.direction.y * ray.origin.y;
	coeffs[0] = o * o - 2.0f * (R2 + r2) * o + 4.0f * R2 * ray.origin.y * ray.origin.y + (R2 - r2) * (R2 - r2);
	num_real_roots = SolveQuartic(coeffs, roots);
	bool	intersect = false;

	if (num_real_roots == 0)
		return false;

	for (int j = 0; j < num_real_roots; j++)
	{
		if (roots[j] > EPSILON && roots[j] < *tmin)
		{
			intersect = true;
			*tmin = roots[j];
			shade_rec->local_hit_point = ray.direction * *tmin + ray.origin;
			shade_rec->normal = get_torus_normal(shade_rec->local_hit_point, torus);
		}
	}
	// hit_info->t = t * 0.99f;
	return (intersect);
}

/*
** TODO(dmelessa): change later
*/
bool	triangle_intersection(t_ray ray, t_triangle triangle,
								t_hit_info *hit_info)
{
	float4	pvec = cross(ray.direction, triangle.vector2);
	float	det = dot(triangle.vector1, pvec);

	if (det < 1e-8 && det > -1e-8)
		return false;

	float	inv_det = 1.0f / det;
	float4	tvec = ray.origin - triangle.vertex1;
	float	u = dot(tvec, pvec) * inv_det;
	if (u < EPSILON || u > 1)
		return false;

	float4	qvec = cross(tvec, triangle.vector1);
	float	v = dot(ray.direction, qvec) * inv_det;
	if (v < EPSILON || u + v > 1)
		return false;
	hit_info->t = dot(triangle.vector2, qvec) * inv_det;
	return hit_info->t > EPSILON;
}

bool	is_intersect(t_obj obj, t_type type, t_ray ray, t_shade_rec *shade_rec, float *const tmin)
{
	if (type == sphere)
	{
		return (generic_sphere_instersection(ray, obj, shade_rec, tmin));
	}
	// else if (type == plane)
	// {
	// 	return (generic_plane_intersection(ray, hit_info));
	// }
	else if (type == cylinder)
	{
		return cylinder_intersection(ray, obj, shade_rec, tmin);
	}
	// else if (type == cone)
	// {
	// 	return (cone_intersection(ray, obj, hit_info));
	// }
	// else if (type == paraboloid)
	// {
	// 	return (paraboloid_intersection(ray, obj, hit_info));
	// }
	else if (type == torus)
	{
		return torus_intersecion(ray, obj, shade_rec, tmin);
	}
	else if (type == box)
	{
		return box_intersection(ray, obj, shade_rec, tmin);
	}
	// else if (type == disk)
	// {
	// 	return (disk_intersection(ray, obj, hit_info));
	// }
	else if (type == rectangle)
	{
		return (rectangle_intersection(ray, obj, shade_rec, tmin));
	}
	return (false);
}

t_ray	transform_ray(t_ray ray, t_matrix transformation_matrix)
{
	t_ray	inv_ray;

	inv_ray.direction = vector_matrix_mul(ray.direction, transformation_matrix);
	inv_ray.origin = point_matrix_mul(ray.origin, transformation_matrix);
	return (inv_ray);
}

bool	instance_hit(t_instance_manager instance_mngr, t_instance instance,
					float *const tmin, t_shade_rec *shade_rec)
{
	bool		intersect = false;
	t_matrix	matrix = get_instance_matrix(instance_mngr, instance);
	t_ray		ray = transform_ray(shade_rec->ray, matrix);
	t_obj		object = instance_mngr.objects[instance.object_id];

	if (instance.type == triangle)
	{
		intersect = (triangle_intersection(ray,
										instance_mngr.triangles[instance.object_id],
										&shade_rec->hit_info));
	}
	else
	{
		intersect = (is_intersect(object, instance.type, ray,
								shade_rec,tmin));
	}

	if (intersect)
	{
		shade_rec->normal = normalize(transform_normal(shade_rec->normal, matrix));
		// if (instance.type == sphere)
		// {
		// 	printf("%v3f ", shade_rec->normal);
		// }
	}
	return (intersect);
}

float4	get_light_direction(t_light light, t_shade_rec shade_rec)
{
	if (light.type == ambient)
		return ((float4)(0.0f, 0.0f, 0.0f, 0.0f));
	else if (light.type == point)
		return (normalize(light.origin - shade_rec.hit_point));
	else if (light.type == directional)
		return -normalize(light.direction);
	else if (light.type == area)
	{
		;//todo
	}
}

 t_color	get_light_radiance(t_light light)
{
	t_color	color;

	if (light.type == ambient)
	{
		color.r = light.color.r * light.ls;
		color.g = light.color.g * light.ls;
		color.b = light.color.b * light.ls;
		return (color);
	}
}

/*
** BRDF - bidirectional reflectance distributuin functions
** the function f returns the BRDF itself, unless it contains the delta function
**
** the function sample_f is used to compute the direction of reflected rays for
** simulating reflective materials and diffuse-diffuse light transport
**
** the function rho returns the bihemispherical reflectance
*/

/*
** BRDF
** 	Lambertian
**	PerfectSpecular
** 	GlossySpecular
*/

t_color	lambertian_f(float kd, t_color color)
{
	return (float_color_multi(kd * (float)M_1_PI, color));
}

t_color	lambertian_rho(float kd, t_color color)
{
	t_color	res;

	res = float_color_multi(kd, color);
	return (res);
}

float	glossy_specular_f(float4 camera_direction, float4 normal, float4 light_direction, float ks, float exp)
{
	float	res = 0;
	float4	r = get_reflected_vector(light_direction, normal);
	float	rdotdir = dot(r, camera_direction);

	if (rdotdir > 0)
		res = ks * pow(rdotdir, exp);
	return res;
}

t_color	perfect_specular_f(float4 ray_dir, float4 normal, float kr, t_color cr)
{
	float	ndotwo = dot(normal, ray_dir);
	float4	wi = -ray_dir + 2.0f * normal * ndotwo;

	return (float_color_multi(kr / dot(normal, wi), cr));
}

float4	get_ambient_occluder_direction(t_ambient_occluder ambient_occluder,
										t_sampler_manager sampler_manager,
										t_sampler *sampler,
										uint2 *seed)
{
	float3 sp = sample_hemisphere(sampler, sampler_manager.hemisphere_samples, seed);
	return (sp.x * ambient_occluder.u
		+ sp.y * ambient_occluder.v
		+ sp.z * ambient_occluder.w);
}

bool	in_shadow(t_ray shadow_ray, t_scene scene)
{
	t_hit_info ht;

	for (int i = 0; i < scene.instance_manager.ninstances; i++)
	{
		// if (instance_hit(scene.instance_manager, shadow_ray, i, &ht))
			// return (true);
	}
	return false;
}

t_color	ambient_occlusion_l(t_scene scene,
							t_sampler_manager sampler_manager,
							t_sampler *sampler,
							t_shade_rec shade_rec,
							uint2 *seed)
{
	t_color	color;

	scene.ambient_occluder.w = shade_rec.normal;
	scene.ambient_occluder.v = normalize(cross(scene.ambient_occluder.w, (float4)(0.0072f, 1.0f, 0.0034f, 0.0f)));
	scene.ambient_occluder.u = cross(scene.ambient_occluder.v, scene.ambient_occluder.w);

	t_ray shadow_ray;
	shadow_ray.origin = shade_rec.hit_point;
	shadow_ray.direction = get_ambient_occluder_direction(scene.ambient_occluder, sampler_manager, sampler, seed);
	color = float_color_multi(scene.ambient_occluder.ls, scene.ambient_occluder.color);
	if (in_shadow(shadow_ray, scene))
		color = float_color_multi(0.1, color);
	return (color);
}

/*
** old ver of interpolation for perlin noise
*/
float	trilinear_interp(float c[2][2][2], float u, float v, float w)
{
	float	accum = 0.0f;
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			for (int k = 0; k < 2; k++)
				accum += (i * u + (1 - i) * (1 - u))
						* (j * v + (1 - j) * (1 - v))
						* (k * w + (1 - k) * (1 - w))
						* c[i][j][k];
	return accum;
}

float	perlin_interp(float3 c[2][2][2], float u, float v, float w)
{
	float	uu = u * u * (3.0 - 2.0 * u);
	float	vv = v * v * (3.0 - 2.0 * v);
	float	ww = w * w * (3.0 - 2.0 * w);
	float	accum = 0.0f;
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			for (int k = 0; k < 2; k++)
			{
				// float3 weight_v = (float3)(u - i, v - j, w - k);
				accum += (i * uu + (1 - i) * (1 - uu))
						* (j * vv + (1 - j) * (1 - vv))
						* (k * ww + (1 - k) * (1 - ww))
						* dot(c[i][j][k], (float3)(u - i, v - j, w - k));
			}
	return (accum);
}

float	perlin_noise(__global float4 *perlin_noise,
					__global int *perm_x,
					__global int *perm_y,
					__global int *perm_z,
					float4 point)
{
	float	u = point.x - floor(point.x);
	float	v = point.y - floor(point.y);
	float	w = point.z - floor(point.z);
	u = u * u * (3.0 - 2.0 * u);
	v = v * v * (3.0 - 2.0 * v);
	w = w * w * (3.0 - 2.0 * w);
	int		i = (int)(4.0f * point.x) & 255;
	int		j = (int)(4.0f * point.y) & 255;
	int		k = (int)(4.0f * point.z) & 255;
	return (perlin_noise[perm_x[i] ^ perm_y[j] ^ perm_z[k]].w);
}

float	smooth_perlin_noise(__global float4 *ranvec,
							__global int *perm_x,
							__global int *perm_y,
							__global int *perm_z,
							float4 point)
{
	int		i = floor(point.x);
	int		j = floor(point.y);
	int		k = floor(point.z);
	float	u = point.x - i;
	float	v = point.y - j;
	float	w = point.z - k;

	float3	c[2][2][2];
	for (int di = 0; di < 2; di++)
		for (int dj = 0; dj < 2; dj++)
			for (int dk = 0; dk < 2; dk++)
				c[di][dj][dk] = ranvec[perm_x[(i + di) & 255]
										^ perm_y[(j + dj) & 255]
										^ perm_z[(k + dk) & 255]].xyz;
	return (perlin_interp(c, u, v, w));
}

float	turbulence_perlin_noise(__global float4 *ranvec,
								__global int *perm_x,
								__global int *perm_y,
								__global int *perm_z,
								float4 point)
{
	float	accum = 0.0f;
	float4	temp_p = point;
	float	weight = 1.0f;
	for (int i = 0; i < 7; i++) {
		accum += weight * smooth_perlin_noise(ranvec, perm_x, perm_y, perm_z, temp_p);
		weight *= 0.5f;
		temp_p *= 2.0f;
	}
	return fabs(accum);
}

t_texture	get_texture(t_texture_manager texture_manager, int texture_id)
{
	return (texture_manager.textures[texture_id]);
}

t_color		get_solid_texture_color(t_texture texture)
{
	return (texture.data.solid.color);
}

/*
** checker 3d
*/
t_color		get_checker_texture_color(t_texture texture, float4 point)
{
	// if (((int)(floor(point.x / 0.3f)) +
	// 	(int)(floor(point.y / 0.3f)) +
	// 	(int)(floor(point.z / 0.3f))) % 2 == 0)
	// {
	// 	return (texture.data.checker.odd);
	// }
	// else
	// {
	// 	return (texture.data.checker.even);
	// }

	float sines = sin(10.0f * point.x) * sin(10.0f * point.y) * sin(10.0f * point.z);
	if (sines < 0)
	{
		return (texture.data.checker.odd);
	}
	else
	{
		return (texture.data.checker.even);
	}
		return ((t_color){ .r = 0.0, .g = 1.0f, .b = 0.0f });
}

/*
** plane checker
*/
t_color		get_checker2d_texture_color(t_texture texture, float4 point)
{
	/* divide by texture size. 1.0f For default and testing purpose */
	int	ix = floor(point.x / 1.0f);
	int	iz = floor(point.z / 1.0f);
	float	fx = point.x / 1.0f - ix;
	float	fz = point.z / 1.0f - iz;
}

t_color		get_perlin_texture_color(t_texture_manager mngr,
									float4 point)
{
	return (float_color_multi(perlin_noise(mngr.perlin_noise, mngr.perm_x,
											mngr.perm_y, mngr.perm_z, point),
							(t_color){ .r = 1.0f, .g = 1.0f, .b = 1.0f }));
}

t_color	get_smooth_perlin_texture_color(t_texture_manager mngr,
										t_texture tex,
										float4 point)
{
	return (float_color_multi(smooth_perlin_noise(mngr.perlin_noise,
								mngr.perm_x, mngr.perm_y,
								mngr.perm_z,
								tex.data.smooth_perlin.scale * point),
							(t_color){ .r = 1.0f, .g = 0.0f, .b = 0.0f }));
}

t_color	get_turbulence_perlin_texture_color(t_texture_manager mngr,
											t_texture tex, float4 point)
{
	return (float_color_multi(
				turbulence_perlin_noise(mngr.perlin_noise, mngr.perm_x,
										mngr.perm_y, mngr.perm_z,
										tex.data.smooth_perlin.scale * point),
				(t_color){ .r = 1.0f, .g = 1.0f, .b = 1.0f }));
}

t_color		get_wave_perlin_texture_color(t_texture_manager mngr,
										t_texture tex, float4 point)
{
	return (float_color_multi(0.5f * (1 +
				sin(tex.data.smooth_perlin.scale * point.z + 10 *
				turbulence_perlin_noise(mngr.perlin_noise, mngr.perm_x,
					mngr.perm_y, mngr.perm_z, point))),
			(t_color){ .r = 0.1f, .g = 0.5f, .b = 0.8f }));
}

/*
** TODO(dmelessa): replace textures with texure manager
*/
t_color		get_color(t_texture_manager texture_manager,
					t_material material,
					t_shade_rec *shade_rec /* hit point */)
{
	t_texture	texture;

	texture = get_texture(texture_manager, material.texture_id);

	if (texture.type == solid)
	{
		return (get_solid_texture_color(texture));
	}
	else if (texture.type == checker)
	{
		return (get_checker_texture_color(texture, shade_rec->hit_point));
	}
	else if (texture.type == perlin)
	{
		return (get_perlin_texture_color(texture_manager, shade_rec->hit_point));
	}
	else if (texture.type == smooth_perlin)
	{
		return (get_smooth_perlin_texture_color(texture_manager,
												texture,
												shade_rec->hit_point));
	}
	else if (texture.type == turbulence_perlin)
	{
		return (get_turbulence_perlin_texture_color(texture_manager,
													texture,
													shade_rec->hit_point));
	}
	else if (texture.type == wave_perlin)
	{
		return (get_wave_perlin_texture_color(texture_manager, texture, shade_rec->hit_point));
	}
}

bool		shadow_hit(t_scene scene, t_light light, t_ray shadow_ray, t_shade_rec shade_rec)
{
	float	t;
	float	tmin = distance(light.origin, shadow_ray.origin);

	int			node_id = 0;
	t_bvh_node	current_node;

	t_shade_rec	sr;
	sr.ray = shadow_ray;

	while (node_id != -1)
	{
		current_node = scene.bvh[node_id];

		if (bbox_intersection(shadow_ray, current_node.aabb))
		{
			if (current_node.instance_id == -1)
			{
				node_id++;
			}
			else /* leaf node*/
			{
				t_instance instance = get_instance(scene.instance_manager,
													current_node.instance_id);
				if (instance_hit(scene.instance_manager, instance,
								&tmin, &sr))
				{
					return (true);
				}
				node_id = current_node.next;
			}
		}
		else
		{
			node_id = current_node.next;
		}
	}

	// for (int i = 0; i < scene.instance_manager.ninstances; i++)
	// {
	// 	t_instance instance = get_instance(scene.instance_manager, i);
	// 	if (instance_hit(scene.instance_manager, shadow_ray, &shade_rec.hit_info, instance)
	// 		&& shade_rec.hit_info.t < d)
	// 		return (true);
	// }
	return (false);
}

t_color		shade_phong(t_material material,
						t_shade_rec shade_rec,
						t_scene scene,
						t_sampler_manager sampler_manager,
						t_rt_options options,
						uint2 *seed)
{
	float4	light_direction;
	float	dirdotn;
	t_color	color_tmp;
	t_color	color;

	// /* revert camera ray for specular light */
	shade_rec.ray.direction = -shade_rec.ray.direction;

	if (options.ambient_occlusion) /* ambient occlusion */
	{
		color = ambient_occlusion_l(scene, sampler_manager, &options.ambient_occluder_sampler, shade_rec, seed);
		// color = color_multi(color, material.color);
	}
	else /* compute constant ambient light using ka coefficent of the materail */
	{
		// color = lambertian_rho(material.ka, material.color);
		color_tmp = get_light_radiance(scene.ambient_light);
		color = color_multi(color, color_tmp);
	}
	// color.r = 0.0f;
	// color.g = 0.0f;
	// color.b = 0.0f;

	/* compute sahding for each light source */
	for (int i = 0; i < scene.nlights; i++)
	{
		bool	in_shadow = false;

		/* compute light direction at hit point */
		light_direction = get_light_direction(scene.lights[i], shade_rec);

		/* multiplying by 0.999f to avoid self shadowing error */
		t_ray	shadow_ray = { .origin = shade_rec.hit_point + 1e-2f * shade_rec.normal, .direction = light_direction };

		if (options.shadows)
			in_shadow = shadow_hit(scene, scene.lights[i], shadow_ray, shade_rec);

		if (!in_shadow)
		{
			/* compute angle between normal at the hit point and light direction */
			dirdotn = dot(shade_rec.normal, light_direction);

			/* if angle > 0 then hit point is receivingl light */
			if (dirdotn > 0.0f)
			{
				/* compute glossy_specular coefficient */
				float a = glossy_specular_f(shade_rec.ray.direction, shade_rec.normal, light_direction, material.ks, material.exp) ;

				/* compute diffuse color */
				// color_tmp = lambertian_f(material.kd, material.color);

				/* sum lambertian color and glossy specular color */
				color_tmp = color_sum(color_tmp, float_color_multi(a, scene.lights[i].color));

				/* compute how much light the point receives depends on angle between the normal at this point and light direction */
				color_tmp.r = scene.lights[i].ls * scene.lights[i].color.r
							* color_tmp.r * dirdotn;
				color_tmp.b = scene.lights[i].ls * scene.lights[i].color.b
							* color_tmp.b * dirdotn;
				color_tmp.g = scene.lights[i].ls * scene.lights[i].color.g
							* color_tmp.g * dirdotn;
				color = color_sum(color_tmp, color);
			}
		}
	}
	return (color);
}

inline t_color		shade_matte(t_material material,
						t_shade_rec shade_rec,
						t_scene scene,
						t_sampler_manager sampler_manager,
						t_rt_options options,
						uint2 *seed)
{
	float4	light_direction;
	float	dirdotn;
	t_color	color_tmp;
	t_color	color;

	if (options.ambient_occlusion) /* ambient occlusion */
	{
		color = ambient_occlusion_l(scene, sampler_manager, &options.ambient_occluder_sampler, shade_rec, seed);
		// color = color_multi(color, material.color);
	}
	else /* compute constant ambient light using ka coefficent of the materail */
	{
		color = lambertian_rho(material.ka,
								get_color(scene.instance_manager.tex_mngr,
										material, &shade_rec));
		color_tmp = get_light_radiance(scene.ambient_light);
		color = color_multi(color, color_tmp);
	}

	// color.r = 0.0f;
	// color.g = 0.0f;
	// color.b = 0.0f;

	/* compute sahding for each light source */
	for (int i = 0; i < scene.nlights; i++)
	{
		bool	in_shadow = false;

		/* compute light direction at hit point */
		light_direction = get_light_direction(scene.lights[i], shade_rec);

		/* multiplying by 0.999f to avoid self shadowing error */
		t_ray	shadow_ray = { .origin = shade_rec.hit_point + 1e-1f * shade_rec.normal,
							   .direction = light_direction };

		if (options.shadows)
			in_shadow = shadow_hit(scene, scene.lights[i], shadow_ray, shade_rec);

		if (!in_shadow)
		{
			/* compute angle between normal at the hit point and light direction */
			dirdotn = dot(shade_rec.normal, light_direction);

			/* if angle > 0 then hit point is receivingl light */
			if (dirdotn > 0.0f)
			{
				/* compute diffuse color */
				color_tmp = lambertian_f(material.kd,
								get_color(scene.instance_manager.tex_mngr,
										material, &shade_rec));

				/* compute how much light the point receives depends on angle between the normal at this point and light direction */
				color_tmp.r = scene.lights[i].ls * scene.lights[i].color.r
							* color_tmp.r * dirdotn;
				color_tmp.b = scene.lights[i].ls * scene.lights[i].color.b
							* color_tmp.b * dirdotn;
				color_tmp.g = scene.lights[i].ls * scene.lights[i].color.g
							* color_tmp.g * dirdotn;
				color = color_sum(color_tmp, color);
			}
		}
	}
	return (color);
}

/*
lights can optionally cast shadows
objects can optionally cast shadows
materials can optionally cast shadows
*/
//note: we don't need pass an object. We can pass  only material and compute normal
//in function before
inline t_color		shade_object(t_material material,
						t_shade_rec shade_rec,
						t_scene scene,
						t_sampler_manager sampler_manager,
						t_rt_options options,
						uint2 *seed)
{
	t_color	color;

	if (material.type == phong)
		color = shade_phong(material, shade_rec, scene, sampler_manager, options, seed);
	else
		color = shade_matte(material, shade_rec, scene, sampler_manager, options, seed);
	return color;
}

inline t_color		shade_material(t_scene scene,
							t_sampler_manager sampler_manager,
							t_material material,
							t_shade_rec shade_rec,
							t_rt_options options,
							uint2 *seed)
{
	t_color	color;

	if (material.type == phong)
		color = shade_phong(material, shade_rec, scene, sampler_manager, options, seed);
	else
		color = shade_matte(material, shade_rec, scene, sampler_manager, options, seed);
	return color;
}

t_color		area_light_shade_phong(t_material material,
									t_shade_rec shade_rec,
									t_scene scene,
									t_sampler_manager sampler_manager,
									t_rt_options options,
									uint2 *seed)
{
	float4	light_direction;
	float	dirdotn;
	t_color	color_tmp;
	t_color	color;

	/* revert camera ray for specular light */
	shade_rec.ray.direction = -shade_rec.ray.direction;

	if (options.ambient_occlusion) /* ambient occlusion */
	{
		color = ambient_occlusion_l(scene, sampler_manager, &options.ambient_occluder_sampler, shade_rec, seed);
		// color = color_multi(color, material.color);
	}
	else /* compute constant ambient light using ka coefficent of the materail */
	{
		// color = lambertian_rho(material.ka, material.color);
		color_tmp = get_light_radiance(scene.ambient_light);
		color = color_multi(color, color_tmp);
	}

	/* compute sahding for each light source */
	for (int i = 0; i < scene.nlights; i++)
	{
		bool	in_shadow = false;

		/* compute light direction at hit point */
		light_direction = get_light_direction(scene.lights[i], shade_rec);

		/* multiplying by 0.999f to avoid self shadowing error */
		t_ray	shadow_ray = {.origin = shade_rec.hit_point * 0.999f, .direction = light_direction };

		if (options.shadows)
			in_shadow = shadow_hit(scene, scene.lights[i], shadow_ray, shade_rec);

		if (!in_shadow)
		{
			/* compute angle between normal at the hit point and light direction */
			dirdotn = dot(shade_rec.normal, light_direction);

			/* if angle > 0 then hit point is receivingl light */
			if (dirdotn > 0.0f)
			{
				/* compute glossy_specular coefficient */
				float a = glossy_specular_f(shade_rec.ray.direction, shade_rec.normal, light_direction, material.ks, material.exp) ;

				/* compute diffuse color */
				// color_tmp = lambertian_f(material.kd, material.color);

				/* sum lambertian color and glossy specular color */
				color_tmp = color_sum(color_tmp, float_color_multi(a, scene.lights[i].color));

				/* compute how much light the point receives depends on angle between the normal at this point and light direction */
				color_tmp.r = clamp(scene.lights[i].ls * scene.lights[i].color.r * color_tmp.r / 255.0f * dirdotn, 0.0f, 255.0f);
				color_tmp.b = clamp(scene.lights[i].ls * scene.lights[i].color.b * color_tmp.b / 255.0f * dirdotn, 0.0f, 255.0f);
				color_tmp.g = clamp(scene.lights[i].ls * scene.lights[i].color.g * color_tmp.g / 255.0f * dirdotn, 0.0f, 255.0f);
				color = color_sum(color_tmp, color);
			}
		}
	}
	return (color);
}

t_color		area_light_shade_emissive(t_material material,
									t_shade_rec shade_rec
									)
{
	// if (shade_rec.normal * shade_rec.ray.direction > 0.0f)
	// {
	// 	;
	// 	// return (float_color_multi(material,
	// }
}

t_color		area_light_shade(t_material material,
							t_shade_rec shade_rec,
							t_scene scene,
							t_sampler_manager sampler_manager,
							t_rt_options render_options,
							uint2 *seed)
{
	t_color	color;

	// if (material.type == matte)
	// {
	// }
	// else if (material.type == emissive)
	// {
	// }

	// if (material.type == phong)
	// 	area_light_shade_phong(material, shade_rec, scene, sampelr_manager, render_options, seed);
	// else if (material.type == emissive)

	return (color);
}

float4	get_reflected_vector(float4 l, float4 n)
{
	float4	r;

	r = l - 2 * dot(l, n) * n;
	return normalize(r);
}

inline t_material	get_instance_material(t_instance_manager instance_manager,
											t_instance instance)
{
	return (instance.material);
}

inline t_instance	get_instance(t_instance_manager instance_manager, int id)
{
	return instance_manager.instances[id];
}

inline t_matrix	get_instance_matrix(t_instance_manager instance_manager,
									t_instance	instance)
{
	return (instance_manager.matrices[instance.matrix_id]);
}

inline t_obj		get_object_info(t_instance_manager instance_manager,
									t_instance instance)
{
	return (instance_manager.objects[instance.object_id]);
}

inline t_triangle	get_triangle_info(t_instance_manager instance_manager,
										t_instance instance)
{
	return (instance_manager.triangles[instance.object_id]);
}

bool	bvh_intersection(t_scene scene, t_shade_rec *shade_rec)
{
	t_hit_info		last_hit_info;
	int				node_id = 0;

	last_hit_info.t = K_HUGE_VALUE;
	shade_rec->id = -1;

	float	tmin = K_HUGE_VALUE;
	while (node_id != -1)
	{
		t_bvh_node current_node = scene.bvh[node_id];

		if (bbox_intersection(shade_rec->ray, current_node.aabb))
		{
			if (current_node.instance_id == -1)
			{
				node_id++;
			}
			else /* leaf node*/
			{
				t_instance instance = get_instance(scene.instance_manager,
													current_node.instance_id);
				if (instance_hit(scene.instance_manager, instance,
								&tmin, shade_rec))
				{
					shade_rec->id = current_node.instance_id;

					shade_rec->hit_point = shade_rec->ray.direction * tmin + shade_rec->ray.origin;
				}
				node_id = current_node.next;
			}
		}
		else
		{
			node_id = current_node.next;
		}
	}
	return (shade_rec->id > -1);
}

//TODO(dmelessa): shading both sides of surface à¸¢à¸‡14
bool	scene_intersection(t_scene scene, t_ray ray, t_shade_rec *shade_rec)
{

	bool ret = bvh_intersection(scene, shade_rec);

	return (ret);

	/* old code for bruteforcing*/
	// t_hit_info	last_hit_info;

	// last_hit_info.t = K_HUGE_VALUE;

	// shade_rec->id = -1;
	// for (int i = 0; i < scene.instance_manager.ninstances; i++)
	// {
	// 	t_instance instance = get_instance(scene.instance_manager, i);
	// 	if (instance_hit(scene.instance_manager, ray, &shade_rec->hit_info, instance)
	// 		&& shade_rec->hit_info.t < last_hit_info.t)
	// 	{
	// 		last_hit_info = shade_rec->hit_info;
	// 		shade_rec->id = i;
	// 	}
	// }
	// shade_rec->hit_info = last_hit_info;
	// return (shade_rec->id > -1);
}

#define maximum_tree_depth 16

t_color	ray_trace(t_ray ray, t_scene scene, t_rt_options options, t_sampler_manager sampler_manager, uint2 *seed)
{
	int			local_id = get_local_id(0);
	t_shade_rec	shade_rec;

	/* computed color */
	t_color		color = options.background_color;
	color.r = 0.0f;
	color.g = 0.0f;
	color.b = 0.0f;

	float		color_coef = 1.0f;
	t_color		clr_coef;
	clr_coef.r = 1.0f;
	clr_coef.g = 1.0f;
	clr_coef.b = 1.0f;

	/* material of hit object*/
	t_material	instance_material;

	bool		continue_loop = true;
	uchar		tree_depth = 0;

	while (continue_loop)
	{
		tree_depth++;
		shade_rec.ray = ray;
		if (scene_intersection(scene, ray, &shade_rec))
		{
			t_instance	instance = scene.instance_manager.instances[shade_rec.id];

			/* if normal is not directed to us then we reverse normal*/
			shade_rec.normal = dot(shade_rec.normal, ray.direction) < 0.0f ?
				shade_rec.normal : -shade_rec.normal;

			instance_material = get_instance_material(scene.instance_manager,
														instance);
			// return get_color(scene.instance_manager.tex_mngr, instance_material, &shade_rec);
			/* shade material at hit point and accumulate color */
			color = color_sum(color,
							float_color_multi(color_coef,
											shade_material(scene,
															sampler_manager,
															instance_material,
															shade_rec, options,
															seed)));

			if (instance_material.is_reflective
				&& tree_depth < 64 && color_coef > 0.01f)
			{
				ray.origin = shade_rec.hit_point + 1e-2f * shade_rec.normal;
				ray.direction = get_reflected_vector(-ray.direction,
													shade_rec.normal);
				color_coef *= instance_material.kr;
			}
			else
				continue_loop = false;
		}
		else /* no hit */
		{
			continue_loop = false;
		}
	};
	return (color);
}


float	GPURnd(float4 *state)
{
	float4 q = (float4)(1225.0f, 1585.0f, 2457.0f, 2098.0f);
	float4 r = (float4)(1112.0f, 367.0f, 92.0f, 265.0f);
	float4 a = (float4)(3423.0f, 2646.0f, 1707.0f, 1999.0f);
	float4 m = (float4)(4194287.0f, 4194277.0f, 4194191.0f, 4194167.0f);

	float4 state_copy = *state;
	float4 beta = floor(state_copy / q);
	float4 p = a * (state_copy - beta * q) - beta * r;
	beta = (sign(-p) + (float4)(1.0f)) * (float4)(0.5f) * m;
	state_copy = p + beta;

	*state = state_copy;
	float res;
	return fract(dot(state_copy / m, (float4)(1.0f, -1.0f, 1.0f, -1.0f)), &res);
}

float4	cosine_sampler_hemisphere(float4 *state)
{
	float e1 = GPURnd(state);
	float e2 = GPURnd(state);
	float theta = sqrt(e1);
	float phi = 2 * M_PI * e2;

	return (float4)(cos(phi) * theta, sin(phi) * theta, sqrt(1 - e1), 0.0f);
}

float4	random_cosin_direction(float4 *state)
{
	float r2 = GPURnd(state);
	float z = sqrt(1.0f - r2);
	float r1 = GPURnd(state);
	float phi = 2.0f * M_PI * r1;
	float x = cos(phi) * 2.0f * sqrt(r2);
	float y = sin(phi) * 2.0f * sqrt(r2);
	return (float4)(x, y, z, 0.0f);
}

float4	random_in_unit_sphere(float4 *state)
{
	float	u = GPURnd(state);
	float	v = GPURnd(state);
	float	theta = u * 2.0f * M_PI;
	float	phi = acos(2.0f * v - 1.0f);
	float	r = cbrt(GPURnd(state));
	float	sinTheta = sin(theta);
	float	cosTheta = cos(theta);
	float	sinPhi = sin(phi);
	float	cosPhi = cos(phi);
	float	x = r * sinPhi * cosTheta;
	float	y = r * sinPhi * sinTheta;
	float	z = r * cosPhi;
	return ((float4)(x, y, z, 0.0f));

	float4 tg = (float4)(GPURnd(state), GPURnd(state), GPURnd(state), 0.0f)
			* 2.0f - (float4)(1.0f, 1.0f, 1.0f, 0.0);
	if (dot(tg, tg) > 1.0f) tg = tg / 2.0f;
	if (dot(tg, tg) > 1.0f) tg = (float4)(GPURnd(state),
				GPURnd(state), GPURnd(state), 0.0f) * 2.0f
				- (float4)(1.0f, 1.0f, 1.0f, 0.0);
	if (dot(tg, tg) > 1.0f) tg = (float4)(GPURnd(state),
				GPURnd(state), GPURnd(state), 0.0f) * 2.0f
				- (float4)(1.0f, 1.0f, 1.0f, 0.0);
	if (dot(tg, tg) > 1.0f) tg = (float4)(GPURnd(state),
				GPURnd(state), GPURnd(state), 0.0f) * 2.0f
				- (float4)(1.0f, 1.0f, 1.0f, 0.0);
	if (dot(tg, tg) > 1.0f) tg = (float4)(GPURnd(state),
				GPURnd(state), GPURnd(state), 0.0f) * 2.0f
				- (float4)(1.0f, 1.0f, 1.0f, 0.0);
	if (dot(tg, tg) > 1.0f) tg = (float4)(GPURnd(state),
				GPURnd(state), GPURnd(state), 0.0f) * 2.0f
				- (float4)(1.0f, 1.0f, 1.0f, 0.0);
	if (dot(tg, tg) > 1.0f) tg = (float4)(GPURnd(state),
				GPURnd(state), GPURnd(state), 0.0f) * 2.0f
				- (float4)(1.0f, 1.0f, 1.0f, 0.0);
	if (dot(tg, tg) > 1.0f) tg = (float4)(GPURnd(state),
				GPURnd(state), GPURnd(state), 0.0f) * 2.0f
				- (float4)(1.0f, 1.0f, 1.0f, 0.0);
	if (dot(tg, tg) > 1.0f) tg = (float4)(GPURnd(state),
				GPURnd(state), GPURnd(state), 0.0f) * 2.0f
				- (float4)(1.0f, 1.0f, 1.0f, 0.0);
	if (dot(tg, tg) > 1.0f) tg = (float4)(GPURnd(state),
				GPURnd(state), GPURnd(state), 0.0f) * 2.0f
				- (float4)(1.0f, 1.0f, 1.0f, 0.0);
	if (dot(tg, tg) > 1.0f) tg = (float4)(GPURnd(state),
				GPURnd(state), GPURnd(state), 0.0f) * 2.0f
				- (float4)(1.0f, 1.0f, 1.0f, 0.0);
	if (dot(tg, tg) > 1.0f) tg = (float4)(GPURnd(state),
				GPURnd(state), GPURnd(state), 0.0f) * 2.0f
				- (float4)(1.0f, 1.0f, 1.0f, 0.0);
	return tg;
}

bool	refract(float4 v, float4 n, float ni_over_nt, float4 *refracted)
{
	float	dt = dot(v, n);
	float	disc = 1.0f - ni_over_nt * ni_over_nt * (1 - dt * dt);
	bool	ret;

	ret = false;
	if (disc > 0.0f)
	{
		*refracted = ni_over_nt * (v - n * dt) - n * sqrt(disc);
		ret = true;
	}
	return (ret);
}

float	schlick(float cosine, float n)
{
	float r0 = (1.0f - n) / (1.0f + n);

	r0 = r0 * r0;
	return (r0 + (1.0f - r0) * pow((1.0f - cosine), 5.0f));
}

/**
** todo: add to material fuzz
*/
bool	metal_scatter(t_texture_manager texture_manager,
					t_material material,
					t_shade_rec *shade_rec,
					t_color *attenuation,
					float4 *state)
{
	shade_rec->normal = dot(shade_rec->normal, shade_rec->ray.direction) < 0.0f ?
							shade_rec->normal : -shade_rec->normal;
	float4 reflected = get_reflected_vector(shade_rec->ray.direction, shade_rec->normal);

	shade_rec->ray.origin = shade_rec->hit_point + 0.1f * shade_rec->normal;
	shade_rec->ray.direction = reflected
							+ 0.0f * random_in_unit_sphere(state);

	*attenuation = float_color_multi(
						material.kr,
						get_color(texture_manager, material, shade_rec));
	// *attenuation = float_color_multi(material.kr, material.color);
	return (dot(reflected, shade_rec->normal) > 0.0f);
}

bool	lambertian_scater(t_texture_manager texture_manager,
						t_material material,
						t_shade_rec *shade_rec,
						t_color *attenuation,
						float4 *state)
{
	float4 target = shade_rec->hit_point
					+ shade_rec->normal
					+ random_in_unit_sphere(state);

	shade_rec->ray.origin = shade_rec->hit_point + 1e-2f * shade_rec->normal;
	shade_rec->ray.direction = normalize(target - shade_rec->hit_point);

	*attenuation = get_color(texture_manager, material, shade_rec);
	// *attenuation = float_color_multi(material.kd, material.color);
	return (true);
}

bool	dielectric_scatter2(t_material material,
							t_shade_rec *shade_rec,
							t_color *attenuation,
							float4 *state)
{
	float4	outward_normal;
	float4	reflected = get_reflected_vector(shade_rec->ray.direction, shade_rec->normal);
	float	ni_over_nt;
	*attenuation = (t_color){1.0f, 1.0f, 1.0f, 0.0f};
	float4	refracted;
	if (dot(shade_rec->ray.direction, shade_rec->normal) > 0.0f)
	{
		outward_normal = -shade_rec->normal;
		ni_over_nt = material.kt;
	}
	else
	{
		outward_normal = shade_rec->normal;
		ni_over_nt = 1.0f / material.kt;
	}
	if (refract(shade_rec->ray.direction,
				outward_normal,
				ni_over_nt,
				&refracted))
	{
		shade_rec->ray.direction = refracted;
		shade_rec->ray.origin = shade_rec->hit_point - 1e-2f * outward_normal;
	}
	else
	{
		shade_rec->ray.direction = reflected;
		shade_rec->ray.origin = shade_rec->hit_point - 1e-2f * outward_normal;
		return (true); //!!!!!!!!!!!
	}
	return (true);
}

bool	dielectric_scatter(
							t_material material,
							t_shade_rec *shade_rec,
							t_color *attenuation,
							float4 *state)
{
	float4	outward_normal;
	float4	reflected = get_reflected_vector(shade_rec->ray.direction, shade_rec->normal);
	float	ni_over_nt;
	*attenuation = (t_color){1.0f, 1.0f, 1.0f, 0.0f};
	float4	refracted;
	float	reflect_prob;
	float	cosine;

	if (dot(shade_rec->ray.direction, shade_rec->normal) > 0.0f)
	{
		outward_normal = -shade_rec->normal;
		ni_over_nt = material.kt;
		cosine = material.kt * dot(shade_rec->ray.direction, shade_rec->normal)
				/ length(shade_rec->ray.direction);
	}
	else
	{
		outward_normal = shade_rec->normal;
		ni_over_nt = 1.0f / material.kt;
		cosine = -dot(shade_rec->ray.direction, shade_rec->normal)
				/ length(shade_rec->ray.direction);
	}

	if (refract(shade_rec->ray.direction,
				outward_normal,
				ni_over_nt,
				&refracted))
	{
		reflect_prob = schlick(cosine, material.kt);
	}
	else
	{
		reflect_prob = 1.0f;
	}

	if (GPURnd(state) < reflect_prob)
	{
		shade_rec->ray.origin = shade_rec->hit_point - 1e-2f * outward_normal;
		shade_rec->ray.direction = reflected;
	}
	else
	{
		shade_rec->ray.direction = refracted;
		shade_rec->ray.origin = shade_rec->hit_point - 1e-2f * outward_normal;
	}
	return (true);
}

bool	scatter(t_texture_manager texture_manager,
				t_material material,
				t_shade_rec *shade_rec,
				t_color *attenuation,
				float4 *state)
{
	if (material.type == matte)
	{
		return (lambertian_scater(texture_manager,
								material,
								shade_rec,
								attenuation,
								state));
	}
	else if (material.type == metal) //reflections
	{
		return (metal_scatter(texture_manager,
							material,
							shade_rec,
							attenuation,
							state));
	}
	else if (material.type == dielectric) //transparance
	{
		return (dielectric_scatter(material, shade_rec, attenuation, state));
	}
	else return false;
}

t_color	emitted(t_material material, t_shade_rec *shade_rec,
				float u, float v, float4 point)
{
	if (material.type == diffuse_light)
		return ((t_color){ .r = 3.0f, .g = 3.0f, .b = 3.0f });
	return ((t_color){ .r = 0.0f, .g = 0.0, .b = 0.0f });
}

/*
** SUffern path tracer
*/
t_color	path_tracer_suffern(t_ray ray, t_scene scene, t_rt_options options,
							t_sampler_manager sampler_manager, uint2 *seed)
{
	t_color	color = (t_color){ .r = 0.0f, .g = 0.0f, .b = 0.0f };

	t_shade_rec	shade_rec;
	shade_rec.ray = ray;

	int		depth = 0;

	bool	continue_loop = true;

	while (continue_loop)
	{
		depth = 0;

		if (scene_intersection(scene, ray, &shade_rec) && depth < 20)
		{
			
		}
	}
}

t_color	path_tracer2(t_ray ray, t_scene scene, t_rt_options options,
					t_sampler_manager sampler_manager, uint2 *seed,
					float4	*state)
{
	t_color	color;
	color.r = 0.0f;
	color.g = 0.0f;
	color.b = 0.0f;

	t_color	cur_attenuation;
	cur_attenuation.r = 1.0f;
	cur_attenuation.g = 1.0f;
	cur_attenuation.b = 1.0f;

	bool continue_loop = 1;
	int	depth = 0;

	t_shade_rec	shade_rec;
	shade_rec.ray = ray;

	do	{
		depth++;
		if (scene_intersection(scene, ray, &shade_rec) && depth < 13
		&& cur_attenuation.r + cur_attenuation.g + cur_attenuation.b > 0.2f)
		{
			t_instance	instance = scene.instance_manager.instances[shade_rec.id];

			/* save ray for specular reflection */

			t_material material = get_instance_material(scene.instance_manager,
														instance);

			t_color	attenuation;
			t_color	emit = color_multi(cur_attenuation,
									emitted(material, &shade_rec,
											0, 0, shade_rec.hit_point));
			if (scatter(scene.instance_manager.tex_mngr,
						material,
						&shade_rec,
						&attenuation,
						state))
			{
				cur_attenuation = color_multi(cur_attenuation, attenuation);
				color = color_sum(emit, color);
			}
			else
			{
				color = color_sum(color, emit);
				continue_loop = false;
			}
		}
		else
		{
			continue_loop = false;
			color = color_sum(color,
						color_multi(cur_attenuation,
							(t_color){ 0., 0., 0., 0}));
		}
	} while (continue_loop);

	return (color);
}

void	build_from_w(float4 *const u, float4 *const v, float4 *const w,
					float4 const n)
{
	float4 a;

	*w = normalize(n);
	if (fabs(w->x) > 0.9f)
		a = (float4)(0.0f, 1.0f, 0.0f, 0.0f);
	else
		a = (float4)(1.0f, 0.0f, 0.0f, 0.0f);
	*v = normalize(cross(*w, a));
	*u = cross(*w, *v);
}

float4	local_dir(float4 const *const u,
				float4 const *const v,
				float4 const *const w,
				float4 const a)
{
	return a.x * *u + a.y * *v + a.z * *w;
}

bool	lambertian_scater2(t_texture_manager const texture_manager,
						t_material const material,
						t_shade_rec *const shade_rec,
						t_color *const attenuation,
						float *const pdf,
						float4 *const state)
{
	float4 u, v, w; // onb

	build_from_w(&u, &v, &w, shade_rec->normal);

	float4 direction = local_dir(&u, &v, &w, random_cosin_direction(state));

	float4	target = shade_rec->hit_point + shade_rec->normal
					+ random_in_unit_sphere(state);
	shade_rec->ray.origin = shade_rec->hit_point + 1e-2f * shade_rec->normal;
	shade_rec->ray.direction = normalize(direction);

	*attenuation = get_color(texture_manager, material, shade_rec);
	*pdf = dot(w, direction) / M_PI;

	return (true);
}

float	lambertian_pdf(t_shade_rec const *const shade_rec,
						t_ray const scattered_ray)
{
	float	cosine;

	cosine = dot(shade_rec->normal, scattered_ray.direction);

	if (cosine < 0.0f) cosine = 0;
	return (cosine / M_PI);
}

bool	scatter2(const t_texture_manager texture_manager,
				const t_material material,
				t_shade_rec *const shade_rec,
				t_color *const attenuation,
				float *const pdf,
				float4 *const state)
{
	if (material.type == matte)
	{
		return (lambertian_scater2(texture_manager, material, shade_rec,
						attenuation, pdf, state));
	}
	return false;
}

float	scattering_pdf(t_material const material,
					t_shade_rec *const shade_rec,
					t_ray const scattered_ray)
{
	if (material.type == matte)
	{
		return (lambertian_pdf(shade_rec, scattered_ray));
	}
	return 0.0f;
}

t_color	path_trace_pdf(t_ray ray, t_scene scene, t_rt_options options,
					t_sampler_manager sampler_manager, uint2 *seed,
					float4	*state)
{
	t_color	color = (t_color){0.0f, 0.0f, 0.0f};
	t_color	cur_attenuation;
	cur_attenuation.r = 1.0f;
	cur_attenuation.g = 1.0f;
	cur_attenuation.b = 1.0f;

	bool continue_loop = true;

	int	depth = 0;

	t_shade_rec	shade_rec;
	shade_rec.ray = ray;
	do
	{
		depth++;

		if (scene_intersection(scene, ray, &shade_rec) && depth < 20 && cur_attenuation.r + cur_attenuation.g + cur_attenuation.b > 0.05f)
		{
			t_instance	instance = scene.instance_manager.instances[shade_rec.id];

			t_material material = get_instance_material(scene.instance_manager,
													instance);

			t_color	attenuation;
			float	pdf;
			t_color	emit = emitted(material, &shade_rec,
									0, 0, shade_rec.hit_point);
			emit = color_multi(cur_attenuation, emit);
			if (scatter2(scene.instance_manager.tex_mngr,
						material,
						&shade_rec,
						&attenuation,
						&pdf,
						state))
			{
				cur_attenuation = color_multi(
									float_color_multi(
										scattering_pdf(material,
													&shade_rec,
													shade_rec.ray) / pdf,
										attenuation),
									cur_attenuation);
				color = color_sum(emit, color);
				ray = shade_rec.ray;
			}
			else
			{
				color = color_sum(color, emit);
				continue_loop = false;
			}
		}
		else
		{
			continue_loop = false;

			color = color_sum(color,
						color_multi(cur_attenuation,
							(t_color){ 0., 0., 0., 0}));
		}
	} while (continue_loop);

	return (color);
}


/**
**
*/
t_ray cast_camera_ray(t_camera camera, float x, float y,
					t_sampler_manager sampler_manager,
					t_sampler *camera_sampler, uint2 *seed,
					float4 *const state)
{
	t_ray	ray;
	float	px;
	float	py;
	float	pixel_size;

	pixel_size = camera.viewplane.pixel_size / camera.zoom;
	if (camera.normalized == true)
	{
		px = pixel_size * ((2.0f * x / camera.viewplane.width) - 1.0f);
		py = pixel_size * (1.0f - 2.0f * y / camera.viewplane.height);
	}
	else
	{
		px = pixel_size * (x - 0.5f * camera.viewplane.width);
		py = pixel_size * (0.5f * camera.viewplane.height - y) ;
	}

	if (camera.type == perspective)
	{
		ray.origin = camera.origin;
		ray.direction = px * camera.u + py  * camera.v - camera.d * camera.w; // camera coordinates
		ray.direction = normalize(ray.direction);
	}
	else if (camera.type == thin_lens)
	{
		float2 dp = sample_unit_disk(camera_sampler, sampler_manager.disk_samples, seed);
		// printf("#%d: %f %f\n", get_global_id(0), dp.x, dp.y);
		// dp.x = GPURnd(state);
		// dp.y = GPURnd(state);
		float2 lp = dp * camera.l; //lens_point
		ray.origin = camera.origin + camera.u * lp.x + camera.v * lp.y;
		px = px * camera.f / camera.d;
		py = py * camera.f / camera.d;
		ray.direction = (px - lp.x) * camera.u + (py - lp.y) * camera.v - camera.w * camera.f;
		ray.direction = normalize(ray.direction);
	}
	else if (camera.type == fisheye)
	{
		ray.origin = camera.origin;

		float	r_squared = px * px + py * py;
		if (r_squared <= 1.0f)
		{
			float r = sqrt(r_squared);
			float psi = r * camera.f * 0.0174532925199432957; // PI / 180 todo: make define
			float sin_psi = sin(psi);
			float cos_psi = cos(psi);
			float sin_alpha = py / r;
			float cos_alpha = px / r;

			ray.direction = sin_psi * cos_alpha * camera.u + sin_psi * sin_alpha * camera.v - cos_psi * camera.w;
		}
		else
			ray.direction = (float4)(0.0f, 0.0f, 0.0f, 0.0f);
	}
	else if (camera.type == spherical)
	{
		ray.origin = camera.origin;

		//compute the angles lambda and phi in radians
		float	lambda = px * camera.l * 0.0174532925199432957;
		float	psi = py * camera.f * 0.0174532925199432957;

		//compute the spherical azimuth and polar angles

		float	phi = M_PI - lambda;
		float	theta = 0.5f * M_PI - psi;

		float	sin_phi = sin(phi);
		float	cos_phi = cos(phi);
		float	sin_theta = sin(theta);
		float	cos_theta = cos(theta);

		ray.direction = sin_theta * sin_phi * camera.u + cos_theta * camera.v + sin_theta * cos_phi * camera.w;
	}
	/*
	** Стерео камера (два изображения с разных ракурсов рядом.
	** todo(dmelessa): поддержка разных типов камеры для стерео эффекта.
	*/
	else if (camera.type == stereo) //todo: rewrite paragraph 12
	{
		float r = 10.0f;
		float xx = r * tan(0.5f * camera.f * 0.0174532925199432957);

		/* Правый глаз */
		if (x < (camera.viewplane.width) * 0.5f - camera.l)
		{
			px = px + camera.viewplane.width / 4.0f;
			ray.origin = camera.origin + xx * camera.u;
			px = px - xx;
		}
		/* Левый глаз */
		else if (x > (camera.viewplane.width) * 0.5f + camera.l)
		{
			px = px - camera.viewplane.width / 4.0f;
			ray.origin = camera.origin - xx * camera.u;
			px = px + xx;
		}
		else
		{
			ray.direction = (float4)(0.0f, 0.0f, 0.0f, 0.0f);
			return (ray);
		}
		ray.direction = px * camera.u + py  * camera.v - camera.d * camera.w; // camera coordinates
		ray.direction = normalize(ray.direction);
	}
	return (ray);
}

void	init_scene(t_scene *scene,
					__constant t_instance *instances, int ninstances,
					__global t_obj *objects, int nobjects,
					__constant t_triangle *triangles, int ntriangles,
					__global t_matrix *matrices, int nmatrices,
					__constant t_light *lights, int nlights,
					__global t_bvh_node *bvh,

					__global t_texture *textures,
					__global float4 *ranvec,
					__global int *perm_x,
					__global int *perm_y,
					__global int *perm_z,

					t_camera camera, t_light ambient_light,
					t_ambient_occluder ambient_occluder)
{
	scene->instance_manager.instances = instances;
	scene->instance_manager.ninstances = ninstances;
	scene->instance_manager.objects = objects;
	scene->instance_manager.nobjects = nobjects;
	scene->instance_manager.triangles = triangles;
	scene->instance_manager.ntriangles = ntriangles;
	scene->instance_manager.matrices = matrices;
	scene->instance_manager.nmatrices = nmatrices;

	scene->instance_manager.tex_mngr.textures = textures;
	scene->instance_manager.tex_mngr.perlin_noise = ranvec;
	scene->instance_manager.tex_mngr.perm_x  = perm_x;
	scene->instance_manager.tex_mngr.perm_y = perm_y;
	scene->instance_manager.tex_mngr.perm_z = perm_z;

	scene->lights = lights;
	scene->nlights = nlights;
	scene->bvh = bvh;
	scene->camera = camera;
	scene->ambient_light = ambient_light;
	scene->ambient_occluder = ambient_occluder;
}

void	init_sampler_manager(t_sampler_manager *sampler_manager,
							__global t_sampler *samplers,
							__global float2 *samples,
							__global float2 *disk_samples,
							__global float3 *hemisphere_samples)
{
	sampler_manager->samplers = samplers;
	sampler_manager->samples = samples;
	sampler_manager->disk_samples = disk_samples;
	sampler_manager->hemisphere_samples = hemisphere_samples;
}

float		hash(float seed)
{
	float res;
	return fract(sin(seed) * 43758.5453123, &res);
}

/*
** Новый кернел.
** Поскольку драйвер убивает кернел если он выполняется дольше чем 0,5 секунды,
** нам надо  его уменьшить. При каждом вызове будет считать по одной точке антиалиасинга.
** В дальнейшем когда будут сделаны материалы / преломления / отражения можно будет еще
** больше разбить кернел чтобы избежать дивергенции кода.
*/												//Pos of argument on host
__kernel  __attribute__((work_group_size_hint(32, 1, 1)))
void main_kernel(__global t_color *image,	//0
				int step,						//1

				__constant t_instance *instances, int ninstances, //2, 3
				__global t_obj *objects, int nobjects,		//4, 5
				__constant t_triangle *triangles, int ntriangles, //6, 7
				__global t_matrix *matrices, int nmatrices,	//8, 9
				__constant t_light *lights, int nlights,		//10, 11
				t_camera camera,		//12
				t_light ambient_light,	//13
				t_ambient_occluder ambient_occluder, //14

				__global t_bvh_node	*bvh, //15

				t_rt_options options, //16

				__global t_sampler *samplers, //17
				__global float2 *samples, //18
				__global float2 *disk_samples,	//19
				__global float3 *hemisphere_samples, //20
				uint num,	//21

				__global t_texture *textures, //22
				__global float4 *ranvec,	//23
				__global int *perm_x,		//24
				__global int *perm_y,		//25
				__global int *perm_z)		//26
{
	int					global_id;
	int					x;
	int					y;
	uint2				seed;
	t_scene				scene;
	t_sampler_manager	sampler_manager;

	t_ray				ray;
	t_color				color;
	t_sampler			camera_sampler;
	t_sampler			ao_sampler;

	/* Инициализируем нужные переменные и структуры */
	global_id = get_global_id(0);
	if (global_id == 0)
		printf("Rendering: %f%%\n", step / options.spp * 100.0f);
	x = global_id % camera.viewplane.width;
	y = global_id / camera.viewplane.width;

	seed.x = global_id + x + num;
	seed.y = y + get_local_id(0) + get_group_id(0);
	seed.y = random(&seed);

	float4 state;
	float2 s;

	s.x = seed.x;
	s.y = seed.y / ((float)num + 1.0f) * 43534.0f - num;

	state.x = hash(s.x + seed.x);
	state.y = hash(s.y + state.x);
	state.z = hash(state.x + state.y);
	state.w = hash(num + s.y - state.x * state.y);
	GPURnd(&state);
	// GPURnd(&state);
	// GPURnd(&state);

	init_scene(&scene,
				instances, ninstances, objects, nobjects,
				triangles, ntriangles, matrices, nmatrices,
				lights, nlights, bvh,
				textures, ranvec, perm_x, perm_y, perm_z,
				camera, ambient_light, ambient_occluder);

	init_sampler_manager(&sampler_manager, samplers, samples, disk_samples, hemisphere_samples);

	/* получаем семплер для антиалиасинга и текущий шаг. */
	ao_sampler = get_sampler(sampler_manager, options.aa_id);
	ao_sampler.count = global_id * ao_sampler.num_samples + step;

	/* Если это не первый шаг, то считаем прыжок для семплеров */
/* 	if (step != 0)
	{ */
		ao_sampler.jump = ((num + random(&seed)) % ao_sampler.num_sets) * ao_sampler.num_samples;
		options.ambient_occluder_sampler.jump = (random(&seed) % options.ambient_occluder_sampler.num_sets) * options.ambient_occluder_sampler.num_samples;
/* 	}
	else */ if (options.reset == 1)
	{
		image[global_id] = (t_color){.r = 0.0f, .g = 0.0f, .b = 0.0f};
	}

	/* */
	float2	sp = sample_unit_square(&ao_sampler, sampler_manager.samples, &seed);
	float	dx = x + GPURnd(&state);
	float	dy = y + GPURnd(&state);

	if (scene.camera.type == thin_lens)
	{
		camera_sampler = get_sampler(sampler_manager, scene.camera.sampler_id);
		camera_sampler.count = global_id * camera_sampler.num_samples + step;
		if (step != 0)
			camera_sampler.jump = ((num + random(&seed)) % camera_sampler.num_sets) * camera_sampler.num_samples;
	}

	ray = cast_camera_ray(scene.camera, dx, dy, sampler_manager, &camera_sampler, &seed, &state);

	color = ray_trace(ray, scene, options, sampler_manager, &seed);

	// color = path_tracer2(ray, scene, options, sampler_manager, &seed, &state);

	image[global_id] = color_sum(image[global_id], color);
}

// typedef union
// {
// 	struct
// 	{
// 		char b;
// 		char g;
// 		char r;
// 		char a;
// 	};
// 	int	value;
// }	int_color;

__kernel void translate_image(__global float4 *rgb_image,
							__global uchar4 *result_image,
							float num_samples)
{
	int				global_id = get_global_id(0);
	float4			color;

	color = rgb_image[global_id];
	// color = rgb_image[global_id] / num_samples;

	uchar4 old = result_image[global_id];

	float4 a;
	a.x = old.x / 255.99f;
	a.y = old.y / 255.99f;
	a.z = old.z / 255.99f;
	a.w = old.w / 255.99f;

	// float4 c = (a + color) / (num_samples + 1);
	// float4 c = mix(color, a, 0.5f);
	// float4 max_v = max(a, color);

	// uchar4 out = convert_uchar4_sat_rte(sqrt(c) * 255.00f);

	// if (global_id == 0)
	// 	printf("%v3f || %v3f || %v3f\n", a, color, c);
	uchar4 out = convert_uchar4_sat_rte(sqrt(color / (float)num_samples) * 255.99f);

	result_image[global_id] = out;
}

