void	init_scene(t_scene *scene,
					__constant t_instance *instances, int ninstances,
					__global t_obj *objects, int nobjects,
					__constant t_triangle *triangles, int ntriangles,
					__global t_matrix *matrices, int nmatrices,
					__constant t_light *lights, int nlights,
					__global t_bvh_node *bvh,

					__global t_texture *textures,
					__global float4 *ranvec,
					__global int *perm_x,
					__global int *perm_y,
					__global int *perm_z,

					t_camera camera, t_light ambient_light,
					t_ambient_occluder ambient_occluder)
{
	scene->instance_manager.instances = instances;
	scene->instance_manager.ninstances = ninstances;
	scene->instance_manager.objects = objects;
	scene->instance_manager.nobjects = nobjects;
	scene->instance_manager.triangles = triangles;
	scene->instance_manager.ntriangles = ntriangles;
	scene->instance_manager.matrices = matrices;
	scene->instance_manager.nmatrices = nmatrices;

	scene->instance_manager.tex_mngr.textures = textures;
	scene->instance_manager.tex_mngr.perlin_noise = ranvec;
	scene->instance_manager.tex_mngr.perm_x  = perm_x;
	scene->instance_manager.tex_mngr.perm_y = perm_y;
	scene->instance_manager.tex_mngr.perm_z = perm_z;

	scene->lights = lights;
	scene->nlights = nlights;
	scene->bvh = bvh;
	scene->camera = camera;
	scene->ambient_light = ambient_light;
	scene->ambient_occluder = ambient_occluder;
}

void	init_sampler_manager(t_sampler_manager *sampler_manager,
							__global t_sampler *samplers,
							__global float2 *samples,
							__global float2 *disk_samples,
							__global float3 *hemisphere_samples)
{
	sampler_manager->samplers = samplers;
	sampler_manager->samples = samples;
	sampler_manager->disk_samples = disk_samples;
	sampler_manager->hemisphere_samples = hemisphere_samples;
}

float		hash(float seed)
{
	float res;
	return fract(sin(seed) * 43758.5453123, &res);
}

/*
** Новый кернел.
** Поскольку драйвер убивает кернел если он выполняется дольше чем 0,5 секунды,
** нам надо  его уменьшить. При каждом вызове будет считать по одной точке антиалиасинга.
** В дальнейшем когда будут сделаны материалы / преломления / отражения можно будет еще
** больше разбить кернел чтобы избежать дивергенции кода.
*/												//Pos of argument on host
__kernel  __attribute__((work_group_size_hint(32, 1, 1)))
void main_kernel(__global t_color *image,	//0
				int step,						//1

				__constant t_instance *instances, int ninstances, //2, 3
				__global t_obj *objects, int nobjects,		//4, 5
				__constant t_triangle *triangles, int ntriangles, //6, 7
				__global t_matrix *matrices, int nmatrices,	//8, 9
				__constant t_light *lights, int nlights,		//10, 11
				t_camera camera,		//12
				t_light ambient_light,	//13
				t_ambient_occluder ambient_occluder, //14

				__global t_bvh_node	*bvh, //15

				t_rt_options options, //16

				__global t_sampler *samplers, //17
				__global float2 *samples, //18
				__global float2 *disk_samples,	//19
				__global float3 *hemisphere_samples, //20
				uint num,	//21

				__global t_texture *textures, //22
				__global float4 *ranvec,	//23
				__global int *perm_x,		//24
				__global int *perm_y,		//25
				__global int *perm_z)		//26
{
	int					global_id;
	int					x;
	int					y;
	uint2				seed;
	t_scene				scene;
	t_sampler_manager	sampler_manager;

	t_ray				ray;
	t_color				color;
	t_sampler			camera_sampler;
	t_sampler			ao_sampler;

	/* Инициализируем нужные переменные и структуры */
	global_id = get_global_id(0);
	if (global_id == 0)
		printf("Rendering: %f%%\n", step / options.spp * 100.0f);
	x = global_id % camera.viewplane.width;
	y = global_id / camera.viewplane.width;

	seed.x = global_id + x + num;
	seed.y = y + get_local_id(0) + get_group_id(0);
	seed.y = random(&seed);

	float4 state;
	float2 s;

	s.x = seed.x;
	s.y = seed.y / ((float)num + 1.0f) * 43534.0f - num;

	state.x = hash(s.x + seed.x);
	state.y = hash(s.y + state.x);
	state.z = hash(state.x + state.y);
	state.w = hash(num + s.y - state.x * state.y);
	GPURnd(&state);
	// GPURnd(&state);
	// GPURnd(&state);

	init_scene(&scene,
				instances, ninstances, objects, nobjects,
				triangles, ntriangles, matrices, nmatrices,
				lights, nlights, bvh,
				textures, ranvec, perm_x, perm_y, perm_z,
				camera, ambient_light, ambient_occluder);

	init_sampler_manager(&sampler_manager, samplers, samples, disk_samples, hemisphere_samples);

	/* получаем семплер для антиалиасинга и текущий шаг. */
	ao_sampler = get_sampler(sampler_manager, options.aa_id);
	ao_sampler.count = global_id * ao_sampler.num_samples + step;

	/* Если это не первый шаг, то считаем прыжок для семплеров */
	if (step != 0)
	{
		ao_sampler.jump = ((num + random(&seed)) % ao_sampler.num_sets) * ao_sampler.num_samples;
		options.ambient_occluder_sampler.jump = (random(&seed) % options.ambient_occluder_sampler.num_sets) * options.ambient_occluder_sampler.num_samples;
	}
	else if (options.reset == 1)
	{
		image[global_id] = (t_color){.r = 0.0f, .g = 0.0f, .b = 0.0f};
	}

	/* */
	float2	sp = sample_unit_square(&ao_sampler, sampler_manager.samples, &seed);
	float	dx = x + GPURnd(&state);
	float	dy = y + GPURnd(&state);

	if (scene.camera.type == thin_lens)
	{
		camera_sampler = get_sampler(sampler_manager, scene.camera.sampler_id);
		camera_sampler.count = global_id * camera_sampler.num_samples + step;
		if (step != 0)
			camera_sampler.jump = (random(&seed) % camera_sampler.num_sets) * camera_sampler.num_samples;
	}

	if (false && global_id == 0 && step == 0)
	{
		printf("GPU:\nobj %u\n", sizeof(t_obj));
		printf("instance %u\n", sizeof(t_instance));
		printf("matrix %u\n", sizeof(t_matrix));
		printf("material %u\n", sizeof(t_material));
		printf("triangle %u\n", sizeof(t_triangle));
		printf("N: %d\n", nobjects);
		print_all(scene);
	}

	ray = cast_camera_ray(scene.camera, dx, dy, sampler_manager, &camera_sampler, &seed, &state);

	// color = ray_trace(ray, scene, options, sampler_manager, &seed);

	color = path_tracer2(ray, scene, options, sampler_manager, &seed, &state);

	image[global_id] = color_sum(image[global_id], color);
}

typedef union cnv
{
	uint	a;
	float4	b;
}cnv;

__kernel void	noise(__global t_color *img)
{
	int		gid = get_global_id(0);
	int		x = gid % 1200;
	int		y = gid / 1200;

	float4	state;

	float2 seed;

	seed.x = x;
	seed.y = y;
	seed = (seed * 2.0f - (float2)(1200.0f, 600.0f)) / 600.0f;

	state.x = hash(seed.x);
	state.y = hash(seed.y + state.x);
	state.z = hash(state.x + state.y);
	state.w = hash(seed.y + dot(state.xyz, (float3)(1.1f)));

	float	n;
	for (int i = 0; i < 1; i++)
	{
		n = GPURnd(&state);
	}

	t_color color;

	n = GPURnd(&state);
	color.r = n;
	color.g = n;
	color.b = n;
	img[gid] = color;
}