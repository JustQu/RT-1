/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 22:52:37 by dmelessa          #+#    #+#             */
/*   Updated: 2020/10/16 20:00:46 by aapricot         ###   ########.fr       */
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

// t_texture	create_checker_texture(t_texture_manager *texture_manager,
// 									t_color color1, t_color color2)
// {
// 	//TODO
// }

// t_texture	create_perlin_texture(t_texture_manager *texture_manager)
// {
// 	//TODO
// }

// t_texture	create_img_texture(t_texture_manager *texture, int mode, void *data)
// {
// 	//TODO
// }
