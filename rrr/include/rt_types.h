/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_types.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 17:57:17 by dmelessa          #+#    #+#             */
/*   Updated: 2020/09/26 21:44:24 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_TYPES_H
# define RT_TYPES_H

# define OPEN_CL __OPENCL_C_VERSION__

/**
** @brief Host code
**
*/
# ifndef __OPENCL_C_VERSION__
#  include "inttypes.h"
#  include "bool.h"
#  ifdef __APPLE__
#   include "OpenCL/opencl.h"
#  else
#   include "CL/cl.h"
#  endif

typedef uint32_t	t_uint;
typedef int32_t		t_int;

# endif

# define SUCCESS	0
# define ERROR	-1

# ifndef M_PI
#  define M_PI 3.14159265358979323846264338327950288
# endif

# ifdef __OPENCL_C_VERSION__
#  define cl_float16 float16
#  define cl_float4 float4
#  define cl_float3 float3
#  define cl_float float
#  define cl_int4 int4
#  define cl_int3 int3
#  define cl_int int
#  define cl_char char
#  define cl_uchar uchar
#  define cl_bool bool
#  define cl_uint unsigned int
# endif

#endif
