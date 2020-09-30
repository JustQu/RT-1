/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 00:15:55 by dmelessa          #+#    #+#             */
/*   Updated: 2020/09/28 15:24:39 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# ifndef __OPENCL_C_VERSION__
#  include "rt_types.h"
#endif

cl_float4	norm4(cl_float4 vec);
cl_float4	cross_product(cl_float4 a, cl_float4 b);

#endif
