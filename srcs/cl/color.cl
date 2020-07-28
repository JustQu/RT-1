t_color	color_sum(t_color a, t_color b)
{
	t_color res;
	res.b = clamp(a.b + b.b, 0, 255);
	res.g = clamp(a.g + b.g, 0, 255);
	res.r = clamp(a.r + b.r, 0, 255);
	return (res);
}

t_color	color_multi(t_color a, t_color b)
{
	t_color	res;

	res.r = clamp(a.r * b.r / 255.0f, 0.0f, 255.0f);
	res.g = clamp(a.g * b.g / 255.0f, 0.0f, 255.0f);
	res.b = clamp(a.b * b.b / 255.0f, 0.0f, 255.0f);
	return (res);
}

t_color	float_color_multi(float	c, t_color color)
{
	t_color	res;

	res.b = clamp(c * color.b, 0.0f, 255.0f);
	res.g = clamp(c * color.g, 0.0f, 255.0f);
	res.r = clamp(c * color.r, 0.0f, 255.0f);
	return (res);
}
