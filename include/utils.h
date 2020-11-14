/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 18:37:14 by dmelessa          #+#    #+#             */
/*   Updated: 2020/11/14 20:18:21 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H
# define UTIL_H

# ifndef __OPENCL_C_VERSION__
#  include "rt_types.h"
#endif

void	*ft_realloc(void *mem, size_t current_size, size_t new_size);

float	float_min(float a, float b);
float	float_max(float a, float b);

float	rand_float();
int int_max(int a, int b);

int int_min(int a, int b);

#endif
