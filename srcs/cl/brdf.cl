/*
** BRDF - bidirectional reflectance distributuin functions
** the function f returns the BRDF itself, unless it contains the delta function
**
** the function sample_f is used to compute the direction of reflected rays for
** simulating reflective materials and diffuse-diffuse light transport
**
** the function rho returns the bihemispherical reflectance
*/

/*
** BRDF
** 	Lambertian
**	PerfectSpecular
** 	GlossySpecular
*/

t_color	lambertian_f(float kd, t_color color)
{
	return (float_color_multi(kd * (float)M_1_PI, color));
}

t_color	lambertian_rho(float kd, t_color color)
{
	t_color	res;

	res = float_color_multi(kd, color);
	return (res);
}

float	glossy_specular_f(float4 camera_direction, float4 normal, float4 light_direction, float ks, float exp)
{
	float	res = 0;
	float4	r = get_reflected_vector(light_direction, normal);
	float	rdotdir = dot(r, camera_direction);

	if (rdotdir > 0)
		res = ks * pow(rdotdir, exp);
	return res;
}

t_color	perfect_specular_f(float4 ray_dir, float4 normal, float kr, t_color cr)
{
	float	ndotwo = dot(normal, ray_dir);
	float4	wi = -ray_dir + 2.0f * normal * ndotwo;

	return (float_color_multi(kr / dor(normal, wi), cr));
}
