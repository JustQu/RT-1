float4	get_reflected_vector(float4 l, float4 n)
{
	float4	r;

	r = -l + 2 * dot(l, n) * n;
	return normalize(r);
}

t_material	get_instance_material(t_instance_manager instance_manager, int id)
{
	return (instance_manager.instances[id].material);
}

//TODO(dmelessa): shading both sides of surface ยง14
bool	scene_intersection(t_scene scene, t_ray ray, t_shade_rec *shade_rec)
{
	float		t;
	t_hit_info	last_hit_info;

	last_hit_info.t = K_HUGE_VALUE;

	shade_rec->id = -1;
	for (int i = 0; i < scene.instance_manager.ninstances; i++)
	{
		if (instance_hit(scene.instance_manager, ray, i, &shade_rec->hit_info)
			&& shade_rec->hit_info.t < last_hit_info.t)
		{
			last_hit_info = shade_rec->hit_info;
			shade_rec->id = i;
		}
	}
	shade_rec->hit_info = last_hit_info;
	return (shade_rec->id > -1);
}

//todo: move normal computation to ray_trace_function
t_color	ray_trace(t_ray ray, t_scene scene, t_render_options options, t_sampler_manager sampler_manager, uint2 *seed)
{
	t_shade_rec	shade_rec;
	t_color		color;
	t_material	instance_material;

	color = options.background_color;

	if (scene_intersection(scene, ray, &shade_rec))
	{
		// shade_rec.ray = ray;
		/* save ray for specular reflection */
		shade_rec.ray =  transform_ray(ray,
			scene.instance_manager.matrices[
				scene.instance_manager.instances[shade_rec.id].matrix_id]);

		/* compute hit point */
		shade_rec.hit_point = (shade_rec.hit_info.t) * shade_rec.ray.direction + shade_rec.ray.origin;

		shade_rec.normal = get_instance_normal(scene.instance_manager, shade_rec);

		shade_rec.ray = ray;

		shade_rec.hit_point = (shade_rec.hit_info.t) * shade_rec.ray.direction + shade_rec.ray.origin;

		// ray =  transform_ray(ray,
			// scene.instance_manager.matrices[
				// scene.instance_manager.instances[shade_rec.id].matrix_id]);

		/* if normal is not directed to us then we reverse normal*/
		shade_rec.normal = dot(shade_rec.normal, ray.direction) < 0.0f ?
			shade_rec.normal : -shade_rec.normal;

		/* NOTE: we can get material in scene_intersection function */
		instance_material = get_instance_material(scene.instance_manager, shade_rec.id);

		// shade_rec.ray = ray;
		if (options.area_lightning)
		{
			;;;;;;;;;;;;;;;;;
			//todo: area_lightning
		}
		else
		{
			color = shade_material(scene, sampler_manager, instance_material,
									shade_rec, options, seed);
		}
	}
	return (color);
}
