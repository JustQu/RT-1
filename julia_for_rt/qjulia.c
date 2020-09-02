/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qjulia.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 15:28:34 by user              #+#    #+#             */
/*   Updated: 2020/09/02 18:04:13 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "julia.h"

#define WIDTH 1200
#define HEIGHT 800

#define GL_SILENCE_DEPRECATION
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl.h>
#include <OpenGL/CGLDevice.h>
#include <GLUT/glut.h>
#include <OpenCL/opencl.h>

#include <mach/mach_time.h>
#include <math.h>

#include <fcntl.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <mach/mach_time.h>

#define COMPUTE_KERNEL_FILENAME	("qjulia_kernel.cl")
#define COMPUTE_KERNEL_METHOD_NAME ("QJuliaKernel")

static int animated		= 0;
static int update		= 1;

static cl_context		compute_context;
static cl_command_queue	compute_commands;
static cl_device_type	compute_device_type;
static cl_device_id		compute_device_id;

static cl_program		compute_program;
static cl_kernel		compute_kernel;
static cl_mem			compute_result;
static cl_mem			compute_image;

static size_t			max_work_group_size;
static int				work_group_size[2];
static int				work_group_items = 32;

static uint texture_id = 0;
static uint texture_width = WIDTH;
static uint texture_height = HEIGHT;
static uint texture_target = GL_TEXTURE_2D;
static uint texture_format = GL_RGBA;
static uint texture_type	= GL_UNSIGNED_BYTE;
static uint texture_internal = GL_RGBA;
static size_t texture_type_size = sizeof(char);
static uint active_texture_uint = 0x84C1;
static void *host_image_buffer = 0;

static float mut			= 0.0f;
static float mua[4]			= { -.278f, -.479f, 0.0f, 0.0f };
static float mub[4]			= { 0.278f, 0.479f, 0.0f, 0.0f };
static float muc[4]			= { -.278f, -.479f, -.231f, .235f };

static float epsilon		= 0.003f;

static float color_t		= 0.0f;
static float color_a[4]		= { 0.25f, 0.45f, 1.0f, 1.0f };
static float color_b[4]		= { 0.25f, 0.45f, 1.0f, 1.0f };
static float color_c[4]		= { 0.25f, 0.45f, 1.0f, 1.0f };

static float shadow_text_color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
static float highlight_text_color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
static uint text_offset[2]			= { 25, 25};

static double time_elapsed	= 0;
static int frame_count 		= 0;
static uint report_stats_interval = 30;

static float tex_coords[4][2];

static float vertex_pos[4][2] = { { -1.0f, -1.0f},
								  { +1.0f, -1.0f},
								  { +1.0f, +1.0f},
								  { -1.0f, +1.0f} };

static uint show_stats		= 1;
static char stats_string[512] = "\0";
static uint show_info		= 1;
static char info_string[512] = "\0";

void	create_texture()
{
	if (texture_id)
		glDeleteTextures(1, &texture_id);
	texture_id = 0;

	printf("Creating Texture %d x %d...\n", WIDTH, HEIGHT);

	texture_width = WIDTH;
	texture_height = HEIGHT;

	glActiveTextureARB(active_texture_uint);
	glGenTextures(1, &texture_id);
	glBindTexture(texture_target, texture_id);
	glTexParameteri(texture_target, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(texture_target, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(texture_target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(texture_target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(texture_target, 0, texture_internal, texture_width, texture_height, 0,
				texture_format, texture_type, 0);
	glBindTexture(texture_target, 0);
}

int		setup_graphics()
{
	create_texture();

	glClearColor(0.0, 0.0, 0.0, 0.0);

	glDisable(GL_DEPTH_TEST);
	glActiveTexture(GL_TEXTURE0);
	glViewport(0,0, WIDTH, HEIGHT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	tex_coords[3][0] = 0.0f;
	tex_coords[3][1] = 0.0f;
	tex_coords[2][0] = WIDTH;
	tex_coords[2][1] = 0.0f;
	tex_coords[1][0] = WIDTH;
	tex_coords[1][1] = HEIGHT;
	tex_coords[0][0] = 0.0f;
	tex_coords[0][1] = HEIGHT;

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, vertex_pos);
	glClientActiveTexture(GL_TEXTURE0);
	glTexCoordPointer(2, GL_FLOAT, 0, tex_coords);
	return (GL_NO_ERROR);
}

int		setup_compute_device()
{
	int err;
	size_t return_size;
	compute_device_type = CL_DEVICE_TYPE_GPU;

	CGLContextObj kcgl_context = CGLGetCurrentContext();
	CGLShareGroupObj kcgl_shape_group = CGLGetShareGroup(kcgl_context);

	cl_context_properties properties[] = {
		CL_CONTEXT_PROPERTY_USE_CGL_SHAREGROUP_APPLE,
		(cl_context_properties)kcgl_shape_group, 0
	};

	compute_context = clCreateContext(properties, 0, 0, clLogMessagesToStderrAPPLE, 0, 0);
	if (!compute_context)
		printf("Error: Failed to create a compute context!\n");

	unsigned int device_count;
	cl_device_id device_ids[16];

	err = clGetContextInfo(compute_context, CL_CONTEXT_DEVICES, sizeof(device_ids), device_ids, &return_size);
	if (err)
		printf("Error: Failed to retrieve compute devices for context!\n");

	device_count = return_size / sizeof(cl_device_id);

	int i = 0;
	int device_found = 0;
	cl_device_type device_type;
	while (i < device_count)
	{
		clGetDeviceInfo(device_ids[i], CL_DEVICE_TYPE, sizeof(cl_device_type), &device_type, NULL);
		if (device_type == compute_device_type)
		{
			compute_device_id = device_ids[i];
			device_found = 1;
			break ;
		}
		i++;
	}

	if (!device_found)
		printf("Error: Failed to locate compute device!\n");

	compute_commands = clCreateCommandQueue(compute_context, compute_device_id, 0, &err);
	if (!compute_commands)
		printf("Error: Failed to create a command queue!\n");

	cl_char vendor_name[1024] = {0};
	cl_char device_name[1024] = {0};
	err = clGetDeviceInfo(compute_device_id, CL_DEVICE_VENDOR, sizeof(vendor_name), vendor_name, &return_size);
	err |= clGetDeviceInfo(compute_device_id, CL_DEVICE_NAME, sizeof(device_name), device_name, &return_size);
	if (err != CL_SUCCESS)
		printf("Error: Failed to retrieve device info!\n");

	return (CL_SUCCESS);
}

int		load_text_from_file(
		const char *file_name, char **result_string, size_t *string_len)
{
	int fd;
	unsigned file_len;
	struct stat file_status;
	int ret;

	*string_len = 0;
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		printf("Error opening file %s\n", file_name);
		return -1;
	}
	ret = fstat(fd, &file_status);
	if (ret)
	{
		printf("Error reading status for file %s\n", file_name);
        return -1;
	}
	file_len = file_status.st_size;

	*result_string = (char*)calloc(file_len + 1, sizeof(char));
	ret = read(fd, *result_string, file_len);
	if (!ret)
	{
		printf("Error reading from file %s\n", file_name);
        return -1;
	}
	close (fd);

	*string_len = file_len;
	return 0;
}

int		setup_compute_kernel()
{
	int err = 0;
	char *source = 0;
	size_t lenght = 0;

	if (compute_kernel)
		clReleaseKernel(compute_kernel);
	compute_kernel = 0;

	if (compute_program)
		clReleaseProgram(compute_program);
	compute_program = 0;

	printf("Loading kernel source from file '%s'...\n", COMPUTE_KERNEL_FILENAME);
	err = load_text_from_file(COMPUTE_KERNEL_FILENAME, &source, &lenght);
	if (!source || err)
	{
		printf("Error: Failed to load kernel source!\n");
	}

	const char *width_macro = "#define WIDTH";
	const char *height_macro = "#define HEIGHT";

	char *preprocess = malloc(strlen(source) + 1024);
	sprintf(preprocess, "\n%s (%d)\n%s (%d)\n%s", width_macro, WIDTH, height_macro, HEIGHT, source);

	compute_program = clCreateProgramWithSource(compute_context, 1, (const char **)&preprocess, NULL, &err);
	if (!compute_program || err != CL_SUCCESS)
		printf("Error: Failed to create compute program!\n");
	free(source);
	free(preprocess);

	err = clBuildProgram(compute_program, 0, NULL, NULL, NULL, NULL);
	if (err != CL_SUCCESS)
	{
		size_t len;
		char buffer[2048];

		printf("Error: Failed to build program executable!\n");
		clGetProgramBuildInfo(compute_program, compute_device_id, CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, &len);
		printf("%s\n", buffer);
	}

	printf("Creating kernel '%s'...\n", COMPUTE_KERNEL_METHOD_NAME);
	compute_kernel = clCreateKernel(compute_program, COMPUTE_KERNEL_METHOD_NAME, &err);
	if (!compute_kernel || err != CL_SUCCESS)
	{
		printf("Error: Failed to create compute kernel!\n");
	}
	err = clGetKernelWorkGroupInfo(compute_kernel, compute_device_id, CL_KERNEL_WORK_GROUP_SIZE, sizeof(size_t), &max_work_group_size, NULL);
	if (err != CL_SUCCESS)
		printf("Error: Failed to retrieve kernel work group info! %d\n", err);

	work_group_size[0] = (max_work_group_size > 1) ? (max_work_group_size / work_group_items) : max_work_group_size;
	work_group_size[1] = max_work_group_size / work_group_size[0];

	return CL_SUCCESS;
}

int		create_compute_result()
{
	int err = 0;

	if (compute_image)
		clReleaseMemObject(compute_image);
	compute_image = 0;

	printf("Allocating compute result image in device memory...\n");
	compute_image = clCreateFromGLTexture2D(compute_context, CL_MEM_WRITE_ONLY, texture_target, 0, texture_id, &err);
	if (!compute_image || err != CL_SUCCESS)
		printf("Failed to create OpenGL texture reference! %d\n", err);

	if (compute_result)
		clReleaseMemObject(compute_result);
	compute_result = 0;

	compute_result = clCreateBuffer(compute_context, CL_MEM_WRITE_ONLY, texture_type_size * 4 * texture_width * texture_height, NULL, NULL);
	if (!compute_result)
		printf("Failed to create OpenCL array!\n");

	return CL_SUCCESS;
}

void	random_color(float v[4])
{
	uint seed;

	seed = (uint)mach_absolute_time(); /* get current time */
	v[0] = 2.0f * rand_r(&seed) / (float) RAND_MAX - 1.0f;
	v[1] = 2.0f * rand_r(&seed) / (float) RAND_MAX - 1.0f;
	v[2] = 2.0f * rand_r(&seed) / (float) RAND_MAX - 1.0f;
	v[3] = 1.0f;
}

void	update_mu(float t[4], float a[4], float b[4])
{
	*t += 0.01f;

	uint seed = (uint)mach_absolute_time();

	if (*t >= 1.0f)
	{
		*t = 0.0f;

		a[0] = b[0];
		a[1] = b[1];
		a[2] = b[2];
		a[3] = b[3];

		b[0] = 2.0f * rand_r(&seed) / (float)RAND_MAX - 1.0f;
		b[1] = 2.0f * rand_r(&seed) / (float)RAND_MAX - 1.0f;
		b[2] = 2.0f * rand_r(&seed) / (float)RAND_MAX - 1.0f;
		b[3] = 2.0f * rand_r(&seed) / (float)RAND_MAX - 1.0f;
	}
}

void	interpolate(float m[4], float t, float a[4], float b[4])
{
	int i;

	i = 0;
	while (i < 4)
	{
		m[i] = (1.0f - t) * a[i] + t * b[i];
		i++;
	}
}

int		divide_up(int a, int b)
{
	return ((a % b) != 0) ? (a / b + 1) : (a / b);
}

int		recompute()
{
	if (!compute_kernel || !compute_result)
		return CL_SUCCESS;

	void *values[10];
	size_t sizes[10];
	size_t global[2];
	size_t local[2];

	int err = 0;
	unsigned int v = 0;
	unsigned int s = 0;
	unsigned int a = 0;
	values[v++] = &compute_result;
	values[v++] = muc;
	values[v++] = color_c;
	values[v++] = &epsilon;

	sizes[s++] = sizeof(cl_mem);
	sizes[s++] = 4 * (sizeof(float));
	sizes[s++] = 4 * (sizeof(float));
	sizes[s++] = sizeof(float);

	if (animated || update)
	{
		update = 0;
		err = CL_SUCCESS;

		a = 0;
		while (a < s)
		{
			err |= clSetKernelArg(compute_kernel, a, sizes[a], values[a]);
			a++;
		}
		if (err)
			return -10;
	}

	int size_x = work_group_size[0];
	int size_y = work_group_size[1];

	global[0] = divide_up(texture_width, size_x) * size_x;
	global[1] = divide_up(texture_height, size_y) * size_y;

	local[0] = size_x;
	local[1] = size_y;

	err = clEnqueueNDRangeKernel(compute_commands, compute_kernel, 2, NULL, global, local, 0, NULL, NULL);
	if (err)
		printf("Failed to enqueue kernel! %d\n", err);

	err = clEnqueueAcquireGLObjects(compute_commands, 1, &compute_image, 0, 0, 0);
	if (err != CL_SUCCESS)
		printf("Failed to acquire GL object! %d\n", err);

	size_t origin[] = { 0, 0, 0 };
	size_t region[] = { texture_width, texture_height, 1 };
	err = clEnqueueCopyBufferToImage(compute_commands, compute_result, compute_image,
									0, origin, region, 0, NULL, 0);
	if (err != CL_SUCCESS)
		printf("Failed to copy buffer to image! %d\n", err);

	err = clEnqueueReleaseGLObjects(compute_commands, 1, &compute_image, 0, 0, 0);
	if (err != CL_SUCCESS)
		printf("Failed to release GL object! %d\n", err);

	return CL_SUCCESS;
}

void	update_color(float t[4], float a[4], float b[4])
{
	*t += 0.01f;

	if (*t >= 1.0f)
	{
		*t = 0.0f;

		a[0] = b[0];
		a[1] = b[1];
		a[2] = b[2];
		a[3] = b[3];

		random_color(b);
	}
}

void	render_texture(void *pv_data)
{
	glDisable(GL_LIGHTING);

	glViewport(0, 0, WIDTH, HEIGHT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D( -1.0, 1.0, -1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(texture_target);
	glBindTexture(texture_target, texture_id);
	if (pv_data)
		glTexSubImage2D(texture_target, 0, 0, 0, texture_width,
			texture_height, texture_format, texture_type, pv_data);

	glTexParameteri(texture_target, GL_TEXTURE_COMPARE_MODE, GL_NONE);
	glBegin(GL_QUADS);
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f( -1.0f, -1.0f, 0.0f);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, 0.0f);

		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, 0.0f);

		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, 0.0f);
	}
	glEnd();
	glBindTexture(texture_target, 0);
	glDisable(texture_target);
}

void	draw_string(float x, float y, float color[4], char *buffer)
{
	unsigned int uilen;
	unsigned int i;

	glPushAttrib(GL_LIGHTING_BIT);
	glDisable(GL_LIGHTING);

	glRasterPos2f(x, y);
	glColor3f(color[0], color[1], color[2]);
	uilen = (unsigned int)strlen(buffer);
	i = 0;
	while (i < uilen)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, buffer[i]);
		i++;
	}
	glPopAttrib();
}

void	draw_text(float x, float y, int light, char *format, ...)
{
	va_list args;
	char buffer[256];
	GLint ivp[4];
	GLint imatrix_mode;

	va_start(args, format);
	vsprintf(buffer, format, args);
	va_end(args);

	glPushAttrib(GL_LIGHTING_BIT);
	glDisable(GL_LIGHTING);
	glDisable(GL_BLEND);

	glGetIntegerv(GL_VIEWPORT, ivp);
	glViewport(0, 0, WIDTH, HEIGHT);
	glGetIntegerv(GL_MATRIX_MODE, &imatrix_mode);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glScalef(2.0f / WIDTH, -2.0f / HEIGHT, 1.0f);
	glTranslatef(-WIDTH / 2.0f, -HEIGHT / 2.0f, 0.0f);

	if (light)
	{
		glColor4fv(shadow_text_color);
		draw_string(x - 0, y - 0, shadow_text_color, buffer);

		glColor4fv(highlight_text_color);
		draw_string(x - 2, y - 2, highlight_text_color, buffer);
	}
	else
	{
		glColor4fv(highlight_text_color);
		draw_string(x - 0, y - 0, highlight_text_color, buffer);

		glColor4fv(shadow_text_color);
		draw_string(x - 2, y - 2, shadow_text_color, buffer);
	}


	glPopMatrix();
	glMatrixMode(GL_PROJECTION);

	glPopMatrix();
	glMatrixMode(imatrix_mode);

	glPopAttrib();
	glViewport(ivp[0], ivp[1], ivp[2], ivp[3]);

}

void	report_info()
{
	if (show_stats)
	{
		int ix = 20;
		int iy = 20;

		draw_text(ix - 1, HEIGHT -iy - 1, 0, stats_string);
		draw_text(ix - 2, HEIGHT -iy - 2, 0, stats_string);
		draw_text(ix, HEIGHT -iy, 1, stats_string);
	}
	if (show_info)
	{
		int ix = text_offset[0];
		int iy = HEIGHT - text_offset[1];

		draw_text(WIDTH - ix - 1 - strlen(info_string) * 10, HEIGHT - iy - 1, 0, info_string);
		draw_text(WIDTH - ix - 2 - strlen(info_string) * 10, HEIGHT - iy - 2, 0, info_string);
		draw_text(WIDTH - ix - strlen(info_string) * 10, HEIGHT - iy, 1, info_string);

		show_info = (show_info > 200) ? 0 : show_info + 1;
	}
}

double	subtract_time(uint64_t ui_end_time, uint64_t ui_start_time)
{
	static double s_dconversion = 0.0;
	uint64_t ui_difference = ui_end_time - ui_start_time;
	if (0.0 ==s_dconversion)
	{
		mach_timebase_info_data_t k_timebase;
		kern_return_t k_error = mach_timebase_info(&k_timebase);
		if (k_error == 0)
			s_dconversion = 1e-9 * (double)k_timebase.numer / (double)k_timebase.denom;
	}
	return s_dconversion * (double)ui_difference;
}

void	report_stats(uint64_t ui_start_time, uint64_t ui_end_time)
{
	time_elapsed += subtract_time(ui_end_time, ui_start_time);

	if (time_elapsed && frame_count && frame_count > report_stats_interval)
	{
		double fms = (time_elapsed * 1000.0 / (double)frame_count);
		double ffps = 1.0 / (fms / 1000.0);

		sprintf(stats_string, "[%s] Compute: %3.2f ms Display: %3.2f fps (%s)\n",
				"GPU", fms, ffps, "Attached");

		glutSetWindowTitle(stats_string);

		frame_count = 0;
		time_elapsed = 0;
	}
}

void	display()
{
	frame_count++;
	uint64_t ui_start_time = mach_absolute_time();

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	if (animated)
	{
		update_mu(&mut, mua, mub);
		interpolate(muc, mut, mua, mub);

		update_color(&color_t, color_a, color_b);
		interpolate(color_c, color_t, color_a, color_b);
	}

	int err = recompute();
	if (err != 0)
		printf("Error %d from Recompute!\n", err);

	render_texture(host_image_buffer);
	report_info();

	glFinish(); /* for timing */

	uint64_t ui_end_time = mach_absolute_time();
	report_stats(ui_start_time, ui_end_time);
	draw_text(text_offset[0], text_offset[1], 1, (animated == 0) ? "Press space to animate" : " ");
	glutSwapBuffers();
}

int		init_cl()
{
	int err;
	err = setup_graphics();
	if (err != GL_NO_ERROR)
	{
		printf("Failed to setup openGL state");
		exit(err);
	}

	err = setup_compute_device();
	if (err != CL_SUCCESS)
		printf ("Failed to connect to compute device! Error %d\n", err);

	cl_bool image_support;
	err = clGetDeviceInfo(compute_device_id, CL_DEVICE_IMAGE_SUPPORT,
							sizeof(image_support), &image_support, NULL);
	if (err != CL_SUCCESS)
		printf("Unable to query device for image support");
	if (image_support == CL_FALSE)
		printf("Qjulia requires images: Images not supported on this device.");

	err = setup_compute_kernel();
	if (err != CL_SUCCESS)
		printf ("Failed to setup compute kernel! Error %d\n", err);

	err = create_compute_result();
	if (err != CL_SUCCESS)
		printf ("Failed to create compute result! Error %d\n", err);

	random_color(color_a);
	random_color(color_b);
	random_color(color_c);

	return CL_SUCCESS;
}

void	idle()
{
	glutPostRedisplay();
}

void	reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();

}

void	keyboard(unsigned char key, int x, int y)
{
	const float f_step_size = 0.05f;

	if (key == 27)
		exit(0);
	if (key == ' ')
	{
		animated = !animated;
		sprintf(info_string, "Animated = %s\n", animated ? "true" : "false");
		show_info = 1;
	}
}

void	cleanup()
{
	clFinish(compute_commands);
	clReleaseKernel(compute_kernel);
	clReleaseProgram(compute_program);
	clReleaseCommandQueue(compute_commands);
	clRetainMemObject(compute_result);
	clReleaseMemObject(compute_image);

	compute_commands = 0;
	compute_kernel = 0;
	compute_result = 0;
	compute_program = 0;
	compute_image = 0;
	compute_context = 0;
}

void	shutdown()
{
	printf("Shutting down...\n");
    cleanup();
    exit(0);
}

int		main(int argc, char **argv) /* is julia main */
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	if (init_cl() == GL_NO_ERROR)
	{
		glutDisplayFunc(display);
		glutIdleFunc(idle);
		glutReshapeFunc(reshape);
		glutKeyboardFunc(keyboard);

		atexit(shutdown);
		printf("Starting event loop...\n");

		glutMainLoop();
	}
	return (0);
}
