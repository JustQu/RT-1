/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 17:59:37 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/13 14:09:44 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_ERROR_H
# define RT_ERROR_H

# include "rt.h"
# define RED "\033[38;2;200;20;20m"
# define EOC "\033[0m"

typedef struct s_code_msg	t_code_msg;
typedef enum e_error_code	t_error_code;
typedef enum e_error_type	t_error_type;

enum	e_error_code
{
	undefinded_error = -1,

	system_malloc_error = -2,
	system_open_file_error = -3,

	cl_get_platform_id_error = -4,
	cl_get_device_id_error = -5,
	cl_create_context_error = -6,
	cl_create_command_queue_error = -7,
	cl_kernel_arg_error = -8,
	cl_kernel_start_error = -9,
	cl_read_buffer_error = -10,
	cl_create_program_error = -11,
	cl_build_program_error = -12,
	cl_create_kernel_error = -13,
	cl_create_buffer_error = -14,

	app_no_scene_file = -15,
	app_unknown_object_type = -16,

	sdl_init_error = -17,
	sdl_create_window_error = -18,
	sdl_create_texture_error = -19
};

enum	e_error_type
{
	system_err,
	opencl_err,
	sdl_err,
	app_err
};

struct s_code_msg
{
	t_s32			err_type; //system, sdl, ocl
	t_error_code	err_code;
	char			*msg;
};

void		rt_error(char *message);

void		rt_warning(char *message);

const char	*get_error_string(int error_code);

/*
** @brief  print error message and exit program.
** we are letting OS free all the memory in case of error
**
** @param error_type type error: system, OpenCL, SDL
** @param error_code error code inside our app
** @param error_type_code code error for additional info of different error types
** 			if not error occures must be 0 or erroc_code
** @param additional_message what message to print after error
** @return ** void
*/

void		rt_is_dead(t_error_type error_type,
						t_error_code error_code,
						t_s32 error_type_code,
						char *additional_message);

void		rt_die(t_error_type error_type,
					t_error_code error_code,
					t_s32 error_type_code,
					char *additional_message);

#endif