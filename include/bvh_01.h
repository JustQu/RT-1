/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_01.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 10:37:46 by jvoor             #+#    #+#             */
/*   Updated: 2020/12/14 10:37:47 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_LEGACY_BVH_01_H
# define RT_LEGACY_BVH_01_H

# include "bvh.h"

int		cmp_x(t_bvh_node a, t_bvh_node b);
int		cmp_y(t_bvh_node a, t_bvh_node b);
int		cmp_z(t_bvh_node a, t_bvh_node b);

#endif
