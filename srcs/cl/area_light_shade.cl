t_color		area_light_shade_phong(t_material material,
									t_shade_rec shade_rec,
									t_scene scene,
									t_sampler_manager sampler_manager,
									t_rt_options options,
									uint2 *seed)
{
	t_color	color = (t_color){ .r = 0.0f, .g = 0.0f, .b = 0.0f };
	t_color	color_tmp;

	/* revert camera ray for specular light */
	shade_rec.ray.direction = -shade_rec.ray.direction;

	// if (options.ambient_occlusion) /* ambient occlusion */
	// {
	// 	color = ambient_occlusion_l(scene, sampler_manager, &options.ambient_occluder_sampler, shade_rec, seed);
	// 	// color = color_multi(color, material.color);
	// }
	// else /* compute constant ambient light using ka coefficent of the materail */
	// {
	// 	// color = lambertian_rho(material.ka, material.color);
	// 	color_tmp = get_light_radiance(scene.ambient_light);
	// 	color = color_multi(color, color_tmp);
	// }

	/* compute sahding for each light source */
	for (int i = 0; i < scene.nlights; i++)
	{
		t_light	light = scene.lights[i];

		bool	in_shadow = false;

		/* compute light direction at hit point */
		float4	wi = get_light_direction2(scene,
										&light,
										shade_rec,
										sampler_manager,
										seed);

		if (options.shadows)
		{
			t_ray	shadow_ray = { .origin = shade_rec.hit_point +
										1e-3f * shade_rec.normal,
									.direction = wi };
			in_shadow = shadow_hit(scene, light, shadow_ray, shade_rec);
		}

		if (!in_shadow)
		{
			/* compute angle between normal at the hit point and light direction */
			float ndotwi = dot(shade_rec.normal, wi);

			/* if angle > 0 then hit point is receivingl light */
			if (ndotwi > 0.0f)
			{
				/* compute glossy_specular coefficient */
				// float k = glossy_specular_f(shade_rec.ray.direction, shade_rec.normal, wi, material.ks, material.exp) ;
				color_tmp = glossy_specular_f(shade_rec.ray.direction,
											shade_rec.normal, wi, ndotwi,
											material.ks, material.exp);


				/* sum lambertian color and glossy specular color */
				color_tmp = color_sum(lambertian_f(material.kd,
												get_color(scene.instance_manager.tex_mngr,
														material, &shade_rec)),
										color_tmp);
				float k = ndotwi
						* light_g(light, wi, shade_rec)
						/ light_pdf(light);
				color_tmp = float_color_multi(k,
											color_multi(light_l(light, wi),
														 color_tmp));
				color = color_sum(color_tmp, color);
			}
		}
	}
	return (color);
}

t_color		area_light_shade_matte(t_material material,
								t_shade_rec shade_rec,
								t_scene scene,
								t_sampler_manager sampler_manager,
								t_rt_options options,
								uint2 *seed)
{
	float4	wo = -shade_rec.ray.direction;

	t_color	color;
	t_color	color_tmp;

	//TODO: ambient_light
	color = (t_color){ .r = 0.0f, .g = 0.0f, .b = 0.0f };

	for (int i = 0; i < scene.nlights; i++)
	{
		t_light	light = scene.lights[i];

		bool	in_shadow = false;

		float4	light_direction = get_light_direction2(scene,
													&light,
													shade_rec,
													sampler_manager,
													seed);

		if (options.shadows)
		{
			t_ray	shadow_ray = { .origin = shade_rec.hit_point +
											1e-2f * shade_rec.normal,
									.direction = light_direction };
			in_shadow = shadow_hit(scene,
								light,
								shadow_ray,
								shade_rec);
		}


		if (!in_shadow)
		{
			float	ndotwi = dot(shade_rec.normal, light_direction);

			if (ndotwi > 0.0f)
			{
				color_tmp = lambertian_f(material.kd,
									get_color(scene.instance_manager.tex_mngr,
											material, &shade_rec));

				float k = ndotwi
						* light_g(light, light_direction, shade_rec)
						/ light_pdf(light);
				color_tmp = float_color_multi(k,
								color_multi(light_l(light, light_direction),
											color_tmp));
				color = color_sum(color, color_tmp);
			}
		}
	}
	return (color);
}

t_color		area_light_shade_emissive(t_scene scene,
									t_material material,
									t_shade_rec shade_rec)
{
	if (dot(-shade_rec.normal, shade_rec.ray.direction) > 0.0f)
	{
		return (float_color_multi(material.ls,
								get_color(scene.instance_manager.tex_mngr,
										material, &shade_rec)));
	}
	else
		return ((t_color){ .r = 0.0f, .g = 0.0f, .b = 0.0f });
}

t_color		area_light_shade(t_scene scene,
							t_sampler_manager sampler_manager,
							t_material material,
							t_shade_rec shade_rec,
							t_rt_options options,
							uint2 *seed)
{
	t_color	color;

	if (material.type == phong)
	{
		color = area_light_shade_phong(material,
									shade_rec,
									scene,
									sampler_manager,
									options,
									seed);
	}
	else if (material.type == emissive)
	{
		color = area_light_shade_emissive(scene, material, shade_rec);
	}
	else
	{
		color = area_light_shade_matte(material,
									shade_rec,
									scene,
									sampler_manager,
									options,
									seed);
	}

	return (color);
}
