#define _get_instance() get_instance(scene.instance_manager, shade_rec.id)
#define _get_instance_material() get_instance_material(scene.instance_manager,\
														instance)
#define _get_enviroment_light() (t_color){ 0.0f, 0.0f, 0.0f, 0.0f }
#define is_black(color) (color.r <= 0.01f && color.g <= 0.1f && color.b <= 0.1f)

t_color	matte_sample_light(t_material material,
							t_shade_rec shade_rec,
							t_scene scene,
							t_sampler_manager sampler_manager,
							t_rt_options options,
							uint2 *seed)
{
	t_light	light;


	/* get random light
	** Note: not the best approach. Lights with bigger intensivity weights more
	*/
	light = scene.lights[random(seed) % scene.nlights];

	bool	in_shadow = false;

	float4	wi = get_light_direction2(scene, &light, shade_rec,
										sampler_manager, seed);
	if (options.shadows)
	{
		t_ray	shadow_ray = { .origin = shade_rec.hit_point
										+ 1e-4f * shade_rec.normal,
								.direction = wi };
		in_shadow = shadow_hit(scene, light, shadow_ray, shade_rec);
	}

	if (!in_shadow)
	{
		float	ndotwi = dot(shade_rec.normal, wi);

		if (ndotwi > 0.0f)
		{
			t_color	c = lambertian_f(material.kd,
									get_color(scene.instance_manager.tex_mngr,
									material, &shade_rec));

			return (color_multi(c,
							float_color_multi(ndotwi
												* light_g(light, wi, shade_rec)
												/ light_pdf(light),
											light_l(light, wi))));
		}
	}
	return ((t_color) { .r = 0.0f, .g = 0.0f, .b = 0.0f });
}


/* shade surface */
t_color	sample_light(t_material material, t_shade_rec shade_rec, t_scene scene,
					t_sampler_manager sampler_manager, t_rt_options options,
					uint2 *seed)
{
	if (material.type == matte)
	{
		return (matte_sample_light(material, shade_rec, scene, sampler_manager,
									options, seed));
	}
	else if (material.type == mirror)
	{
		/* don't shade if it is a mirror material */
		return ((t_color) { 0.0f, 0.0f, 0.0f, 0.0f });
	}
	else if (material.type == conductor)
	{
		return ((t_color) { 0.0f, 0.0f, 0.0f, 0.0f });
	}
	else if (material.type == emissive)
	{
		return ((t_color){ 1.0f, 1.0f, 1.0f, 0.0f });
	}
	return ((t_color){0.0f, 0.0f, 0.0f, 0.0f});
}

/* scatter */
t_color	matte_sample_material(t_material material, t_shade_rec *shade_rec,
							t_color *f, float *pdf, float *weight,
							t_texture_manager texture_manager,
							float4 *state)
{
	float4 u, v, w;

	build_from_w(&u, &v, &w, shade_rec->normal);
	float4 direction = local_dir(&u, &v, &w, random_cosine_direction(state));

	shade_rec->ray.origin = shade_rec->hit_point + shade_rec->normal * 1e-2f;
	shade_rec->ray.direction = direction;

	float ndotwi = dot(w, direction);
	*pdf = ndotwi * M_1_PI_F;

	/* todo: multiply by diffuse coefficient */
	*f = float_color_multi(*pdf,
						get_color(texture_manager, material, shade_rec));
	*weight = 1.0f;
	return (*f);
}

t_color	mirror_sample_material(t_material material, t_shade_rec *shade_rec,
							t_color *f, float *pdf, float *weight,
							t_texture_manager texture_manager, float4 *state)
{
	if (dot(shade_rec->normal, shade_rec->ray.direction) > 0.0f)
		shade_rec->normal = -shade_rec->normal;

	shade_rec->ray.origin = shade_rec->hit_point + 1e-1f * shade_rec->normal;

	shade_rec->ray.direction = get_reflected_vector(shade_rec->ray.direction,
													shade_rec->normal);

	*f = (t_color){ .r = 1.0f, .g = 1.0f, .b = 1.0f };
	*pdf = 1.0f;
	*weight = 1.0f;
	// *f = get_color(texture_manager, material, shade_rec);
}

float	fresnel_conductor(float cos_theta)
{
	return (1.0f);
}

float	ggx_visibility(float roughness_sq, float cos_theta)
{
	float cos_theta_squared = cos_theta * cos_theta;
	float tan_theta_squared = (1.0f - cos_theta_squared) / cos_theta_squared;
	return (2.0f / (1.0f + sqrt(1.0f + roughness_sq * tan_theta_squared)));
}
float	ggx_visibility_term(float roughness_sq, float t0, float t1)
{
	return (ggx_visibility(roughness_sq, t0) * ggx_visibility(roughness_sq, t1));
}

float	ggx_normal_distribution(float roughness_sq, float cos_theta)
{
	float denom = (roughness_sq - 1.0f) * cos_theta * cos_theta + 1.0f;
	return (roughness_sq / (M_PI * denom * denom));
}

//wo from ray
//wi incident direction
t_color	conductor_sample_material(t_material material, t_shade_rec *shade_rec,
								t_color *f, float *pdf, float *weight,
								t_texture_manager texture_manager, float4 *state)
{
	if (dot(shade_rec->normal, shade_rec->ray.direction) > 0.0f)
		shade_rec->normal = -shade_rec->normal;

	shade_rec->ray.origin = shade_rec->hit_point + 1e-2f * shade_rec->normal;
	float4 wo = -shade_rec->ray.direction;

	{ /* sample ggx distribution */
		float4 reflected = get_reflected_vector(shade_rec->ray.direction,
												shade_rec->normal);
		float e1 = GPURnd(state);
		float e2 = GPURnd(state);
		float cos_theta = sqrt((1.0f - e1)
						/ (e1 * (material.exp * material.exp - 1.0f) + 1.0f));
		float phi = e2 * M_PI_F * 2.0f;
		float sin_theta = sqrt(1.0f - cos_theta * cos_theta);
		float4 u, v, w;
		build_from_w(&u, &v, &w, reflected);
		shade_rec->ray.direction = (float4)((u * cos(phi) +
											v * sin(phi)) * sin_theta +
											w * cos_theta);
	}

	float4 h = normalize(wo + shade_rec->ray.direction);

	float ndotwo = dot(shade_rec->normal, wo);
	float ndotwi = dot(shade_rec->normal, shade_rec->ray.direction);
	float hdotwi = dot(h, shade_rec->ray.direction);
	float ndoth = dot(shade_rec->normal, h);
	{
		float fr = fresnel_conductor(hdotwi);
		float d = ggx_normal_distribution(material.exp * material.exp, ndoth);
		float g = ggx_visibility_term(material.exp * material.exp, ndotwi,
													ndotwo);

		*f = float_color_multi(fr * d * g / (4.0f * ndotwo),
								get_color(texture_manager, material, shade_rec));
		*pdf = d * ndoth / (4.0f * hdotwi);
	}
}

/* sample f*/
t_color	sample_material(t_material material, t_shade_rec *shade_rec,
						t_color *f, float *pdf, float *weight,
						t_texture_manager texture_manager,
						uint2 *seed, float4 *state)
{
	if (material.type == matte)
	{
		return (matte_sample_material(material, shade_rec, f, pdf, weight,
									texture_manager, state));
	}
	else if (material.type == mirror)
	{
		return (mirror_sample_material(material, shade_rec, f, pdf, weight,
										texture_manager, state));
	}
	else if (material.type == conductor)
	{
		return (conductor_sample_material(material, shade_rec, f, pdf, weight,
										texture_manager, state));
	}
	else if(material.type == emissive)
	{
		*pdf = 0.0f;
	}
	return ((t_color){ 0.0f, 0.0f, 0.0f, 0.0f });
}


/* integrator */
t_color	trace(t_ray ray, t_scene scene, t_rt_options options,
			t_sampler_manager sampler_manager,
			uint2 *seed, float4 *state)
{
	t_color	color = (t_color){ .r = 0.0f, .g = 0.0f, .b = 0.0f };

	t_color	beta = (t_color){ .r = 1.0f, .g = 1.0f, .b = 1.0f };

	t_shade_rec	shade_rec;
	shade_rec.ray = ray;

	float	material_pdf = 1.0f;
	float	light_pdf = 1.0f;

	char	depth = 0;

	bool	specular_hit = false;

	while (depth < 5)
	{
		if (scene_intersection(scene, ray, &shade_rec))
		{
			if (specular_hit)
			{
				//todo
			}

			t_instance instance = _get_instance();
			t_material material = _get_instance_material();

			color = color_sum(color,
							color_multi(beta,
										sample_light(material, shade_rec, scene,
											sampler_manager, options, seed)));

			if (material_pdf == 0.0f)
				break;

			t_color	f;
			float	pdf;
			float	weight;
			float	bsdf;

			/* scatter */
			sample_material(material, &shade_rec, &f, &pdf, &weight,
								scene.instance_manager.tex_mngr, seed, state);

			if (is_black(f) || pdf <= 0.001f)
				break;

			/* beta = beta * f * dot(n, wi) * invPI / pdf */
			// beta = color_multi(beta,
			beta = color_multi(float_color_multi(1.0f / pdf, f), beta);
		}
		else
		{
			color = color_sum(color, color_multi(beta, _get_enviroment_light()));
			break;
		}
		depth++;
	}

	return (color);
}
