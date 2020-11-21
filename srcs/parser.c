/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 19:56:06 by aapricot          #+#    #+#             */
/*   Updated: 2020/11/21 22:58:47 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "parser.h"
#include "offset.h"
#include "logs.h"
#include "resource_manager.h"
#include "scene.h"
// #include "rt.h"

void		to_lower(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
}

int			check_block_type(char *str)
{
	int		i;

	i = 0;
	to_lower(str);
	// if (!ft_strcmp(str, "ambient_light"))
		// i = 1;
	if (!ft_strcmp(str, "object"))
		i = object;
	else if (!ft_strcmp(str, "light"))
		i = light;
	else if (!ft_strcmp(str, "camera"))
		i = camera;
	else if (!ft_strcmp(str, "options"))
		i = options;
	free(str);
	return (i);
}

int			block_type_lengh(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '{' && str[i] != '=')
		i++;
	return (i);
}

int			get_block_type(char *str)
{
	int		i;
	char	*type;
	int		j;

	i = 0;
	j = 0;
	if (str[0] == '=' || str[0] == '{')
		return (-1);
	type = (char *)malloc(sizeof(char) * (block_type_lengh(str) + 1));
	while (str[i] != '{' && str[i] != '=')
	{
		type[j] = str[i];
		i++;
		j++;
	}
	type[j] = '\0';
	return (check_block_type(type));
}

int			check_brackets(char *str)
{
	int		i;
	int		brackets;
	int		count;

	i = 0;
	count = 0;
	brackets = 0;
	while (str[i] != '\0')
	{
		// if (count == 0 && brackets != 0)
		// 	return (-1);
		if (str[i] == '{')
		{
			brackets++;
			count++;
		}
		else if (str[i] == '}')
		{
			brackets++;
			count--;
		}
		i++;
	}
	if (count != 0)
		return (-1);
	else if (count == 0 && brackets == 0)
		return (-2);
	return (1);
}

int			char_count(char *str)
{
	int		i;
	int		count;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '\t' && str[i] != ' ' && str[i] != '\n')
			count++;
		i++;
	}
	return (count);
}

char		*delete_tabs(char *str)
{
	char	*res;
	int		i;
	int		j;

	j = 0;
	i = 0;
	res = (char *)malloc(sizeof(char) * (char_count(str) + 1));
	while (str[i] != '\0')
	{
		if (str[i] != '\t' && str[i] != ' ' && str[i] != '\n')
		{
			res[j] = str[i];
			j++;
		}
		i++;
	}
	res[j] = '\0';
	free(str);
	return (res);
}

char		*get_read_block(int fd)
{
	char	*current_line;
	char	*block_line;
	char	*tmp;
	int		i;

	block_line = NULL;
	while ((i = get_next_line(fd, &current_line)) == 1)
	{
		if (!ft_strcmp(current_line, "\0") && block_line != NULL)
		{
			free(current_line);
			break ;
		}
		else
		{
			if (block_line == NULL)
				block_line = ft_strdup(current_line);
			else
			{
				tmp = block_line;
				block_line = ft_strjoin(tmp, current_line);
				free(tmp);
			}
		}
		free(current_line);
	}
	return (block_line);
}

void		pars_router(t_res_mngr *resource_manager, t_parsed_info *asset , int block_type, char *block, int log, t_camera *cam)
{
	// if (block_type == ambient_light)
	// 	printf("ambient_light:\n");
	if (block_type == object)
	{
		pars_object(resource_manager, &asset, block, log);
		write_logs(WRITE_BLOCK, log, block);
	}
	else if (block_type == light)
		pars_light(block);
	else if (block_type == camera)
		pars_camera(block, cam);
	else if (block_type == options)
		printf("options:\n");
	else if (block_type == 0)
		write_logs(UNKNOWN_SCENE_TYPE, log, block);
	else if (block_type == -1)
		write_logs(SCENE_TYPE_DOES_NOT_EXIST, log, block);
}

int			parser(t_res_mngr *resource_manager, t_parsed_info *asset, char *file_name, t_camera *camera)  //t_tr *rt
{
	int		fd;
	char	*line;
	int		i;
	int		log;

	i = 0;
	log = get_log_fd(file_name);
	if (log == -1)
		return (0);
	if ((fd = open(file_name, O_RDONLY)) < 0)
		;
	while ((line = get_read_block(fd)) != NULL)
	{
		line = delete_tabs(line);
		if ((i = check_brackets(line)) == 1)
		{
			pars_router(resource_manager, asset, get_block_type(line), line, log, camera);
			printf("%s\n\n", line);
		}
		else if (i == -2)
			write_logs(COMMENT, log, line);
		else
			write_logs(BAD_BRACKETS, log, line);
		free(line);
	}
	close(log);
	close(fd);
	return (0);
}
