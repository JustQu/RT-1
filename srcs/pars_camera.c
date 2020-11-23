/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 18:52:00 by aapricot          #+#    #+#             */
/*   Updated: 2020/11/23 21:35:01 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "offset.h"
#include "scene.h"

t_selector		g_selector_cam[] = { {"type", offsetof(t_camera, type), get_cam_type},
									{"d", offsetof(t_camera, d), get_float},
									{"direction", offsetof(t_camera, direction), get_vector},
									{"f", offsetof(t_camera, f), get_float},
									{"l", offsetof(t_camera, l), get_float},
									{"origin", offsetof(t_camera, origin), get_vector},
									{"zoom", offsetof(t_camera, zoom), get_float} };

int				g_cam_selector_size = sizeof(g_selector_cam) / sizeof(t_selector);

void			add_parsed_camera(t_camera *camera)
{
	// scene->camera = *camera;
	printf("type = %d\n", camera->type);
	printf("origin.x = %f\n", camera->origin.x);
	printf("origin.x = %f\n", camera->origin.y);
	printf("origin.x = %f\n", camera->origin.z);
	printf("direction.x = %f\n", camera->direction.x);
	printf("direction.y = %f\n", camera->direction.y);
	printf("direction.z = %f\n", camera->direction.z);
}

// void			fill_camera(char *a, char *b, t_camera *cam)
// {
// 	int			i;

// 	i = 0;
// 	while (i < g_cam_selector_size)
// 	{
// 		if (!ft_strcmp(g_selector_cam[i].name, a))
// 		{
// 			g_selector_cam[i].func(b, g_selector_cam[i].offset, cam);
// 			break ;
// 		}
// 		// printf("key = %s\ncheck = %s\n\n", a, g_selector_cam[i].name);
// 		i++;
// 	}
// }

void		pars_camera(char *str, t_camera *camera)
{
	char			*a;
	char			*b;
	int				i;

	i = 0;
	*camera = get_default_camera();
	while (*str != '{' && *str != '\0')
		str++;
	str++;
	while (*str != '\0')
	{
		a = get_key(&str);
		b = get_value(&str);
		while (*str == ';' || *str == '}')
			str++;
		while (i < g_cam_selector_size)
		{
			if (!ft_strcmp(g_selector_cam[i].name, a))
			{
				g_selector_cam[i].func(b, g_selector_cam[i].offset, camera);	//can changed with fill_camera
				break ;
			}
			i++;
		}
		// fill_camera(a, b, &camera);
		i = 0;
		free(a);
		free(b);
	}
	add_parsed_camera(camera);
}