/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_second_values.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 20:09:10 by aapricot          #+#    #+#             */
/*   Updated: 2020/12/10 16:21:51 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "offset.h"
#include "parser.h"
#include "rt_err.h"

void		get_uchar(char *str, int offset, void *data)
{
	unsigned char	*v;
	cl_uchar		*c;

	if (str == NULL || data == NULL)
		rt_error("get_uchar(): given NULL pointer");
	v = (unsigned char *)data + offset;
	c = (cl_uchar *)v;
	if (!ft_strcmp(str, "true"))
		*c = 1;
	else if (!ft_strcmp(str, "false"))
		*c = 0;
}

void		get_int(char *str, int offset, void *data)
{
	unsigned char	*v;
	cl_int			*num;

	if (str == NULL || data == NULL)
		rt_error("get_int(): given NULL pointer");
	v = (unsigned char *)data + offset;
	num = (cl_int *)v;
	*num = ft_atoi(str);
}

void		free_tab(char **tab)
{
	int		n;

	n = 0;
	if (tab == NULL)
		rt_error("free_tab(): given NULL pointer");
	while (NULL != tab[n])
	{
		free(tab[n]);
		tab[n] = NULL;
		n += 1;
	}
	free(tab);
}

int			len_word(char *str)
{
	int len;
	int	i;

	if (str == NULL)
		rt_error("len_word(): given NULL pointer");
	i = 0;
	len = 0;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]))
			len++;
		i++;
	}
	return (len);
}

int			char_count(char *str)
{
	int		i;
	int		count;

	if (str == NULL)
		rt_error("char_count(): given NULL pointer");
	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '#')
		{
			i++;
			while (str[i] != '\0' && str[i] != '#')
				i++;
		}
		if (str[i] != '\t' && str[i] != ' ' && str[i] != '\n' &&
			str[i] != '#' && str[i] != '\0')
			count++;
		if (str[i] != '\0')
			i++;
	}
	return (count);
}
