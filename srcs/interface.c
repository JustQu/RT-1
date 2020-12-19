/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 15:01:35 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/19 20:22:55 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"

void	init_interface(t_interface *interface, int mode, int enable_gui)
{
	interface->mode = mode;
	interface->enable_gui = enable_gui;
	interface->current_instance_id = 7;
	interface->current_light_id = 0;
}
