/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximka <maximka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 17:08:46 by maximka           #+#    #+#             */
/*   Updated: 2020/06/29 17:21:47 by maximka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int				check_elem(char ***elem, char *line)
{
	int			res;

	res = 0;
	if (!(*elem = ft_strsplit_2(line, " ,\t")))
		return (-1);
	res += ***elem == '0' ? check_zero(*elem) : 0;
	res += ***elem == '1' ? check_one(*elem) : 0;
	res += ***elem == '2' ? check_two(*elem) : 0;
	res += ***elem == '3' ? check_three(*elem) : 0;
	res += ***elem == 'p' ? check_p(*elem) : 0;
	res += ***elem == 'c' ? check_c(*elem) : 0;
	res += ***elem == 'D' ? check_d(*elem) : 0;
	if (res)
		return (1);
	return (-1);
}

t_shape			*list_of_shapes(t_rtv1 rtv1, int fd)
{
	t_pshape	shape;
	char		*line;
	char		**elem;

	shape.start = NULL;
	line = NULL;
	elem = NULL;
	while (get_next_line(fd, &line) && *line != '@')
	{
		if ((check_elem(&elem, line)) == -1)
			incorrect_scene(rtv1, &line, &elem);
		if (**elem == '0')
			shape = ft_psphere(shape, elem);
		if (**elem == '1')
			shape = ft_pcilin(shape, elem);
		if (**elem == '2')
			shape = ft_pcone(shape, elem);
		if (**elem == '3')
			shape = ft_pplane(shape, elem);
		free_elem_line(&line, &elem);
	}
	line ? free(line) : NULL;
	return (shape.start);
}

t_light			*list_of_light(t_rtv1 rtv1, int fd)
{
	t_plight	light;
	char		*line;
	char		**elem;

	light.start = NULL;
	while (get_next_line(fd, &line) && *line != '@')
	{
		if ((check_elem(&elem, line)) == -1)
			incorrect_scene(rtv1, &line, &elem);
		if (*line == 'p')
			light = ft_plight(light, elem);
		free(line);
		free_elem(elem);
	}
	line ? free(line) : NULL;
	return (light.start);
}

t_vector		*define_camera(t_rtv1 rtv1, int fd)
{
	t_vector	*cam;
	char		*line;
	char		**elem;

	elem = NULL;
	get_next_line(fd, &line);
	if ((check_elem(&elem, line)) == -1)
		incorrect_scene(rtv1, &line, &elem);
	cam = (t_vector*)malloc(sizeof(t_vector));
	cam->x = ft_atoi_for_float(elem[1]);
	cam->y = ft_atoi_for_float(elem[2]);
	cam->z = ft_atoi_for_float(elem[3]);
	elem ? free_elem(elem) : NULL;
	line ? free(line) : NULL;
	get_next_line(fd, &line);
	line ? free(line) : NULL;
	return (cam);
}

t_vector		*define_dir(t_rtv1 rtv1, int fd)
{
	t_vector	*dir;
	char		*line;
	char		**elem;

	get_next_line(fd, &line);
	if ((check_elem(&elem, line)) == -1)
		incorrect_scene(rtv1, &line, &elem);
	dir = (t_vector*)malloc(sizeof(t_vector));
	dir->x = ft_atoi_for_float(elem[1]);
	dir->y = ft_atoi_for_float(elem[2]);
	dir->z = ft_atoi_for_float(elem[3]);
	free(line);
	free_elem(elem);
	return (dir);
}
