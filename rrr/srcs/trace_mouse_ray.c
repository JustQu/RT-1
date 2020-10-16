/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_mouse_ray.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 14:20:20 by dmelessa          #+#    #+#             */
/*   Updated: 2020/09/28 14:23:21 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app.h"

void		trace_mouse_ray(t_rt *rt, t_gui *gui, float x, float y)
{
	gui->current_object = rt->scene.instance_mngr.instances_info;
}
