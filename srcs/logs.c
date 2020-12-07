/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 15:51:27 by aapricot          #+#    #+#             */
/*   Updated: 2020/12/07 22:06:02 by aapricot         ###   ########.fr       */
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
	}
	else if (num_log == SCENE_TYPE_DOES_NOT_EXIST)
	{
		ft_putstr_fd("Scene type does not exist:\n", fd);
		ft_putendl_fd(str, fd);
	}
	else if (num_log == UNKNOWN_OBJ_TYPE)
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
	else if (num_log == MATERIAL_TYPE_DOES_NOT_EXIST)
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
	else if (num_log == COLOR_DOES_NOT_EXIST)
	{
		ft_putstr_fd("Color does not exist:\n", fd);
		ft_putendl_fd(str, fd);
		ft_putchar_fd('\n', fd);
	}
	else if (num_log == BAD_ORIGIN)
	{
		ft_putendl_fd(str, fd);
		ft_putendl_fd("Has no origin. Using default param\n", fd);
	}
	else if (num_log == BAD_ROTATION)
	{
		ft_putendl_fd(str, fd);
		ft_putendl_fd("Has no rotation. Using default param", fd);
	}
	else if (num_log == BAD_SOLID_COLOR)
	{
		ft_putendl_fd(str, fd);
		ft_putendl_fd("Solid color does not exist. Using default: {1.0f, 1.0f, 1.0f}", fd);
	}
	else if (num_log == BAD_EVEN_COLOR)
	{
		ft_putendl_fd(str, fd);
		ft_putendl_fd("Even color does not exist. Using default: {0.5f, 0.5f, 0.5f}", fd);
	}
	else if (num_log == BAD_ODD_COLOR)
	{
		ft_putendl_fd(str, fd);
		ft_putendl_fd("Odd color does not exist. Using default: {0.0f, 0.0f, 1.0f}", fd);
	}
	else if (num_log == BAD_CAMERA_ORIGIN)
	{
		ft_putendl_fd(str, fd);
		ft_putendl_fd("Camera origin does not exist. Using default", fd);
	}
	else if (num_log == BAD_CAMERA_DIRECTION)
	{
		ft_putendl_fd(str, fd);
		ft_putendl_fd("Camera direction does not exist. Using default", fd);
	}
	else if (num_log == BAD_CAMERA_ZOOM)
	{
		ft_putendl_fd(str, fd);
		ft_putendl_fd("Camera zoom does not exist. Using default", fd);
	}
	else if (num_log == BAD_CAMERA_TYPE)
	{
		ft_putendl_fd(str, fd);
		ft_putendl_fd("Camera type does not exist. Using perspective", fd);
	}
	else if (num_log == NO_CAMERA)
	{
		ft_putendl_fd(str, fd);
		ft_putendl_fd("Camera does not exist. Using default camera", fd);
	}
	else if (num_log == UNKNOWN_OBJ_TYPE)
	{
		ft_putendl_fd(str, fd);
		ft_putendl_fd("Unkwnown object type", fd);
	}
	else if (num_log == ANGLE_DOES_NOT_EXIST)
	{
		ft_putendl_fd(str, fd);
		ft_putendl_fd("Angle of cone does not exist", fd);
	}
	else if (num_log == BAD_MINM_MAXM)
	{
		ft_putendl_fd(str, fd);
		ft_putendl_fd("Bad minm or maxm", fd);
	}
	else if (num_log == RADIUS_DOES_NOT_EXIST)
	{
		ft_putendl_fd(str, fd);
		ft_putendl_fd("Radius does not exist", fd);
	}
	else if (num_log == VECTORS_DOES_NOT_EXIST)
	{
		ft_putendl_fd(str, fd);
		ft_putendl_fd("Bad vectors", fd);
	}
	else if (num_log == BAD_DIFFUSE_COEFFICIEN)
	{
		ft_putendl_fd(str, fd);
		ft_putendl_fd("Diffuse coefficient does not exist", fd);
	}
	else if (num_log == BAD_INTENSITY)
	{
		ft_putendl_fd(str, fd);
		ft_putendl_fd("Intensity does not exist", fd);
	}
	else if (num_log == BAD_REFLECTIVE)
	{
		ft_putendl_fd(str, fd);
		ft_putendl_fd("Reflective coefficietn does not exist", fd);
	}
	else if (num_log == BAD_ROUGHNESS)
	{
		ft_putendl_fd(str, fd);
		ft_putendl_fd("Roughness does not exist", fd);
	}
	else if (num_log == BAD_TRANSMISSION)
	{
		ft_putendl_fd(str, fd);
		ft_putendl_fd("Transmission coefficient does not exist", fd);
	}
	else if (num_log == BAD_SPECULAR)
	{
		ft_putendl_fd(str, fd);
		ft_putendl_fd("Specular coefficient does not exist", fd);
	}
	else if (num_log == BAD_AMBIENT)
	{
		ft_putendl_fd(str, fd);
		ft_putendl_fd("Ambient coefficient does not exist", fd);
	}
}
