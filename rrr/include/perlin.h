/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 13:19:10 by dmelessa          #+#    #+#             */
/*   Updated: 2020/10/06 21:14:06 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PERLIN_H
# define PERLIN_H

# include "rt_types.h"

# define PERLIN_SIZE 256

// extern float	ranfloat[PERLIN_SIZE];
// extern int		perm_x[PERLIN_SIZE];
// extern int		perm_y[PERLIN_SIZE];
// extern int		perm_z[PERLIN_SIZE];

// float	pelin_noise(cl_float3 p);
cl_float3	*perlin_generate();
void		permute(int *p, int n);
int			*perlin_generate_perm();

// typedef struct	s_perlin
// {
// 	cl_float	ranfloat[PERLIN_SIZE];
// 	cl_int		perm_x[PERLIN_SIZE];
// 	cl_int		perm_y[PERLIN_SIZE];
// 	cl_int		perm_z[PERLIN_SIZE];
// }				t_perlin;

# endif
