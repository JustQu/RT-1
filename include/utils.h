/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 18:37:14 by dmelessa          #+#    #+#             */
/*   Updated: 2020/10/30 23:23:29 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H
# define UTIL_H

# include "rt_types.h"

void	*ft_realloc(void *mem, size_t current_size, size_t new_size);

float	float_min(float a, float b);
float	float_max(float a, float b);

float	rand_float();
int int_max(int a, int b);

int int_min(int a, int b);

#endif
