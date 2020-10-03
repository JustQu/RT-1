float4	get_reflected_vector(float4 l, float4 n)
{
	float4	r;

	r = l - 2 * dot(l, n) * n;
	return normalize(r);
}

inline t_material	get_instance_material(t_instance_manager instance_manager, t_instance instance)
{
	return (instance.material);
}

inline t_instance	get_instance(t_instance_manager instance_manager, int id)
{
	return instance_manager.instances[id];
}

inline t_matrix	get_instance_matrix(t_instance_manager instance_manager, t_instance	instance)
{
	return (instance_manager.matrices[instance.matrix_id]);
}

inline t_obj get_object_info(t_instance_manager instance_manager, t_instance instance)
{
	return (instance_manager.objects[instance.object_id]);
}

inline t_triangle get_triangle_info(t_instance_manager instance_manager, t_instance instance)
{
	return (instance_manager.triangles[instance.object_id]);
}

bool	bvh_intersection(t_scene scene, t_ray ray, t_shade_rec *shade_rec)
{
	t_hit_info	last_hit_info;

	last_hit_info.t = K_HUGE_VALUE;

	shade_rec->id = -1;
	int			node_id = 0;
	t_bvh_node	current_node;

	while (node_id != -1)
	{
		current_node = scene.bvh[node_id];

		if (bbox_intersection(ray, current_node.aabb))
		{
			// return true;
			if (current_node.instance_id == -1)
			{
				node_id++;
			}
			else /* leaf node*/
			{
				if (instance_hit(scene.instance_manager,
								ray,
								&shade_rec->hit_info,
								get_instance(scene.instance_manager, current_node.instance_id))
					&& shade_rec->hit_info.t < last_hit_info.t)
				{
					last_hit_info = shade_rec->hit_info;
					shade_rec->id = current_node.instance_id;
				}
				node_id = current_node.next;
			}
		}
		else
		{
			node_id = current_node.next;
		}
	}
	shade_rec->hit_info = last_hit_info;
	return (shade_rec->id > -1);
}

//TODO(dmelessa): shading both sides of surface à¸¢à¸‡14
bool	scene_intersection(t_scene scene, t_ray ray, t_shade_rec *shade_rec)
{
	return (bvh_intersection(scene, ray, shade_rec));

	/* old code for bruteforcing*/
	t_hit_info	last_hit_info;

	last_hit_info.t = K_HUGE_VALUE;

	shade_rec->id = -1;
	for (int i = 0; i < scene.instance_manager.ninstances; i++)
	{
		t_instance instance = get_instance(scene.instance_manager, i);
		if (instance_hit(scene.instance_manager, ray, &shade_rec->hit_info, instance)
			&& shade_rec->hit_info.t < last_hit_info.t)
		{
			last_hit_info = shade_rec->hit_info;
			shade_rec->id = i;
		}
	}
	shade_rec->hit_info = last_hit_info;
	return (shade_rec->id > -1);
}

#define maximum_tree_depth 16

t_color	ray_trace(t_ray ray, t_scene scene, t_rt_options options, t_sampler_manager sampler_manager, uint2 *seed)
{
	int			local_id = get_local_id(0);
	t_shade_rec	shade_rec;

	/* computed color */
	t_color		color = options.background_color;
	color.r = 0.0f;
	color.g = 0.0f;
	color.b = 0.0f;

	float		color_coef = 1.0f;
	t_color		clr_coef;
	clr_coef.r = 1.0f;
	clr_coef.g = 1.0f;
	clr_coef.b = 1.0f;

	/* material of hit object*/
	t_material	instance_material;

	bool		continue_loop = true;
	uchar		tree_depth = 0;

	while (continue_loop)
	{
		tree_depth++;

		if (scene_intersection(scene, ray, &shade_rec))
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

			/* if normal is not directed to us then we reverse normal*/
			shade_rec.normal = dot(shade_rec.normal, ray.direction) < 0.0f ?
				shade_rec.normal : -shade_rec.normal;

			instance_material = get_instance_material(scene.instance_manager,
														instance);

			/* shade material at hit point and accumulate color */
			color = color_sum(color,
							float_color_multi(color_coef,
											shade_material(scene,
															sampler_manager,
															instance_material,
															shade_rec, options,
															seed)));

			if (instance_material.is_reflective
				&& tree_depth < 64 && color_coef > 0.01f)
			{
				ray.origin = shade_rec.hit_point + 1e-2f * shade_rec.normal;
				ray.direction = get_reflected_vector(-ray.direction,
													shade_rec.normal);
				color_coef *= instance_material.kr;
			}
			else
				continue_loop = false;
		}
		else /* no hit */
		{
			continue_loop = false;
		}
	};
	return (color);
}
