/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_options.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 21:34:36 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/12 23:55:28 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_OPTIONS_H
# define RT_OPTIONS_H

# ifndef __OPENCL_C_VERSION__
#  include "rt_types.h"
#  include "color.h"
#  include "sampler.h"
#  include "sampler_manager.h"
# endif

typedef enum	e_tracer_type
{
	ray_caster,
	direct_lightning,
	path_tracer
}				t_tracer_type;

typedef struct s_rt_options		t_rt_options;

/*
** TODO(dmelessa): move seed to this struct
** ambient_illumination: 0 - no, 1 - constant, 2 - occluder
** spp - samples per pixel
** aa_id - anti aliasing sampler id
*/

struct			s_rt_options
{
	t_sampler		sampler;
	cl_int			ambient_illumination; //4

	t_color			background_color;	//16

	cl_int			depth;			//4

	cl_int			shadows;	//4

	cl_int			area_lightning;//4

	cl_float		spp;	//4
	cl_int			aa_id;//4

	t_tracer_type	tracer_type;//4

	cl_uchar		reset; //1

	cl_uchar		strategy;//1
};

# ifndef __OPENCL_C_VERSION__

int				init_default_options(t_rt_options *options,
									t_sampler_manager *sampler_manager);

# endif

#endif
