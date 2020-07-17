#define WIDTH 1200
#define HEIGHT 800

#include "rt.h"


vool	sphere_intersection(t_obj sphere, t_ray ray)
{
	float4	L = sphere.origin - ray.origin;
	float	tca = dot(L, ray.direction);
	if (tca < 0.0f)
		return false;

	float	d2 = dot(L, L) - tca * tca;
	if (d2 > sphere.r2) //r^2 should be precomputed
		return false;

	float	thc = sqrt(sphere.r2 - d2);
	float	t = tca - thc;
	if (t < 0.0f)
	{
		t = tca + thc;
		if (t < 0.0f)
			return false;
	}
	return true;
}

void	cast_camera_ray(t_ray *ray, int x, int y)
{
	ray->origin = (float4)(x, y, 0.0f, 0.0f);
	ray->direction = (float4)(0.0f, 0.0f, 1.0f, 0.0f);
}

int	get_pixel_color(int x, int y, __constant t_obj *objects, int nobjects)
{
	float	t = 10000.0f;
	float	t1;
	t_ray	ray;

	ray = cast_camera_ray(&ray, x, y);
	if (sphere_intersection(objects[0], ray))
	{
		return 0x00ff0000; //красный
	}
	return 0x0000ff00; //зеленый
}

__kernel	void	main(__global uint *image,
						__constant t_obj *objects, int nobjects)
{
	int		global_id;
	int		x;
	int		y;

	global_id = get_global_id(0);
	x = global_id % WIDTH;
	y = global_id / WIDTH;
	// image[global_id] = 0x00ffffff * x ;
	image[global_id] = (x / 255) << 16 | (y % 255) << 8;
}
