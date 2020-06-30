/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximka <maximka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 14:56:18 by maximka           #+#    #+#             */
/*   Updated: 2020/06/29 15:11:48 by maximka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			average_light(t_light *light)
{
	float		sum;
	t_light		*begin;

	begin = light;
	sum = 0;
	while (light)
	{
		sum += light->intensity;
		light = light->next;
	}
	if (sum < 1)
		return ;
	while (begin)
	{
		begin->intensity /= sum;
		begin = begin->next;
	}
}

int				check_valid_letters(char **elem)
{
	int			j;
	int			i;

	i = 1;
	while (elem[i])
	{
		j = 0;
		while (elem[i][j])
		{
			if ((elem[i][j] < '0' || elem[i][j] > '9') &&
							(elem[i][j] != '.' && elem[i][j] != '-'))
				return (0);
			++j;
		}
		++i;
	}
	return (1);
}

int				check_len(char **elem)
{
	int			i;

	i = 0;
	while (elem[i])
		++i;
	return (i);
}

int				check_p(char **elem)
{
	int			i;

	i = 1;
	if (check_len(elem) != 5)
		return (0);
	if (!check_valid_letters(elem))
		return (0);
	while (elem[i])
	{
		if (ft_strlen(elem[i]) > 10)
			return (0);
		i++;
	}
	return (1);
}

int				check_d(char **elem)
{
	int			i;

	i = 1;
	if (check_len(elem) != 4)
		return (0);
	if (!check_valid_letters(elem))
		return (0);
	while (elem[i])
	{
		if (ft_strlen(elem[i]) > 10)
			return (0);
		i++;
	}
	return (1);
}
