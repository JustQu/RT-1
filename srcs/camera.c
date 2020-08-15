/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 01:05:19 by dmelessa          #+#    #+#             */
/*   Updated: 2020/08/13 01:05:20 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "vector.h"

//todo: check
void	compute_uvw(t_camera *camera)
{
	camera->w.x = -camera->direction.x;
	camera->w.y = -camera->direction.y;
	camera->w.z = -camera->direction.z;
	camera->w.w = 0.0f;
	camera->w = norm4(camera->w);
	camera->u = cross_product(camera->up, camera->w);
	camera->u.x = -camera->u.x; //doing this because we are using left handed coordinate system
	camera->u.y = -camera->u.y;
	camera->u.z = -camera->u.z;
	camera->v = cross_product(camera->w, camera->u);
	camera->v.x = -camera->v.x;
	camera->v.y = -camera->v.y;
	camera->v.z = -camera->v.z;
}

/**
** @todo
** @brief
**
** @param camera
** @param axis 0 - x, 1 - y, 2 - z
** @param angle_degrees
** @return ** void
*/
void	rotate_camera(t_camera *camera, int axis, float angle_degrees)
{
	//rotate u, v, w
}
