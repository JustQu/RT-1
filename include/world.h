/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 19:36:22 by dmelessa          #+#    #+#             */
/*   Updated: 2020/08/08 14:04:05 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H

# include "types.h"
# include "camera.h"
# include "objects.h"
# include "material.h"
# include "light.h"
# include "sampler.h"
# include "color.h"
# include "instance.h"

# define DEFAULT_WIDTH 1200
# define DEFAULT_HEIGHT 600
# define WORK_GROUP_SIZE 64

typedef struct s_render_options		t_render_options;

# ifdef _WIN64
__declspec(align(4))
# endif
struct				s_render_options
{
	t_sampler		ambient_occluder_sampler;
	cl_int			ambient_occlusion;

	t_color			background_color;

	cl_int			depth;

	cl_int			shadows;

	cl_int			area_lightning;

	cl_int			sampler_id; //anti-aliasing sampler
};

#endif
