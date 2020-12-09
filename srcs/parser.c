/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 19:56:06 by aapricot          #+#    #+#             */
/*   Updated: 2020/12/08 17:46:39 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "offset.h"
#include "logs.h"
#include "resource_manager.h"
#include "scene.h"

char		*delete_tabs(char *str)
{
	char	*res;
	int		i;
	int		j;

	if (str == NULL)
		rt_error("delete_tabs(): given NULL pointer");
	j = -1;
	i = 0;
	safe_call_ptr((res = (char *)malloc(sizeof(char) * (char_count(str) + 1))),
			"delete_tabs(): malloc error");
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
			res[++j] = str[i];
		if (str[i] != '\0')
			i++;
	}
	res[++j] = '\0';
	free(str);
	return (res);
}

char		*get_read_block(int fd)
{
	char	*current_line;
	char	*block_line;
	char	*tmp;
	int		i;

	if (fd < 0)
		rt_error("get_read_block(): wrong fd");
	block_line = NULL;
	while ((i = get_next_line(fd, &current_line)) == 1)
	{
		if (!ft_strcmp(current_line, "\0") && block_line != NULL)
		{
			free(current_line);
			break ;
		}
		if (block_line == NULL)
			safe_call_ptr((block_line = ft_strdup(current_line)),
			"malloc error");
		else
		{
			tmp = block_line;
			safe_call_ptr((block_line = ft_strjoin(tmp, current_line)),
			"malloc error");
			free(tmp);
		}
		free(current_line);
	}
	return (block_line);
}

void		pars_router(t_res_mngr *resource_manager, t_parsed_info *asset,
						char *block, int log)
{
	int		block_type;

	if (resource_manager == NULL || asset == NULL || block == NULL)
		rt_error("pars_router(): given NULL pointer");
	block_type = get_block_type(block);
	if (block_type == object)
		pars_object(resource_manager, asset, block, log);
	else if (block_type == light)
		pars_light(block, asset, resource_manager);
	else if (block_type == camera)
		pars_camera(block, &resource_manager->scene->camera, log);
	else if (block_type == options)
		pars_options(block, resource_manager);
	else if (block_type == 0)
		write_logs(UNKNOWN_SCENE_TYPE, log, block);
	else if (block_type == -1)
		write_logs(SCENE_TYPE_DOES_NOT_EXIST, log, block);
	write_logs(WRITE_BLOCK, log, block);
}

void		parser_cycle(t_res_mngr *resource_manager, t_parsed_info *asset,
						int fd, int log)
{
	char	*line;
	int		i;

	if (resource_manager == NULL || asset == NULL)
		rt_error("parser_cycle(): given NULL pointer");
	i = 0;
	while ((line = get_read_block(fd)) != NULL)
	{
		line = delete_tabs(line);
		if ((i = check_brackets(line)) == 1)
			pars_router(resource_manager, asset, line, log);
		else if (i == -1)
			write_logs(BAD_BRACKETS, log, line);
		free(line);
	}
}

int			parser(t_res_mngr *resource_manager, t_parsed_info *asset,
					char *file_name)
{
	int		fd;
	int		log;

	if (resource_manager == NULL || asset == NULL)
		rt_error("parser(): given NULL pointer");
	if (file_name == NULL)
		return (-1);
	log = get_log_fd(file_name);
	if (log == -1)
		return (-1);
	if ((fd = open(file_name, O_RDONLY)) < 0)
		return (-1);
	parser_cycle(resource_manager, asset, fd, log);
	close(log);
	if (close(fd))
		rt_error("parser(): close error");
	return (0);
}
