/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_options.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 21:34:36 by dmelessa          #+#    #+#             */
/*   Updated: 2020/11/05 14:15:39 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_OPTION_H
# define RT_OPTION_H

# ifndef __OPENCL_C_VERSION__
#  include "rt_types.h"
#  include "color.h"
#  include "sampler.h"
# endif

# define DEFAULT_WIDTH 1280
# define DEFAULT_HEIGHT 720

typedef struct s_rt_options		t_rt_options;

/*
** TODO(dmelessa): move seed to this struct
*/
struct				s_rt_options
{
	t_sampler		ambient_occluder_sampler;
	cl_int			ambient_occlusion;

	t_color			background_color;

	cl_int			depth;

	cl_int			shadows;

	cl_int			area_lightning;

	cl_float		spp; //samples per pixel
	cl_int			aa_id; //anti-aliasing sampler id

	cl_uchar		reset;

	int				current_id; // id instans_info
};

# ifndef __OPENCL_C_VERSION__

#  include "sampler_manager.h"

int	init_default_options(t_rt_options *options,
					t_sampler_manager *sampler_manager);

# endif

#endif
