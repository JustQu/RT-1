/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_options.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 21:37:09 by dmelessa          #+#    #+#             */
/*   Updated: 2020/11/25 20:35:40 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_options.h"
#include "sampler_manager.h"

void	set_anti_aliasing(t_rt_options *options, int sampler_per_pixel)
{
	// options->aa
}

int		init_default_options(t_rt_options *options,
						 /* перенести в сэттер */
						 t_sampler_manager *sampler_manager)
{
	options->reset = 1;
	options->shadows = TRUE;
	options->ambient_illumination = 1;
	options->area_lightning = FALSE;
	set_color_float(&options->background_color, 0.0f, 0.0f, 0.0f);
	// set_color_uchar(&options->background_color, 0x05, 0x05, 0xAF);
	options->depth = 10;
	options->spp = NUM_SAMPLES;
	options->aa_id = new_sampler(sampler_manager, nrooks, 16384,
				DEFAULT_SAMPLES | DISK_SAMPLES | HEMISPHERE_SAMPLES);
	options->tracer_type = ray_caster;
	options->strategy = 1;
	return (SUCCESS);
}
