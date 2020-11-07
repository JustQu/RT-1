#define _get_instance() get_instance(scene.instance_manager, shade_rec.id)
#define _get_instance_material() get_instance_material(scene.instance_manager,\
														instance)
#define _get_enviroment_light() (t_color){ 0.0f, 0.0f, 0.0f, 0.0f }

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
			t_color	c = lambertian_f(material.kd, get_color(scene.instance_manager.tex_mngr, material, &shade_rec));

			return (color_multi(c,
							float_color_multi(ndotwi * light_g(light, wi, shade_rec)
													/ light_pdf(light),
											light_l(light, wi))));
		}
	}
	return ((t_color) { .r = 0.0f, .g = 0.0f, .b = 0.0f });
}

// t_

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
	else if (material.type == emissive)
	{
		return ((t_color){ 1.0f, 1.0f, 1.0f, 0.0f });
	}
	return ((t_color){0.0f, 0.0f, 0.0f, 0.0f});
}

t_color	matte_sample_material(t_material material, t_shade_rec,

/* sample f*/
t_color	sample_material(t_material material, t_shade_rec shade_rec, t_scene scene,
						t_sampler_manager sampler_manager, t_rt_options opotions,
						float *pdf, float *weight, float *
						uint2 *seed)
{
	if (material.type == matte)
	{
	}
	else if(material.type == emissive)
	{
	}

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
												sampler_manager,  options, seed)));

			// color += color_multi(f, beta);

			/* generate next bounce */
			// sample_material();

			if (material_pdf == 0.0f)
				break;

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
				break;
			}
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
