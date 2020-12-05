/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 22:52:37 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/04 21:54:00 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "texture_manager.h"

t_texture	create_solid_texture(t_color color)
{
	t_texture	tex;

	tex.type = solid;
	tex.data.solid.color = color;
	return (tex);
}
