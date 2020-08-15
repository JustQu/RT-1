/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 17:57:17 by dmelessa          #+#    #+#             */
/*   Updated: 2020/08/14 00:22:08 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

#define OPEN_CL __OPENCL_C_VERSION__

/**
** @brief Host code
**
*/
# ifndef __OPENCL_C_VERSION__
#  include "inttypes.h"
#  include "bool.h"
#  ifdef __APPLE__
#   include "OpenCL/opencl.h"
#else
#   include "CL/cl.h"
#  endif
# endif

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
