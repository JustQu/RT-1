/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 22:52:37 by dmelessa          #+#    #+#             */
/*   Updated: 2020/10/30 13:00:14 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "texture_manager.h"

t_texture	create_solid_texture(t_color color)
{
	t_texture	tex;

	tex.type = solid;
	tex.data.solid.color = color;
	return tex;
}
