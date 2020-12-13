/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 15:51:27 by aapricot          #+#    #+#             */
/*   Updated: 2020/12/11 20:06:49 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "logs.h"
#include "safe_call.h"

int			get_log_fd(char *str)
{
	int		fd;
	char	*line_1;
	char	*line_2;

	if (str == NULL)
		rt_error("get_log_fd(): given NULL pointer");
	safe_call_ptr((line_1 = ft_strjoin("logs/", str)), "malloc error");
	safe_call_ptr((line_2 = ft_strjoin(line_1, ".log")), "malloc error");
	if ((fd = open(line_2, O_WRONLY | O_CREAT | O_TRUNC, 0666)) < 0)
	{
		free(line_1);
		free(line_2);
		close(fd);
		rt_error("get_log_fd(): logs directory was not found");
	}
	free(line_1);
	free(line_2);
	return (fd);
}

void		write_logs_4(int num_log, int fd, char *str)
{
	if (num_log == SCENE_TYPE_DOES_NOT_EXIST)
	{
		ft_putstr_fd("Scene type does not exist:\n", fd);
		ft_putendl_fd(str, fd);
	}
	else if (num_log == COLOR_DOES_NOT_EXIST)
	{
		ft_putendl_fd(str, fd);
		ft_putendl_fd("Color does not exist:", fd);
	}
	else if (num_log == BAD_ORIGIN)
	{
		ft_putendl_fd(str, fd);
		ft_putendl_fd("Has no origin. Using default param", fd);
	}
	else if (num_log == BAD_ROTATION)
	{
		ft_putendl_fd(str, fd);
		ft_putendl_fd("Has no rotation. Using default param", fd);
	}
	write_logs_5(num_log, fd, str);
}

void		write_logs_3(int num_log, int fd, char *str)
{
	if (num_log == MATERIAL_TYPE_DOES_NOT_EXIST)
	{
		ft_putendl_fd(str, fd);
		ft_putendl_fd("Material type does not exist", fd);
	}
	else if (num_log == TEXTURE_TYPE_DOES_NOT_EXIST)
	{
		ft_putendl_fd(str, fd);
		ft_putendl_fd("Texture type does not exist", fd);
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
	write_logs_4(num_log, fd, str);
}

void		write_logs_2(int num_log, int fd, char *str)
{
	if (num_log == UNKNOWN_OBJ_TYPE)
	{
		ft_putstr_fd("Unknown object type:\n", fd);
		ft_putendl_fd(str, fd);
	}
	else if (num_log == UNKNOWN_MATERIAL_TYPE)
	{
		ft_putstr_fd("Unknown material type:\n", fd);
		ft_putendl_fd(str, fd);
	}
	else if (num_log == UNKNOWN_TEXTURE_TYPE)
	{
		ft_putstr_fd("Unknown texure type:\n", fd);
		ft_putendl_fd(str, fd);
	}
	else if (num_log == OBJ_TYPE_DOES_NOT_EXIST)
	{
		ft_putendl_fd(str, fd);
		ft_putendl_fd("Object type does not exist", fd);
	}
	write_logs_3(num_log, fd, str);
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
	}
	write_logs_2(num_log, fd, str);
}
