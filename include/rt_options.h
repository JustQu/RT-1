/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_options.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 21:34:36 by dmelessa          #+#    #+#             */
/*   Updated: 2020/11/20 22:16:16 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_OPTION_H
# define RT_OPTION_H

# ifndef __OPENCL_C_VERSION__
#  include "rt_types.h"
#  include "color.h"
#  include "sampler.h"
# endif

# define DEFAULT_WIDTH 800
# define DEFAULT_HEIGHT 640

# define IMG_WIDTH 800
# define IMG_HEIGHT 640

typedef enum	e_tracer_type
{
	ray_caster,
	direct_lightning,
	path_tracer
}				t_tracer_type;

typedef struct s_rt_options		t_rt_options;

/*
** TODO(dmelessa): move seed to this struct
*/
struct				s_rt_options
{
	t_sampler		sampler;
	cl_int			ambient_illumination; //0 - no, 1 - constant, 2 - occluder

	t_color			background_color;

	cl_int			depth;

	cl_int			shadows;

	cl_int			area_lightning;

	cl_float		spp; //samples per pixel
	cl_int			aa_id; //anti-aliasing sampler id

	t_tracer_type	tracer_type;

	cl_uchar		reset;

	cl_uchar		strategy;
};

# ifndef __OPENCL_C_VERSION__

#  include "sampler_manager.h"

int	init_default_options(t_rt_options *options,
					t_sampler_manager *sampler_manager);

# endif

#endif
