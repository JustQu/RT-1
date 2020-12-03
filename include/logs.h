/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 16:10:52 by aapricot          #+#    #+#             */
/*   Updated: 2020/12/03 19:19:07 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGS_H
# define LOGS_H

# include "parser.h"

# define UNKNOWN_SCENE_TYPE					-1
# define SCENE_TYPE_DOES_NOT_EXIST			-2
# define OBJ_TYPE_DOES_NOT_EXIST			-3
# define MATERIAL_TYPE_DOES_NOT_EXIST		-4
# define TEXTURE_TYPE_DOES_NOT_EXIST		-5
# define WRITE_BLOCK						-6
# define COMMENT							-7
# define BAD_BRACKETS						-8
# define VALID_BLOCK						-9
# define UNKNOWN_OBJ_TYPE					-10
# define UNKNOWN_MATERIAL_TYPE				-11
# define UNKNOWN_TEXTURE_TYPE				-12
# define COLOR_DOES_NOT_EXIST				-13
# define PARS_SUCCESS						-14
# define PARS_UNSUCCESS						-15
# define BAD_ORIGIN							-16
# define BAD_DIRECTION						-17
# define BAD_SOLID_COLOR					-18
# define BAD_EVEN_COLOR						-19
# define BAD_ODD_COLOR						-20
# define BAD_CAMERA_ORIGIN					-21
# define BAD_CAMERA_DIRECTION				-22
# define BAD_CAMERA_ZOOM					-23
# define BAD_CAMERA_TYPE					-24
# define NO_CAMERA							-25

void		write_logs(int num_log, int fd, char *str);

#endif
