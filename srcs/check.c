/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 23:23:46 by maximka           #+#    #+#             */
/*   Updated: 2020/06/29 17:03:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		check_three(char **elem)
{
	int	i;

	i = 1;
	if (check_len(elem) != 12)
		return (0);
	if (!check_valid_letters(elem))
		return (0);
	while (elem[i])
	{
		if ((i >= 5 && i <= 7) && (ft_strlen(elem[i]) > 3
			|| elem[i][0] == '-'))
			return (0);
		if ((i < 4 || i > 6) && ft_strlen(elem[i]) > 10)
			return (0);
		i++;
	}
	return (1);
}

int		check_zero(char **elem)
{
	int	i;

	i = 1;
	if (check_len(elem) != 12)
		return (0);
	if (!check_valid_letters(elem))
		return (0);
	while (elem[i])
	{
		if ((i >= 4 && i <= 6) && (ft_strlen(elem[i]) > 3
			|| elem[i][0] == '-'))
			return (0);
		if ((i < 4 || i > 6) && ft_strlen(elem[i]) > 10)
			return (0);
		i++;
	}
	return (1);
}

int		check_two(char **elem)
{
	int i;

	i = 1;
	if (check_len(elem) != 14)
		return (0);
	if (!check_valid_letters(elem))
		return (0);
	while (elem[i])
	{
		if ((i >= 4 && i <= 6) && (ft_strlen(elem[i]) > 3
			|| elem[i][0] == '-'))
			return (0);
		if ((i < 4 || i > 6) && ft_strlen(elem[i]) > 10)
			return (0);
		i++;
	}
	return (1);
}

int		check_c(char **elem)
{
	int	i;

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

int		check_one(char **elem)
{
	int	i;

	i = 1;
	if (check_len(elem) != 13)
		return (0);
	if (!check_valid_letters(elem))
		return (0);
	while (elem[i])
	{
		if ((i >= 4 && i <= 6) && (ft_strlen(elem[i]) > 3
			|| elem[i][0] == '-'))
			return (0);
		if ((i < 4 || i > 6) && ft_strlen(elem[i]) > 10)
			return (0);
		i++;
	}
	return (1);
}
