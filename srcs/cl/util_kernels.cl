typedef union
{
	struct
	{
		char b;
		char g;
		char r;
		char a;
	};
	int	value;
}	int_color;

__kernel void translate_image(__global t_color *rgb_image,
							__global uint *uint_image,
							int num_samples)
{
	t_color			color;
	int				global_id = get_global_id(0);
	uint			value;
	int_color		int_clr;

	color = rgb_image[global_id];
	color.r = color.r / num_samples;
	color.g = color.g / num_samples;
	color.b = color.b / num_samples;

	color.r = clamp(color.r, 0.0f, 1.0f);
	color.g = clamp(color.g, 0.0f, 1.0f);
	color.b = clamp(color.b, 0.0f, 1.0f);

	int_clr.r = color.r * 255.0f;
	int_clr.g = color.g * 255.0f;
	int_clr.b = color.b * 255.0f;
	int_clr.a = 0;

	uint_image[global_id] = int_clr.value;
}
