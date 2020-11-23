/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 15:51:27 by aapricot          #+#    #+#             */
/*   Updated: 2020/11/23 17:48:42 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "logs.h"

int			get_log_fd(char *str)
{
	int		fd;
	char	*line_1;
	char	*line_2;

	line_1 = ft_strjoin("logs/", str);
	line_2 = ft_strjoin(line_1, ".log");
	if ((fd = open(line_2, O_WRONLY | O_CREAT | O_TRUNC, 0666)) < 0)
	{
		free(line_1);
		free(line_2);
		close(fd);
		return (-1);
	}
	free(line_1);
	free(line_2);
	return (fd);
}

void		write_logs(int num_log, int fd, char *str)
{
	if (num_log == PARS_SUCCESS)
	{
		ft_putendl_fd("SUCCESS:", fd);
		ft_putendl_fd("Render this object", fd);
	}
	else if (num_log == PARS_UNSUCCESS)
	{
		ft_putendl_fd("UNSUCCESS:", fd);
		ft_putendl_fd("Skip this object", fd);
	}
	else if (num_log == WRITE_BLOCK)
	{
		ft_putstr_fd("Block:\n", fd);
		ft_putendl_fd(str, fd);
		ft_putchar_fd('\n', fd);
	}
	else if (num_log == UNKNOWN_SCENE_TYPE)
	{
		ft_putstr_fd("Unknown scene type\n", fd);
		ft_putendl_fd(str, fd);
		ft_putchar_fd('\n', fd);
	}
	else if (num_log == SCENE_TYPE_DOES_NOT_EXIST)
	{
		ft_putstr_fd("Scene type does not exist:\n", fd);
		ft_putendl_fd(str, fd);
		// ft_putchar_fd('\n', fd);
	}
	else if (num_log == UNKNOWN_OBJ_TYPE)
	{
		ft_putstr_fd("Unknown object type:\n", fd);
		ft_putendl_fd(str, fd);
		// ft_putchar_fd('\n', fd);
	}
	else if (num_log == UNKNOWN_MATERIAL_TYPE)
	{
		ft_putstr_fd("Unknown material type:\n", fd);
		ft_putendl_fd(str, fd);
		ft_putchar_fd('\n', fd);
	}
	else if (num_log == UNKNOWN_TEXTURE_TYPE)
	{
		ft_putstr_fd("Unknown texure type:\n", fd);
		ft_putendl_fd(str, fd);
		ft_putchar_fd('\n', fd);
	}
	else if (num_log == OBJ_TYPE_DOES_NOT_EXIST)
	{
		ft_putendl_fd(str, fd);
		ft_putstr_fd("Object type does not exist\n", fd);
		// ft_putchar_fd('\n', fd);
	}
	else if (num_log == MATERIAL_TYPE_DOES_NOT_EXIST)
	{
		ft_putendl_fd(str, fd);
		ft_putstr_fd("Material type does not exist\n", fd);
		// ft_putchar_fd('\n', fd);
	}
	else if (num_log == TEXTURE_TYPE_DOES_NOT_EXIST)
	{
		ft_putendl_fd(str, fd);
		ft_putstr_fd("Texture type does not exist\n", fd);
		// ft_putchar_fd('\n', fd);
	}
	else if (num_log == COMMENT)
	{
		ft_putstr_fd("Comment:\n", fd);
		ft_putendl_fd(str, fd);
		ft_putchar_fd('\n', fd);
	}
	else if (num_log == BAD_BRACKETS)
	{
		ft_putstr_fd("Bad brackets in block:\n", fd);
		ft_putendl_fd(str, fd);
		ft_putchar_fd('\n', fd);
	}
	else if (num_log == COLOR_DOES_NOT_EXIST)
	{
		ft_putstr_fd("Color does not exist:\n", fd);
		ft_putendl_fd(str, fd);
		ft_putchar_fd('\n', fd);
	}
	else if (num_log == BAD_ORIGIN)
	{
		ft_putendl_fd(str, fd);
		ft_putstr_fd("Has no origin. Using default param\n", fd);
	}
	else if (num_log == BAD_DIRECTION)
	{
		ft_putendl_fd(str, fd);
		ft_putstr_fd("Has no direction. Using default param\n", fd);
	}
}