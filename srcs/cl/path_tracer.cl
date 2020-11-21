
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

float4	cosine_sample_hemisphere(float4 *state)
{
	float e1 = GPURnd(state);
	float e2 = GPURnd(state);
	float theta = sqrt(e1);
	float phi = 2 * M_PI * e2;

	return (float4)(cos(phi) * theta, sin(phi) * theta, sqrt(1 - e1), 0.0f);
}

float4	random_cosine_direction(float4 *state)
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
							+ 0.3f * random_in_unit_sphere(state);

	*attenuation = float_color_multi(
						material.kr,
						get_color(texture_manager, material, shade_rec));
	// *attenuation = float_color_multi(material.kr, material.color);
	return (dot(reflected, shade_rec->normal) > 0.0f);
}

void	build_from_w(float4 *const u, float4 *const v, float4 *const w,
					float4 const n)
{
	float4 a;

	*w = n;
	if (fabs(w->x) > 0.9f)
		a = (float4)(0.0f, 1.0f, 0.0f, 0.0f);
	else
		a = (float4)(1.0f, 0.0f, 0.0f, 0.0f);
	*v = normalize(cross(*w, a));
	*u = cross(*w, *v);
}

/* return normalized direcrtion in u,v,w coordinate system */
float4	local_dir(float4 const *const u,
				float4 const *const v,
				float4 const *const w,
				float4 const a)
{
	return normalize(a.x * *u + a.y * *v + a.z * *w);
}

bool	lambertian_scater(t_texture_manager texture_manager,
						t_material material,
						t_shade_rec *shade_rec,
						t_color *attenuation,
						float *pdf,
						float4 *state,
						t_sampler_manager sampler_manager,
						t_sampler *sampler, uint2 *seed)
{

	// float4 target = shade_rec->hit_point
					// + shade_rec->normal
					// + random_in_unit_sphere(state);
//
	shade_rec->ray.origin = shade_rec->hit_point + 1e-2f * shade_rec->normal;
	// shade_rec->ray.direction = normalize(target - shade_rec->hit_point);
//
	// *attenuation = get_color(texture_manager, material, shade_rec);
	// *pdf = 0.5f / M_PI;

	float4 u, v, w; // onb

	build_from_w(&u, &v, &w, shade_rec->normal);
	float4 direction = local_dir(&u, &v, &w, cosine_sample_hemisphere(state));

	shade_rec->ray.direction = normalize(direction);

	// w = shade_rec->normal;
	// v = normalize(cross(w, (float4)(0.0072f, 1.0f, 0.0034f, 0.0f)));
	// u = cross(v, w);

	// float3 sp = sample_hemisphere(sampler, sampler_manager.hemisphere_samples, seed);
	// shade_rec->direction = normalize(sp.x * u + sp.y * v + sp.z * w);
	// shadow_ray.origin = shade_rec.hit_point + 1e-2f * shade_rec.normal;

	// shade_rec->ray.origin = (float4)(0.0f, 0.0f, 0.0f, 0.0f);
	// shade_rec->ray.direction = normalize(direction);

	*attenuation = get_color(texture_manager, material, shade_rec);
	// *pdf = 0.5f / M_PI_F;
	*pdf = dot(w, normalize(direction)) / M_PI;


	// *attenuation = float_color_multi(material.kd, material.color);
	return (true);
}

bool	dielectric_scatter1(t_material material,
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

bool	scatter(t_texture_manager texture_manager,
				t_material material,
				t_shade_rec *shade_rec,
				t_color *attenuation,
				float *pdf,
				float4 *state,
				t_sampler_manager sampler_manager,
						t_sampler *sampler, uint2 *seed)
{
	if (material.type == matte)
	{
		return (lambertian_scater(texture_manager,
								material,
								shade_rec,
								attenuation,
								pdf,
								state,
								sampler_manager,
								sampler, seed));
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
	if (material.type == diffuse_light || material.type == emissive)
		return ((t_color){ .r = 1.0f, .g = 1.0f, .b = 1.0f });
	return ((t_color){ .r = 0.0f, .g = 0.0, .b = 0.0f });
}

float	lambertian_pdf(t_shade_rec const *const shade_rec,
						t_ray const scattered_ray)
{
	float	cosine;

	cosine = dot(shade_rec->normal, scattered_ray.direction);

	if (cosine < 0.0f)
	{
		cosine = 0.0f;
	}
	return (cosine / M_PI);
}

float	metal_pdf(t_shade_rec const *const shade_rec,
				t_ray const scattered_ray)
{
	return (dot(scattered_ray.direction, shade_rec->normal));
}

float	scattering_pdf(t_material const material,
					t_shade_rec *const shade_rec,
					t_ray const scattered_ray)
{
	if (material.type == matte)
	{
		return (lambertian_pdf(shade_rec, scattered_ray));
	}
	else if (material.type == metal)
	{
		return (metal_pdf(shade_rec, scattered_ray));
	}
	return 0.0f;
}

inline bool	lambertian_scater2(t_texture_manager  texture_manager,
						t_material  material,
						t_shade_rec * shade_rec,
						t_color * attenuation,
						float * pdf,
						float4 * state)
{
	float4 u, v, w; // onb

	build_from_w(&u, &v, &w, shade_rec->normal);
	float4 direction = local_dir(&u, &v, &w, random_cosine_direction(state));

	shade_rec->ray.origin = shade_rec->hit_point + shade_rec->normal * 1e-2f;
	shade_rec->ray.direction = normalize(direction);

	*attenuation = get_color(texture_manager, material, shade_rec);
	// *pdf = 0.5f / M_PI_F;
	*pdf = dot(w, normalize(direction)) / M_PI;

	return (true);
}

bool	metal_scatter2(t_texture_manager texture_manager,
					t_material material,
					t_shade_rec *shade_rec,
					t_color *attenuation,
					float *pdf,
					float4 *state)
{
	shade_rec->normal = dot(shade_rec->normal, shade_rec->ray.direction) < 0.0f ?
							shade_rec->normal : -shade_rec->normal;
	float4 reflected = get_reflected_vector(shade_rec->ray.direction, shade_rec->normal);

	shade_rec->ray.origin = shade_rec->hit_point + 1e-2f * shade_rec->normal;
	shade_rec->ray.direction = reflected
							+ 0.0f * random_cosine_direction(state);

	*attenuation = float_color_multi(
						material.kr,
						get_color(texture_manager, material, shade_rec));
	*pdf = dot(reflected, shade_rec->normal);
	// *attenuation = float_color_multi(material.kr, material.color);
	return (dot(reflected, shade_rec->normal) > 0.0f);
}

bool	scatter2(t_texture_manager texture_manager,
				t_material material,
				t_shade_rec *shade_rec,
				t_color *attenuation,
				float *pdf,
				float4 *state)
{
	if (material.type == matte)
	{
		return (lambertian_scater2(texture_manager, material, shade_rec,
									attenuation, pdf, state));
	}
	else if (material.type == dielectric)
	{
		// return (dielectric_scatter2(texture_manager, material, shade_rec,
									// attenuatuin, pdf, state));
	}
	else if (material.type == metal)
	{
		return (metal_scatter2(texture_manager, material, shade_rec,
								attenuation, pdf, state));
	}
	return false;
}

t_color	global_shade(t_ray ray, t_scene scene, t_rt_options options,
					t_sampler_manager sampler_manager,
					uint2 *seed, float4 *state)
{
	/* NOTE: color accamulator */
	t_color	color = (t_color){ .r = 0.0f, .g = 0.0f, .b = 0.0f};

	/* NOTE: current color coefficient */
	t_color	beta = (t_color) { .r = 1.0f, .g = 1.0f, .b = 1.0f };

	bool	continue_loop = true;
	int		depth = 0;

	t_shade_rec	shade_rec;
	shade_rec.ray = ray;

	bool	specular_bounce = false;

	do
	{
		//TODO: RUSSIAN ROULETTE?

		if (scene_intersection(scene, ray, &shade_rec) &&
			depth < 10 /* options.depth */)
		{
			t_instance	instance = get_instance(scene.instance_manager,
												shade_rec.id);

			t_material	material = get_instance_material(scene.instance_manager,
														instance);

			if (depth == 0 || specular_bounce)
			{
				color = color_sum(color,
								color_multi(beta,
											area_light_shade(scene, sampler_manager,
															material, shade_rec,
															options, seed)));
				// return (color);
			}

			t_color	f;
			float	pdf;
			if (scatter2(scene.instance_manager.tex_mngr, material, &shade_rec,
						&f, &pdf, state
						/* , sampler_manager, &options.ambient_occluder_sampler, seed */))
			{
				beta = color_multi(beta,
							float_color_multi(scattering_pdf(material,
															&shade_rec,
															shade_rec.ray) / pdf,
											f));
			}
			else
			{
				// if (depth != 1)
				color = color_sum(color,
								color_multi(emitted(material, &shade_rec,
													0, 0, shade_rec.hit_point),
										beta));
				continue_loop = false;
			}

			specular_bounce = material.type == metal;
		}
		else
		{
			continue_loop = false;
		}
		depth++;
	} while (continue_loop);

	return (color);
}

t_color	path_tracer2(t_ray ray, t_scene scene, t_rt_options options,
					t_sampler_manager sampler_manager, uint2 *seed,
					float4	*state,
					t_sampler *sampler)
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
		if (scene_intersection(scene, ray, &shade_rec) && depth < 10
		&& cur_attenuation.r + cur_attenuation.g + cur_attenuation.b > 0.0f)
		{
			t_instance	instance = scene.instance_manager.instances[shade_rec.id];

			t_material material = get_instance_material(scene.instance_manager,
														instance);

			t_color	attenuation;
			t_color	emit = color_multi(cur_attenuation,
									emitted(material, &shade_rec,
											0, 0, shade_rec.hit_point));
			float	pdf = 0.5f / M_PI;
			if (scatter(scene.instance_manager.tex_mngr,
						material,
						&shade_rec,
						&attenuation,
						&pdf,
						state, sampler_manager, sampler, seed))
			{
				cur_attenuation = color_multi(
									float_color_multi(
										scattering_pdf(material,
													&shade_rec,
													shade_rec.ray) / pdf,
										attenuation),
									cur_attenuation);
				// cur_attenuation = color_multi(cur_attenuation, attenuation);
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
		if (scene_intersection(scene, ray, &shade_rec) && depth < 10 && cur_attenuation.r + cur_attenuation.g + cur_attenuation.b > 0.05f)
		{
			t_instance	instance = scene.instance_manager.instances[shade_rec.id];

			t_material material = get_instance_material(scene.instance_manager,
													instance);

			t_color	attenuation;
			float	pdf = 0.5f / M_PI;
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
