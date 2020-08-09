float4	get_sphere_normal(float4 point, t_obj sphere)
{
	return (normalize(point - sphere.origin));
}

float4	get_plane_normal(t_obj plane, t_hit_info hit_info)
{
	// return (float4)(0.0f, 1.0f, 0.0f, 0.0f);
	if (hit_info.dv < 0.0f)
		return (plane.direction);
	else
		return -(plane.direction);
}

float4	get_cylinder_normal(float4 point, t_obj cylinder, t_hit_info hit_info)
{
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
	float	k;
	float	m;
	float4	A;

	point = 1.0001f * point;
	k = dot(point - torus.origin, torus.direction);
	A = point - k * torus.direction;
	m = sqrt(torus.r2 * torus.r2 - k * k);
	return normalize(point - A - (torus.origin - A) * (m / (torus.r + m)));
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
	return (float4)(matrix.s0 * normal.x + matrix.s4 * normal.y + matrix.s8 * normal.z,
					   matrix.s1 * normal.x + matrix.s5 * normal.y + matrix.s9 * normal.z,
					   matrix.s2 * normal.x + matrix.s6 * normal.y + matrix.sA * normal.z,
					   0.0f);
}

float4	get_instance_normal(t_instance_manager instance_manager, t_shade_rec shade_rec)
{
	t_instance	instance;
	float4		normal;
	t_matrix	matrix;

	instance = instance_manager.instances[shade_rec.id];
	if (instance.type == triangle)
		normal = get_triangle_normal(
					instance_manager.triangles[instance.object_id]);
	else
		normal = get_object_normal(shade_rec.hit_point,
			instance_manager.objects[instance.object_id],
			shade_rec.hit_info,
			instance_manager.instances[shade_rec.id].type);
	matrix = instance_manager.matrices[instance_manager.instances[shade_rec.id].matrix_id];
	normal = transform_normal(normal, matrix);
	// printf("Normal %f %f %f %f", normal.x, normal.y, normal.z, normal.w);

	return normalize(normal);
}
