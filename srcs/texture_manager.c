/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 15:34:21 by dmelessa          #+#    #+#             */
/*   Updated: 2020/10/04 19:13:26 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture_manager.h"
#include "libft.h"
#include "utils.h"

#include <assert.h>

int		init_texture_manager(t_texture_manager *texture_manager)
{
	int	a;

	a = 100;
	texture_manager->textures = malloc(sizeof(t_texture) * a);
	texture_manager->imgs_data = NULL;
	texture_manager->textures_malloc_size = sizeof(t_texture) * a;
	texture_manager->imgs_data_malloc_size = 0;
	texture_manager->nimgs = 0;
	texture_manager->ntextures = 0;
	texture_manager->current_offset = 0;
	assert(texture_manager->textures);
	return (SUCCESS);
}

int		add_texture(t_texture_manager *texture_manager,
					t_texture texture)
{
	if ((1 + texture_manager->ntextures) * sizeof(t_texture)
		> texture_manager->textures_malloc_size)
	{
		texture_manager->textures = ft_realloc(texture_manager,
										texture_manager->textures_malloc_size,
										texture_manager->textures_malloc_size * 2);
		texture_manager->textures_malloc_size *= 2;
	}
	//TODO(dmelessa): realloc_imgs_data
	texture_manager->textures[texture_manager->ntextures++] = texture;
	return (texture_manager->ntextures - 1);
}
