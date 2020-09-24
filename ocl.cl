/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 19:36:22 by dmelessa          #+#    #+#             */
/*   Updated: 2020/09/23 15:36:32 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H

# include "types.h"
# include "camera.h"
# include "objects.h"
# include "material.h"
# include "light.h"
# include "sampler.h"
# include "color.h"
# include "instance.h"
# include "bvh.h"

# define DEFAULT_WIDTH 1200
# define DEFAULT_HEIGHT 600
# define WORK_GROUP_SIZE 32

typedef struct s_render_options		t_render_options;

struct				s_render_options
{
	t_sampler		ambient_occluder_sampler;
	cl_int			ambient_occlusion;

	t_color			background_color;

	cl_int			depth;

	cl_int			shadows;

	cl_int			area_lightning;

	cl_int			sampler_id; //anti-aliasing sampler
};

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_rt.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 00:29:53 by dmelessa          #+#    #+#             */
/*   Updated: 2020/09/23 23:31:54 by dmelessa         ###   ########.fr       */
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

typedef struct				s_instance_manager
{
	__constant t_instance	*instances;
	__global t_obj			*objects;
	__constant t_triangle	*triangles;
	__global t_matrix		*matrices;
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
						 t_render_options render_options,
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
	printf("\t\tColor:\t%f %f %f| %d\n", material.color.r,
		material.color.g, material.color.b,
		((int)(material.color.r * 255) << 16) + ((int)(material.color.g * 255) << 8) + material.color.b);
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

	offset = 0;
	for (i = 0; i < sampler_id; i++)
	{
		tmp = sampler_manager.samplers[i];
		offset += tmp.num_sets * tmp.num_samples;
	}
	tmp = sampler_manager.samplers[i];
	tmp.offset = offset;
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


/**
**
*/
t_ray cast_camera_ray(t_camera camera, float x, float y, t_sampler_manager sampler_manager,
					t_sampler *camera_sampler, uint2 *seed)
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

bool	box_intersection(t_ray ray, t_obj box, t_hit_info *hit_info)
{
	int	face_in;
	int	face_out;

	float ox = ray.origin.x;
	float oy = ray.origin.y;
	float oz = ray.origin.z;
	float dx = ray.direction.x;
	float dy = ray.direction.y;
	float dz = ray.direction.z;
	float tx_min, ty_min, tz_min;
	float tx_max, ty_max, tz_max;
	float a = 1.0f / dx;

	t_bbox bbox; /* = box.bounding_box; */

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

	float	t0, t1;
	if (tx_min > ty_min)
	{
		t0 = tx_min;
		face_in = (a >= 0.0f) ? 0 : 3;
	}
	else
	{
		t0 = ty_min;
		face_in = (b >= 0.0f) ? 1 : 4;
	}
	if (tz_min > t0)
	{
		t0 = tz_min;
		face_in = (c >= 0.0f) ? 2 : 5;
	}

	if (tx_max < ty_max)
	{
		t1 = tx_max;
		face_out = (a > 0.0f) ? 3 : 0;
	}
	else
	{
		t1 = ty_max;
		face_out = (b > 0.0f) ? 4 : 1;
	}
	if (tz_max < t1)
	{
		t1 = tz_max;
		face_out = (c > 0.0f) ? 5 : 2;
	}

	if (t0 < t1 && t1 > EPSILON)
	{
		if (t0 > EPSILON)
		{
			hit_info->t = t0;
			hit_info->m = face_in;
		}
		else
		{
			hit_info->t = t1;
			hit_info->m = face_out;
		}
		return (true);
	}
	return (false);
}

bool	generic_sphere_instersection(t_ray ray, t_obj sphere, t_hit_info *hit_info)
{
	float4 L = ray.origin;
	float a = dot(ray.direction, ray.direction);
	float b = 2.0f * dot(ray.direction, L); //b/2
	float c = dot(L, L) - 1.0f;
	float disc = b * b - 4.0f * a * c; // DISC = (b/2)^2-ac

	if (disc < 0.0f)
		return false;
	disc = sqrt(disc);
	hit_info->t = (-b - disc) / (2.0f * a);
	if (hit_info->t < 0.0f)
	{
		hit_info->t = (-b + disc) / (2.0f * a);
		if (hit_info->t < 0.0f)
			return false;
	}
	return true;
}

bool	sphere_intersection(t_ray ray, t_obj sphere, t_hit_info *hit_info)
{
#if 1 // geometric solution

	float4	L = sphere.origin - ray.origin; //1
	float	tca = dot(L, ray.direction); //1 + 4
	if (tca < 0.0f)
		return false;

	float	d2 = dot(L, L) - tca * tca; //5 + 4 + 1 + 1
	if (d2 > sphere.r2) //r^2 should be precomputed
		return false;

	float	thc = sqrt(sphere.r2 - d2); // 11 + 6
	float	t = tca - thc; // 18
	if (t < 0.0f)
	{
		t = tca + thc; //19
		if (t < 0.0f)
			return false;
	}
	hit_info->t = t;
	return (true);

#elif 1// analytic solution

	float4 L = sphere.origin - ray.origin;
	float a = 1; //NOTE: if ray.direction normalized!
	float b = dot(ray.direction, L); //b/2
	float c = dot(L, L) - sphere.r2;
	float disc = b * b - c; // DISC = (b/2)^2-ac

	if (disc < 0.0f)
		return false;
	a = sqrt(disc);
	hit_info->t = b - a;
	if (hit_info->t < 0.0f)
	{
		hit_info->t = b + a;
		if (hit_info->t < 0.0f)
			return false;
	}
	return true;
#endif
}

bool	generic_plane_intersection(t_ray ray, t_hit_info *hit_info)
{
	bool	ret = false;
	float	denom = dot(ray.direction, (float4)(0.0f, 1.0f, 0.0f, 0.0f));
	float	t;

	if (denom != 0.0f)
	{
		t = dot(-ray.origin, (float4)(0.0f, 1.0f, 0.0f, 0.0f));
		if (t * denom > 0.0f)
		{
			t = t / denom;
			if (t >= EPSILON)
			{
				hit_info->t = t;
				hit_info->dv = denom;
				ret = true;
			}
		}
	}
	return (ret);
}

bool	plane_intersection(t_ray ray, t_obj plane, t_hit_info *hit_info)
{
	float4	a;
	float	t;
	float	denom;
	bool	ret;

	ret = false;
	denom = dot(ray.direction, (float4)(0.0f, 1.0f, 0.0f, 0.0f)/* plane.direction */);
	if (denom != 0)
	{
		a = /* plane.origin */ -ray.origin;
		t = dot(a, (float4)(0.0f, 1.0f, 0.0f, 0.0f)/* plane.direction */);
		if (t * denom > 0.0f) //different signes
		{
			hit_info->t = t / denom;
			if (hit_info->t >= EPSILON)
			{
				hit_info->dv = denom;
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

bool	rectangle_intersection(t_ray ray, t_obj rectangle, t_hit_info *hit_info)
{
	float4	d;
	float	t;
	float	denom;
	bool	ret;

	ret = false;
	denom = dot(ray.direction, rectangle.normal);
	if (denom != 0.0f)
	{
		d = rectangle.origin - ray.origin;
		t = dot(d, rectangle.normal);
		if (t * denom > 0.0f)
		{
			hit_info->t = t / denom;

			if (hit_info->t >= EPSILON)
			{
				float4 point =  hit_info->t * ray.direction + ray.origin;
				d = point - rectangle.origin;

				float ddota = dot(d, rectangle.direction);
				if (ddota < 0.0f || ddota > rectangle.r)
					return (false);

				float ddotb = dot(d, rectangle.dir2);
				if (ddotb < 0.0f || ddotb > rectangle.r2)
					return (false);
				ret = true;
			}
		}
	}
	return (ret);
}

/*
** TODO(dmelessa): cap cylinder with discs
*/
 bool cylinder_intersection(t_ray ray, t_obj cylinder, t_hit_info *hit_info)
{
	float4	x;
	float	a, b, c, dv, xv, disc;

	x = ray.origin;
	dv = dot(ray.direction, (float4)(0.0f, 1.0f, 0.0f, 0.0f));
	xv = dot(x, (float4)(0.0f, 1.0f, 0.0f, 0.0f));
	a = dot(ray.direction, ray.direction) - dv * dv;
	b = 2.0f * (dot(ray.direction, x) - dv * xv);
	c = dot(x, x) - xv * xv - 1.0f;
	disc = b * b - 4.0f * a * c;
	// a = ray.direction.x * ray.direction.x + ray.direction.z * ray.direction.z;
	// b = 2.0f * (ray.origin.x * ray.direction.x + ray.origin.z *ray.direction.z);
	// c = ray.origin.x * ray.origin.x + ray.origin.x * ray.origin.z - 1.0f;
	// disc = b * b - 4.0f * a * c;
	if (disc >= EPSILON)
	{
		a *= 2.0f;
		disc = sqrt(disc);
		hit_info->t = (-b - disc) / a;
		if (hit_info->t < EPSILON)
			hit_info->t = (-b + disc) / a;
		if (hit_info->t > EPSILON)
		{
			if (cylinder.maxm > 0.0f)
			{
				float m1 = dv * hit_info->t + xv;
				if (m1 < cylinder.maxm && m1 > EPSILON)
				{
					hit_info->m = m1;
					hit_info->dv = dv;
					hit_info->xv = xv;
					return true;
				}
				hit_info->t = (-b + disc) / a;
				hit_info->m = dv * hit_info->t + xv;
				if (hit_info->m >= cylinder.minm + EPSILON &&
					hit_info->m <= cylinder.maxm)
				{
					return true;
				}
			}
			else
			{
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

 bool	torus_intersecion(t_ray ray, t_obj torus, t_hit_info *hit_info)
{
	double	coeffs[5];
	double	roots[4];
	float4	x;
	float	m, n, o, p, q, r2, R2;
	int		num_real_roots;

	x = ray.origin - torus.origin;
	m = dot(ray.direction, ray.direction);
	n = dot(ray.direction, x);
	o = dot(x, x);
	p = dot(ray.direction,(float4)(0.0f, 1.0f, 0.0f, 0.0f));
	q = dot(x,(float4)(0.0f, 1.0f, 0.0f, 0.0f));
	r2 = torus.r2 * torus.r2;
	R2 = torus.r * torus.r;

	coeffs[4] = m * m; //a
	coeffs[3] = 4.0f * n * m; //b
	coeffs[2] = 4.0f * n * n + 2.0f * m * o - 2.0f * (R2 + r2) * m + 4.0f * R2 * p * p;
	coeffs[1] = 4.0f * n * o - 4.0f * (R2 + r2) * n + 8.0f * R2 * p * q;
	coeffs[0] = o * o - 2.0f * (R2 + r2) * o + 4.0f * R2 * q * q + (R2 - r2) * (R2 - r2);
	num_real_roots = SolveQuartic(coeffs, roots);
	bool	intersect = false;
	float	t;

	if (num_real_roots == 0)
		return false;

	t = 10000.0f;
	for (int j = 0; j < num_real_roots; j++)
	{
		if (roots[j] > EPSILON)
		{
			intersect = true;
			if (roots[j] < t)
			{
				t = roots[j];
			}
		}
	}
	hit_info->t = t;
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

bool	is_intersect(t_ray ray, t_obj obj, t_hit_info *hit_info, t_type type)
{
	if (type == sphere)
	{
		return (generic_sphere_instersection(ray, obj, hit_info));
		return (sphere_intersection(ray, obj, hit_info));
	}
	else if (type == plane)
	{
		return (generic_plane_intersection(ray, hit_info));
		// return (plane_intersection(ray, obj, hit_info));
	}
	else if (type == cylinder)
	{
		return cylinder_intersection(ray, obj, hit_info);
	}
	else if (type == cone)
	{
		return (cone_intersection(ray, obj, hit_info));
	}
	else if (type == paraboloid)
	{
		return (paraboloid_intersection(ray, obj, hit_info));
	}
	else if (type == torus)
	{
		return torus_intersecion(ray, obj, hit_info);
	}
	else if (type == box)
	{
		return box_intersection(ray, obj, hit_info);
	}
	else if (type == disk)
	{
		return (disk_intersection(ray, obj, hit_info));
	}
	else if (type == rectangle)
	{
		return (rectangle_intersection(ray, obj, hit_info));
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

bool	instance_hit(t_instance_manager instance_mngr, t_ray ray, t_hit_info *hit_info, t_instance instance)
{
	t_obj	object = instance_mngr.objects[instance.object_id];
	ray = transform_ray(ray, instance_mngr.matrices[instance.matrix_id]);

	if (instance.type == triangle)
		return (triangle_intersection(ray,
									instance_mngr.triangles[instance.object_id],
									hit_info));
	else
		return (is_intersect(ray,
							object, hit_info,
							instance.type));;
}

float4	get_sphere_normal(float4 point, t_obj sphere)
{
	return (normalize(point - sphere.origin));
}

float4	get_plane_normal(t_obj plane, t_hit_info hit_info)
{
	return (float4)(0.0f, 1.0f, 0.0f, 0.0f);
	if (hit_info.dv < 0.0f)
		return (plane.direction);
	else
		return -(plane.direction);
}

float4	get_cylinder_normal(float4 point, t_obj cylinder, t_hit_info hit_info)
{
	return (normalize(point - cylinder.origin
		- dot(cylinder.direction, (point - cylinder.origin)) * cylinder.direction));
	float m = hit_info.dv * hit_info.t + hit_info.xv;
	return (normalize(point - cylinder.origin - cylinder.direction * m));
}

float4	get_cone_normal(float4 point, t_obj cone, t_hit_info hit_info)
{
	float m = hit_info.dv * hit_info.t + hit_info.xv;
	return (normalize(point - cone.origin - cone.r2 * cone.direction * m));
}

float4	get_paraboloid_normal(float4 point, t_obj paraboloid, t_hit_info hit_info)
{
	if (paraboloid.maxm > 0.0f)
		return (normalize(point - paraboloid.origin - paraboloid.direction *
			(hit_info.m + paraboloid.r)));
	float m = hit_info.dv * hit_info.t + hit_info.xv;
	return (normalize(point - paraboloid.origin - paraboloid.direction * (m +
		paraboloid.r)));
}

 float4	get_triangle_normal(t_triangle triangle)
{
	return (triangle.normal);
}

float4	get_torus_normal(float4 point, t_obj torus, t_hit_info hit_info)
{
		point = 1.0f * point;
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
		return (get_plane_normal(object, hit_info));
	}
	else if (type == cylinder)
	{
		return (get_cylinder_normal(point, object, hit_info));
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
		return (get_torus_normal(point, object, hit_info));
	}
	else if (type == box)
	{
		return (get_box_normal(point, object, hit_info));
	}
	else if (type == disk)
	{
		return (get_plane_normal(object, hit_info));
	}
	else if (type == rectangle)
		return object.normal;
}

float4	transform_normal(float4 normal, t_matrix matrix)
{
	// print_matrix(matrix);
	return (float4)(
		matrix.s0 * normal.x + matrix.s4 * normal.y + matrix.s8 * normal.z,
		matrix.s1 * normal.x + matrix.s5 * normal.y + matrix.s9 * normal.z,
		matrix.s2 * normal.x + matrix.s6 * normal.y + matrix.sA * normal.z,
		0.0f);
}

float4	get_instance_normal(t_instance_manager instance_mngr, t_shade_rec shade_rec)
{
	t_instance	instance;
	float4		normal;
	t_matrix	matrix;

	instance = instance_mngr.instances[shade_rec.id];
	if (instance.type == triangle)
		normal = get_triangle_normal(
					instance_mngr.triangles[instance.object_id]);
	else
		normal = get_object_normal(shade_rec.hit_point,
			instance_mngr.objects[instance.object_id],
			shade_rec.hit_info,
			instance_mngr.instances[shade_rec.id].type);
	matrix = instance_mngr.matrices[instance_mngr.instances[shade_rec.id].matrix_id];
	normal = transform_normal(normal, matrix);
	// printf("Normal %f %f %f %f", normal.x, normal.y, normal.z, normal.w);

	return normalize(normal);
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

bool		shadow_hit(t_scene scene, t_light light, t_ray shadow_ray, t_shade_rec shade_rec)
{
	float	t;
	float	d = distance(light.origin, shadow_ray.origin);

	int			node_id = 0;
	t_bvh_node	current_node;

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
				if (instance_hit(scene.instance_manager,
								shadow_ray,
								&shade_rec.hit_info,
								get_instance(scene.instance_manager, current_node.instance_id))
						&& shade_rec.hit_info.t < d)
					return (true);
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
						t_render_options options,
						uint2 *seed)
{
	float4	light_direction;
	float	dirdotn;
	t_color	color_tmp;
	t_color	color;

	// /* revert camera ray for specular light */
	shade_rec.ray.direction = -shade_rec.ray.direction;

	// if (options.ambient_occlusion) /* ambient occlusion */
	// {
	// 	color = ambient_occlusion_l(scene, sampler_manager, &options.ambient_occluder_sampler, shade_rec, seed);
	// 	color = color_multi(color, material.color);
	// }
	// else /* compute constant ambient light using ka coefficent of the materail */
	// {
	// 	color = lambertian_rho(material.ka, material.color);
	// 	color_tmp = get_light_radiance(scene.ambient_light);
	// 	color = color_multi(color, color_tmp);
	// }
	color.r = 0.0f;
	color.g = 0.0f;
	color.b = 0.0f;

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
				color_tmp = lambertian_f(material.kd, material.color);

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
						t_render_options options,
						uint2 *seed)
{
	float4	light_direction;
	float	dirdotn;
	t_color	color_tmp;
	t_color	color;

	if (options.ambient_occlusion) /* ambient occlusion */
	{
		color = ambient_occlusion_l(scene, sampler_manager, &options.ambient_occluder_sampler, shade_rec, seed);
		color = color_multi(color, material.color);
	}
	else /* compute constant ambient light using ka coefficent of the materail */
	{
		color = lambertian_rho(material.ka, material.color);
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
				/* compute diffuse color */
				color_tmp = lambertian_f(material.kd, material.color);

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
						t_render_options options,
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
							t_render_options options,
							uint2 *seed)
{
	t_color	color;

	if (material.type == phong)
		color = shade_phong(material, shade_rec, scene, sampler_manager, options, seed);
	else if (material.type == matte)
		color = shade_matte(material, shade_rec, scene, sampler_manager, options, seed);
	return color;
}

t_color		area_light_shade_phong(t_material material,
									t_shade_rec shade_rec,
									t_scene scene,
									t_sampler_manager sampler_manager,
									t_render_options options,
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
		color = color_multi(color, material.color);
	}
	else /* compute constant ambient light using ka coefficent of the materail */
	{
		color = lambertian_rho(material.ka, material.color);
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
				color_tmp = lambertian_f(material.kd, material.color);

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

t_color		area_light_shade(t_material material,
							t_shade_rec shade_rec,
							t_scene scene,
							t_sampler_manager sampler_manager,
							t_render_options render_options,
							uint2 *seed)
{
	t_color	color;

	// if (material.type == phong)
	// 	area_light_shade_phong(material, shade_rec, scene, sampelr_manager, render_options, seed);
	// else if (material.type == emissive)

	// else

	return (color);
}

float4	get_reflected_vector(float4 l, float4 n)
{
	float4	r;

	r = -l + 2 * dot(l, n) * n;
	return normalize(r);
}

inline t_material	get_instance_material(t_instance_manager instance_manager, t_instance instance)
{
	return (instance.material);
}

inline t_instance	get_instance(t_instance_manager instance_manager, int id)
{
	return instance_manager.instances[id];
}

inline t_matrix	get_instance_matrix(t_instance_manager instance_manager, t_instance	instance)
{
	return (instance_manager.matrices[instance.matrix_id]);
}

inline t_obj get_object_info(t_instance_manager instance_manager, t_instance instance)
{
	return (instance_manager.objects[instance.object_id]);
}

inline t_triangle get_triangle_info(t_instance_manager instance_manager, t_instance instance)
{
	return (instance_manager.triangles[instance.object_id]);
}

bool	bvh_intersection(t_scene scene, t_ray ray, t_shade_rec *shade_rec)
{
	t_hit_info	last_hit_info;

	last_hit_info.t = K_HUGE_VALUE;

	shade_rec->id = -1;
	int			node_id = 0;
	t_bvh_node	current_node;

	while (node_id != -1)
	{
		current_node = scene.bvh[node_id];

		if (bbox_intersection(ray, current_node.aabb))
		{
			if (current_node.instance_id == -1)
			{
				node_id++;
			}
			else /* leaf node*/
			{
				if (instance_hit(scene.instance_manager,
								ray,
								&shade_rec->hit_info,
								get_instance(scene.instance_manager, current_node.instance_id))
					&& shade_rec->hit_info.t < last_hit_info.t)
				{
					last_hit_info = shade_rec->hit_info;
					shade_rec->id = current_node.instance_id;
				}
				node_id = current_node.next;
			}
		}
		else
		{
			node_id = current_node.next;
		}
	}
	shade_rec->hit_info = last_hit_info;
	return (shade_rec->id > -1);
}

//TODO(dmelessa): shading both sides of surface à¸¢à¸‡14
bool	scene_intersection(t_scene scene, t_ray ray, t_shade_rec *shade_rec)
{
	return (bvh_intersection(scene, ray, shade_rec));

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

t_color	ray_trace(t_ray ray, t_scene scene, t_render_options options, t_sampler_manager sampler_manager, uint2 *seed)
{
	int			local_id = get_local_id(0);
	t_shade_rec	shade_rec;

	/* computed color */
	t_color		color = options.background_color;
	color.r = 0.0f;
	color.b = 0.0f;
	color.g = 0.0f;
	float		color_coef = 1.0f;

	/* material of hit object*/
	t_material	instance_material;

	bool		continue_loop = true;
	uchar		tree_depth = 0;

	while (continue_loop)
	// do
	{
		if (scene_intersection(scene, ray, &shade_rec))
		{
			t_instance	instance = scene.instance_manager.instances[shade_rec.id];
			shade_rec.ray =  transform_ray(ray,
				scene.instance_manager.matrices[instance.matrix_id]);

			/* local_hit_point */
			shade_rec.hit_point = (shade_rec.hit_info.t) * shade_rec.ray.direction + shade_rec.ray.origin;

			/* normal at hit point */
			shade_rec.normal = get_instance_normal(scene.instance_manager, shade_rec);

			/* save ray for specular reflection */
			shade_rec.ray = ray;
			/* world hit point */
			shade_rec.hit_point = (shade_rec.hit_info.t) * shade_rec.ray.direction + shade_rec.ray.origin;

			/* if normal is not directed to us then we reverse normal*/
			shade_rec.normal = dot(shade_rec.normal, ray.direction) < 0.0f ?
				shade_rec.normal : -shade_rec.normal;

			/* NOTE: we can get material in scene_intersection function */
			instance_material = get_instance_material(scene.instance_manager, instance);

			/* accumulate color */
			color = color_sum(color, shade_material(scene, sampler_manager, instance_material, shade_rec, options, seed));
		}
		else /* no hit */
		{
			continue_loop = false;
			color = color_sum(color, options.background_color);
		}
		continue_loop = false;

	};
	return (color);
}

void	init_scene(t_scene *scene,
					__constant t_instance *instances, int ninstances,
					__global t_obj *objects, int nobjects,
					__constant t_triangle *triangles, int ntriangles,
					__global t_matrix *matrices, int nmatrices,
					__constant t_light *lights, int nlights,
					__global t_bvh_node *bvh,
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

				t_render_options options, //16

				__global t_sampler *samplers, //17
				__global float2 *samples, //18
				__global float2 *disk_samples,	//19
				__global float3 *hemisphere_samples) //20
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
	x = global_id % camera.viewplane.width;
	y = global_id / camera.viewplane.width;
	seed.x = global_id;
	seed.y = get_local_id(0) + get_group_id(0);
	seed.y = random(&seed);

	init_scene(&scene,
				instances, ninstances, objects, nobjects,
				triangles, ntriangles, matrices, nmatrices,
				lights, nlights, bvh,
				camera, ambient_light, ambient_occluder);

	init_sampler_manager(&sampler_manager, samplers, samples, disk_samples, hemisphere_samples);

	/* получаем семплер для антиалиасинга и текущий шаг. */
	ao_sampler = get_sampler(sampler_manager, options.sampler_id);
	ao_sampler.count = global_id * ao_sampler.num_samples + step;

	/* Если это не первый шаг, то считаем прыжок для семплеров */
	if (step != 0)
	{
		ao_sampler.jump = (random(&seed) % ao_sampler.num_sets) * ao_sampler.num_samples;
		options.ambient_occluder_sampler.jump = (random(&seed) % options.ambient_occluder_sampler.num_sets) * options.ambient_occluder_sampler.num_samples;
	}
	else
		image[global_id] = (t_color){.r = 0.0f, .g = 0.0f, .b = 0.0f};

	/* */
	float2	sp = sample_unit_square(&ao_sampler, sampler_manager.samples, &seed);
	float	dx = x + sp.x;
	float	dy = y + sp.y;

	if (scene.camera.type == thin_lens)
	{
		camera_sampler = get_sampler(sampler_manager, scene.camera.sampler_id);
		camera_sampler.count = global_id * camera_sampler.num_samples + step;
		if (step != 0)
			camera_sampler.jump = (random(&seed) % camera_sampler.num_sets) * camera_sampler.num_samples;
	}

	if (false && global_id == 0 && step == 0)
	{
		printf("GPU:\nobj %u\n", sizeof(t_obj));
		printf("instance %u\n", sizeof(t_instance));
		printf("matrix %u\n", sizeof(t_matrix));
		printf("material %u\n", sizeof(t_material));
		printf("triangle %u\n", sizeof(t_triangle));
		printf("N: %d\n", nobjects);
		print_all(scene);
	}

	ray = cast_camera_ray(scene.camera, dx, dy, sampler_manager, &camera_sampler, &seed);
	color = ray_trace(ray, scene, options, sampler_manager, &seed);;;;;

	image[global_id] = color_sum(image[global_id], color);
}

typedef union
{
	struct
	{
		char b;
		char g;
		char r;
		char a;
	};
	int	value;
}	int_color;

__kernel void translate_image(__global t_color *rgb_image,
							__global uint *uint_image,
							int num_samples)
{
	t_color			color;
	int				global_id = get_global_id(0);
	uint			value;
	int_color		int_clr;

	color = rgb_image[global_id];
	color.r = color.r / num_samples;
	color.g = color.g / num_samples;
	color.b = color.b / num_samples;

	color.r = clamp(color.r, 0.0f, 1.0f);
	color.g = clamp(color.g, 0.0f, 1.0f);
	color.b = clamp(color.b, 0.0f, 1.0f);

	int_clr.r = color.r * 255.0f;
	int_clr.g = color.g * 255.0f;
	int_clr.b = color.b * 255.0f;
	int_clr.a = 0;

	uint_image[global_id] = int_clr.value;
}

