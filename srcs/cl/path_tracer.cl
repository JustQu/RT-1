
/*
** SUffern path tracer
*/
t_color	path_tracer1(t_ray ray, t_scene scene, t_rt_options options,
					t_sampler_manager sampler_manager, uint2 *seed)
{


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
bool	metal_scatter(t_material material,
					t_shade_rec *shade_rec,
					t_color *attenuation,
					float4 *state)
{
	shade_rec->normal = dot(shade_rec->normal, shade_rec->ray.direction) < 0.0f ?
							shade_rec->normal : -shade_rec->normal;
	float4 reflected = get_reflected_vector(shade_rec->ray.direction, shade_rec->normal);

	shade_rec->ray.origin = shade_rec->hit_point + 1e-2f * shade_rec->normal;
	shade_rec->ray.direction = reflected
							+ 0.2f * cosine_sampler_hemisphere(state);

	*attenuation = float_color_multi(material.kr, material.color);
	return (dot(reflected, shade_rec->normal) > 0);
}

bool	lambertian_scater(t_material material,
						t_shade_rec *shade_rec,
						t_color *attenuation,
						float4 *state)
{
	float4 target = shade_rec->hit_point
					+ shade_rec->normal
					+ cosine_sampler_hemisphere(state);

	shade_rec->ray.origin = shade_rec->hit_point + 1e-2f * shade_rec->normal;
	shade_rec->ray.direction = target - shade_rec->hit_point;

	*attenuation = float_color_multi(material.kd, material.color);
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

bool	dielectric_scatter(t_material material,
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

bool	scatter(t_material material,
				t_shade_rec *shade_rec,
				t_color *attenuation,
				float4 *state)
{

	if (material.type == matte)
	{
		return (lambertian_scater(material, shade_rec, attenuation, state));
	}
	else if (material.type == metal)
	{
		return (metal_scatter(material, shade_rec, attenuation, state));
	}
	else if (material.type == dielectric)
	{
		return (dielectric_scatter(material, shade_rec, attenuation, state));
	}
	else return false;
}

t_color	path_tracer2(t_ray ray, t_scene scene, t_rt_options options,
					t_sampler_manager sampler_manager, uint2 *seed,
					float4	*state)
{
	t_color	color;
	color.r = 0.0f;
	color.g = 0.0f;
	color.b = 0.0f;
	// float	cur_attenuation = 1.0f;

	t_color	cur_attenuation;
	cur_attenuation.r = 1.0f;
	cur_attenuation.g = 1.0f;
	cur_attenuation.b = 1.0f;

	bool continue_loop = 1;

	int	depth = 0;
do	{
		t_shade_rec	shade_rec;
		depth++;
		if (scene_intersection(scene, ray, &shade_rec) && depth < 50)
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

			// /* if normal is not directed to us then we reverse normal*/
			// shade_rec.normal = dot(shade_rec.normal, ray.direction) < 0.0f ?
			// 	shade_rec.normal : -shade_rec.normal;

			// shade_rec.hit_point += + 1e-3f * shade_rec.normal;

			t_material material = get_instance_material(scene.instance_manager,
													instance);

			t_color	attenuation;
			if (scatter(material, &shade_rec, &attenuation, state))
			{
				cur_attenuation = color_multi(cur_attenuation, attenuation);
				ray = shade_rec.ray;
			}
			else
			{
				continue_loop = false;
			}
		}
		else
		{
			continue_loop = false;
			float4 unit_vec = normalize(ray.direction);
			float t = 0.5f * (unit_vec.y + 1.0f);
			float3 c = (1.0f - t) * (float3)(1.0f, 1.0f, 1.0f) + t * (float3)(0.5f, 0.7f, 1.0f);

			color.r = cur_attenuation.r * c.x;
			color.g = cur_attenuation.g * c.y;
			color.b = cur_attenuation.b * c.z;
		}
	}
	while (continue_loop);
	return (color);
}
