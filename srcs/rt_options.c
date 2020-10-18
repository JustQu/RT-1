/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_options.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 21:37:09 by dmelessa          #+#    #+#             */
/*   Updated: 2020/10/18 18:29:27 by user             ###   ########.fr       */
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
	options->shadows = TRUE;
	options->ambient_occlusion = FALSE;
	options->area_lightning = FALSE;
	set_color_uchar(&options->background_color, 0x05, 0x05, 0xAF);
	options->depth = 1;
	options->aa_id = new_sampler(sampler_manager, regular_grid, NUM_SAMPLES, NUM_SETS);
	return (SUCCESS);
}
