t_texture	get_texture(t_texture_manager texture_manager, int texture_id)
{
	return (texture_manager.textures[texture_id]);
}

t_color		get_solid_texture_color(t_texture texture)
{
	return (texture.data.solid.color);
}

/*
** checker 3d
*/
t_color		get_checker_texture_color(t_texture texture, float4 point)
{
	// if (((int)(floor(point.x / 0.3f)) +
	// 	(int)(floor(point.y / 0.3f)) +
	// 	(int)(floor(point.z / 0.3f))) % 2 == 0)
	// {
	// 	return (texture.data.checker.odd);
	// }
	// else
	// {
	// 	return (texture.data.checker.even);
	// }

	float sines = sin(10.0f * point.x) * sin(10.0f * point.y) * sin(10.0f * point.z);
	if (sines < 0)
	{
		return (texture.data.checker.odd);
	}
	else
	{
		return (texture.data.checker.even);
	}
		return ((t_color){ .r = 0.0, .g = 1.0f, .b = 0.0f });
}

/*
** plane checker
*/
t_color		get_checker2d_texture_color(t_texture texture, float4 point)
{
	/* divide by texture size. 1.0f For default and testing purpose */
	int	ix = floor(point.x / 1.0f);
	int	iz = floor(point.z / 1.0f);
	float	fx = point.x / 1.0f - ix;
	float	fz = point.z / 1.0f - iz;
}

t_color		get_perlin_texture_color(t_texture_manager mngr,
									float4 point)
{
	return (float_color_multi(perlin_noise(mngr.perlin_noise, mngr.perm_x,
											mngr.perm_y, mngr.perm_z, point),
							(t_color){ .r = 1.0f, .g = 1.0f, .b = 1.0f }));
}

t_color	get_smooth_perlin_texture_color(t_texture_manager mngr,
										t_texture tex,
										float4 point)
{
	return (float_color_multi(smooth_perlin_noise(mngr.perlin_noise,
								mngr.perm_x, mngr.perm_y,
								mngr.perm_z,
								tex.data.smooth_perlin.scale * point),
							(t_color){ .r = 1.0f, .g = 1.0f, .b = 1.0f }));
}

t_color	get_turbulence_perlin_texture_color(t_texture_manager mngr,
											t_texture tex, float4 point)
{
	return (float_color_multi(
				turbulence_perlin_noise(mngr.perlin_noise, mngr.perm_x,
										mngr.perm_y, mngr.perm_z,
										tex.data.smooth_perlin.scale * point),
				(t_color){ .r = 1.0f, .g = 1.0f, .b = 1.0f }));
}

t_color		get_wave_perlin_texture_color(t_texture_manager mngr,
										t_texture tex, float4 point)
{
	return (float_color_multi(0.5f * (1 +
				sin(tex.data.smooth_perlin.scale * point.z + 10 *
				turbulence_perlin_noise(mngr.perlin_noise, mngr.perm_x,
					mngr.perm_y, mngr.perm_z, point))),
			(t_color){ .r = 1.0f, .g = 1.0f, .b = 1.0f }));
}

/*
** TODO(dmelessa): replace textures with texure manager
*/
t_color		get_color(t_texture_manager texture_manager,
					t_material material,
					t_shade_rec *shade_rec /* hit point */)
{
	t_texture	texture;

	texture = get_texture(texture_manager, material.texture_id);

	if (texture.type == solid)
	{
		return (get_solid_texture_color(texture));
	}
	else if (texture.type == checker)
	{
		return (get_checker_texture_color(texture, shade_rec->hit_point));
	}
	else if (texture.type == perlin)
	{
		return (get_perlin_texture_color(texture_manager, shade_rec->hit_point));
	}
	else if (texture.type == smooth_perlin)
	{
		return (get_smooth_perlin_texture_color(texture_manager,
												texture,
												shade_rec->hit_point));
	}
	else if (texture.type == turbulence_perlin)
	{
		return (get_turbulence_perlin_texture_color(texture_manager,
													texture,
													shade_rec->hit_point));
	}
	else if (texture.type == wave_perlin)
	{
		return (get_wave_perlin_texture_color(texture_manager, texture, shade_rec->hit_point));
	}
}
