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

	t_bbox bbox = box.bounding_box;

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
	hit_info->t = t * 0.99f;
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
