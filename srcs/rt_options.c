/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_options.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 21:37:09 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/06 18:21:14 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_options.h"
#include "sampler_manager.h"

/*
** перенести в сэттер sampler manager
*/

int		init_default_options(t_rt_options *options,
						t_sampler_manager *sampler_manager)
{
	options->reset = 1;
	options->shadows = TRUE;
	options->ambient_illumination = 1;
	options->area_lightning = FALSE;
	set_color_float(&options->background_color, 0.0f, 0.0f, 0.0f);
	options->depth = 10;
	options->spp = NUM_SAMPLES;
	options->aa_id = new_sampler(sampler_manager, nrooks, 16384,
				DEFAULT_SAMPLES | DISK_SAMPLES | HEMISPHERE_SAMPLES);
	options->tracer_type = ray_caster;
	options->strategy = 1;
	return (SUCCESS);
}
