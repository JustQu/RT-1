
void	print_material(t_material material)
{
	printf("\t\tType:\t");
	if (material.type == phong)
		printf("phong");
	else if (material.type == matte)
		printf("matte");
	else
	{
		printf("\033[0;31m");
		printf("~ERROR~");
		printf("\033[0m");
	}
	printf("\n");
	// printf("\t\tColor:\t%f %f %f| %d\n", material.color.r,
	// 	material.color.g, material.color.b,
	// 	((int)(material.color.r * 255) << 16) + ((int)(material.color.g * 255) << 8) + material.color.b);
	printf("\t\tKd:\t%f\n", material.kd);
	printf("\t\tKa:\t%f\n", material.ka);
	if (material.type == phong)
	{
		printf("\t\tKs:\t%f\n", material.ks);
		printf("\t\tExp:\t%f\n", material.exp);
	}
}

void	print_vector(float4	vec)
{
	printf("Vector: (%f, %f, %f, %f)\n", vec.x, vec.y, vec.z, vec.w);
}

void	print_camera(t_camera camera)
{
	printf("Camera:\n");
	printf("\tViewplane:\n");
}

void	print_sampler(t_sampler sampler, int id)
{
	printf("Sampler #%d:", id);
	printf("\tType: %d\n", sampler.type);
	printf("\tnum_samples %d\n", sampler.num_sets);
	printf("\tnum_sets %d\n", sampler.count);
	printf("\tjump %d\n", sampler.jump);
	printf("\tsamples_type %d\n", sampler.samples_type);
	printf("\toffset %d\n", sampler.offset);
	printf("\tdisk samples offset %d\n", sampler.disk_samples_offset);
	printf("\themisphere samples offset %d\n", sampler.hemisphere_samples_offset);
}

void	print_samples(t_sampler_manager *sampler_manager, t_sampler sampler)
{
	int		offset;

	offset = sampler.num_samples * sampler.num_sets;

}


void	print_instance(t_instance instance)
{
	printf("\tType:\t");
	if (instance.type == sphere)
		printf("sphere");
	else if (instance.type == plane)
		printf("plane");
	else if (instance.type == cone)
		printf("cone");
	else if (instance.type == cylinder)
		printf("cylinder");
	else if (instance.type == torus)
		printf("torus");
	else if (instance.type == triangle)
		printf("triangle");
	else if (instance.type == disk)
		printf("disk");
	else if (instance.type == paraboloid)
		printf("paraboloid");
	else if (instance.type == box)
		printf("box");
	else if (instance.type == rectangle)
		printf("rectangle");
	else
	{
		printf("\033[0;31m");
		printf("~ERROR~");
		printf("\033[0m");
	}
	printf("\n");
	printf("\tObject id:\t%d\n", instance.object_id);
	printf("\tMatrix id:\t%d\n", instance.matrix_id);
	printf("\tMaterial:\t\n");
	print_material(instance.material);
}

void	print_object(t_obj object)
{
	// printf("\t\tBounding box:\t(%f, %f, %f, %f)\n", object.bounding_box.min.x,
	// 												object.bounding_box.min.y,
	// 												object.bounding_box.min.z,
	// 												object.bounding_box.min.w);
	// printf("\t\t\t\t(%f, %f, %f, %f)\n", object.bounding_box.max.x,
	// 									object.bounding_box.max.y,
	// 									object.bounding_box.max.z,
	// 									object.bounding_box.max.w);
	printf("\t\tOrigin:\t\t(%f, %f, %f, %f)\n", object.origin.x,
												object.origin.y,
												object.origin.z,
												object.origin.w);
	// printf("\t\tDirection:\t(%f, %f, %f, %f)\n", object.direction.x,
	// 											object.direction.y,
	// 											object.direction.z,
	// 											object.direction.w);
	// printf("\t\tDir2:\t\t(%f, %f, %f, %f)\n", object.dir2.x,
	// 										object.dir2.y,
	// 										object.dir2.z,
	// 										object.dir2.w);
	printf("\t\tNormal:\t\t(%f, %f, %f, %f)\n", object.normal.x,
												object.normal.y,
												object.normal.z,
												object.normal.w);
	printf("\t\tRadius:\t\t%f\n", object.r);
	printf("\t\tRadis2:\t\t%f\n", object.r2);
	printf("\t\tmaxm:\t\t%f\n", object.maxm);
	printf("\t\tminm:\t\t%f\n", object.minm);
	printf("\t\tshadows:\t%d\n", object.shadows);
	printf("\t\tsampler_id: %d\n", object.sampler_id);
}

void	print_matrix(t_matrix matrix)
{
	// if (get_global_id(0) != 0)
	// 	return ;
	printf("\t\t|%.6f %.6f %.6f %.6f|\n", matrix.s0, matrix.s1, matrix.s2, matrix.s3);
	printf("\t\t|%.6f %.6f %.6f %.6f|\n", matrix.s4, matrix.s5, matrix.s6, matrix.s7);
	printf("\t\t|%.6f %.6f %.6f %.6f|\n", matrix.s8, matrix.s9, matrix.sA, matrix.sB);
	printf("\t\t|%.6f %.6f %.6f %.6f|\n", matrix.sC, matrix.sD, matrix.sE, matrix.sF);
}

void	print_all(t_scene scene)
{
	t_instance	instance;

#if OPEN_CL
	printf("TEST\n");
#endif

	printf("Scene:\n");
	for (int i = 0; i < scene.instance_manager.ninstances; i++)
	{
		instance = scene.instance_manager.instances[i];
		printf("Instance #%d:\n", i);
		print_instance(instance);
		if (instance.type == triangle)
		{
		}
		else
		{
			printf("\tObject: \n");
			print_object(scene.instance_manager.objects[instance.object_id]);
		}
		if (instance.matrix_id > -1)
		{
			printf("\tMatrix:\n");
			print_matrix(scene.instance_manager.matrices[instance.matrix_id]);
		}
	}
}
