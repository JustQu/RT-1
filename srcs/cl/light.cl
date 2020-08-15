float4	get_light_direction(t_light light, t_shade_rec shade_rec)
{
	if (light.type == ambient)
		return ((float4)(0.0f, 0.0f, 0.0f, 0.0f));
	else if (light.type == point)
		return (normalize(light.origin - shade_rec.hit_point));
	else if (light.type == directional)
		return -normalize(light.direction);
	else if (light.type == area)
	{
		;//todo
	}
}

 t_color	get_light_radiance(t_light light)
{
	t_color	color;

	if (light.type == ambient)
	{
		color.r = light.color.r * light.ls;
		color.g = light.color.g * light.ls;
		color.b = light.color.b * light.ls;
		return (color);
	}
}
