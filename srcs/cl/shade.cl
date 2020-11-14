bool		shadow_hit(t_scene scene, t_light light, t_ray shadow_ray, t_shade_rec shade_rec)
{
	float	t;
	float	tmin = distance(light.origin, shadow_ray.origin);
	// float	tmin = dot(light.origin - shadow_ray.origin, shadow_ray.direction);
	// printf("%f %f %f - %f %f %f = %f   ", light.origin.x, light.origin.y, light.origin.z, shadow_ray.origin.x, shadow_ray.origin.y, shadow_ray.origin.z, tmin);
	// if (light.type == directional)
	// 	tmin = 0;
	int			node_id = 0;
	t_bvh_node	current_node;

	t_shade_rec	sr;
	sr.id = shade_rec.id;
	sr.ray = shadow_ray;
	sr.ray.direction = normalize(sr.ray.direction);

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
					//NOTE: for area lights, don't intersect if it is the object emitting the light
					if (light.object_id != current_node.instance_id && tmin > 0.001)
						return (true);
					tmin = distance(light.origin, shadow_ray.origin);
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
		color = ambient_occlusion_l(scene, sampler_manager, sampler_manager.sampler, shade_rec, seed);
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
			color_tmp = glossy_specular_f(shade_rec.ray.direction, shade_rec.normal, light_direction, dirdotn, material.ks, material.exp) ;

				/* compute diffuse color */
				// color_tmp = lambertian_f(material.kd, material.color);

				/* sum lambertian color and glossy specular color */
				color_tmp = color_sum(color_tmp, color_multi(color_tmp, scene.lights[i].color));

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
		color = ambient_occlusion_l(scene, sampler_manager, sampler_manager.sampler, shade_rec, seed);
		color = color_multi(color, get_color(scene.instance_manager.tex_mngr,
											material, &shade_rec));
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
		t_ray	shadow_ray = { .origin = shade_rec.hit_point + 1e-2f * shade_rec.normal,
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
