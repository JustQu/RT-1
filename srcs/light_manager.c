/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 23:40:30 by dmelessa          #+#    #+#             */
/*   Updated: 2020/10/20 23:41:50 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "light_manager.h"

void	init_light_manager(t_light_manager *light_manager)
{
	light_manager->lights = NULL;
	light_manager->nlights = 0;
	light_manager->light_malloc_size = 0;
}
