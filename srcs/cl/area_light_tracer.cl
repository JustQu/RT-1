t_color	area_light_tracer(t_ray ray, t_scene scene, t_rt_options options,
						t_sampler_manager sampler_manager, uint2 *seed)
{
	t_shade_rec	shade_rec;

	t_color	color;
	color = (t_color){ .r = 0.0f, .g = 0.0f, .b = 0.0f };

	t_color	clr_coef;
	clr_coef = (t_color){ .r = 1.0f, .g = 1.0f, .b = 1.0f };

	bool	continue_loop = true;

	uchar	depth = 0;

	shade_rec.ray = ray;
	while (continue_loop)
	{
		depth++;

		if (scene_intersection(scene, ray, &shade_rec))
		{
			if (dot(shade_rec.normal, ray.direction) > 0.0f)
			{
				shade_rec.normal = -shade_rec.normal;
			}

			t_instance instance = get_instance(scene.instance_manager,
											shade_rec.id);
			t_material material = get_instance_material(
									scene.instance_manager,
									instance);

			color = color_sum(color,
							color_multi(clr_coef,
									area_light_shade(scene,
													sampler_manager,
													material,
													shade_rec,
													options,
													seed)));
		}
		continue_loop = false;
	}
	return (color);
}
