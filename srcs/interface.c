/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 15:01:35 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/13 15:28:02 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"

void	init_interface(t_interface *interface, int mode, int enable_gui)
{
	interface->mode = mode;
	interface->enable_gui = enable_gui;
	interface->current_instance_id = 0;
	interface->current_light_id = 0;
}
