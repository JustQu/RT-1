/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tex_cam_types.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 21:35:46 by aapricot          #+#    #+#             */
/*   Updated: 2020/12/10 16:22:49 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "offset.h"
#include "parser.h"
#include "camera.h"

int					get_tex_type_value(char *str)
{
	if (str == NULL)
		rt_error("get_tex_type_value(): given NULL pointer");
	if (!ft_strcmp(str, "solid"))
		return (solid);
	else if (!ft_strcmp(str, "checker"))
		return (checker);
	else if (!ft_strcmp(str, "checker2d"))
		return (checker2d);
	else if (!ft_strcmp(str, "transparent_checker"))
		return (transparent_checker);
	else if (!ft_strcmp(str, "reflective_checker"))
		return (reflective_checker);
	else if (!ft_strcmp(str, "perlin"))
		return (perlin);
	else if (!ft_strcmp(str, "smooth_perlin"))
		return (smooth_perlin);
	else if (!ft_strcmp(str, "turbulence_perlin"))
		return (turbulence_perlin);
	else if (!ft_strcmp(str, "wave_perlin"))
		return (wave_perlin);
	else if (!ft_strcmp(str, "image"))
		return (image);
	return (-1);
}

int					get_cam_type_value(char *str)
{
	if (str == NULL)
		rt_error("get_cam_type_value(): given NULL pointer");
	if (!ft_strcmp(str, "orthographic"))
		return (orthographic);
	else if (!ft_strcmp(str, "perspective"))
		return (perspective);
	else if (!ft_strcmp(str, "thin_lens"))
		return (thin_lens);
	else if (!ft_strcmp(str, "fisheye"))
		return (fisheye);
	else if (!ft_strcmp(str, "spherical"))
		return (spherical);
	else if (!ft_strcmp(str, "stereo"))
		return (stereo);
	return (-1);
}

void				get_tex_type(char *str, int offset, void *data)
{
	unsigned char	*v;
	t_texture_type	*type;

	if (str == NULL || data == NULL)
		rt_error("get_tex_type(): given NULL pointer");
	v = (unsigned char *)data + offset;
	type = (t_texture_type *)v;
	*type = get_tex_type_value(str);
}

void				get_cam_type(char *str, int offset, void *data)
{
	unsigned char	*v;
	t_camera_type	*type;

	if (str == NULL || data == NULL)
		rt_error("get_cam_type(): given NULL pointer");
	v = (unsigned char *)data + offset;
	type = (t_camera_type *)v;
	*type = get_cam_type_value(str);
}
