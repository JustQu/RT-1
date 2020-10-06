t_texture	get_texture(__global t_texture *textures, int texture_id)
{
	return (textures[texture_id]);
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

t_color		get_color(__global t_texture *textures, t_material material,
						t_shade_rec *shade_rec /* hit point */)
{
	t_texture	texture;

	texture = get_texture(textures, material.texture_id);

	if (texture.type == solid)
	{
		return (get_solid_texture_color(texture));
	}
	else if (texture.type == checker)
	{
		return (get_checker_texture_color(texture, shade_rec->hit_point));
	}
}
