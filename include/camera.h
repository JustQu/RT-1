/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 17:46:35 by dmelessa          #+#    #+#             */
/*   Updated: 2020/10/30 13:34:08 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

#include "rt_types.h"

typedef enum e_camera_type	t_camera_type;
typedef struct s_camera		t_camera; //160
typedef struct s_viewplane	t_viewplane;

/**
** @brief Набор типов камеры
**
** orthographic - ортографическая проекция
** perspective - перспектива
** thin_lens - эффект тонкой линзы
** fisheye - эффект рыбьего глаза
** spherical - сферическая проекция
** stereo - стерео изображение
*/
enum	e_camera_type
{
		orthographic,
		perspective,
		thin_lens,
		fisheye,
		spherical,
		stereo
};

/**
** @brief Плоскость проецирования
** pixel_size - размер пикселя, по умолчанию 1
** width - ширина плоскости
** height - высота плоскости
*/
struct s_viewplane
{
	cl_float	pixel_size;
	cl_int		width;
	cl_int		height;
};

/**
** @TODO: make transformation matrix
** TODO: singularity paragraph 9.9
**
*/

/**
** @brief Класс камеры
**
** viewplane - плоскоть проецирования
** origin - местоположение камеры
** direction - напралвние взгляда
** up -вектор вверх
** u, v, w - внутренняя система координат камеры
** d - расстояние до viewplane, плоскости проецирования
** zoom - коэффициент приближения
** exposure_time - экспозиция
** type - тип камеры
** sampler_id - идентификатор сэмплера для тонкой линзы
** normalized - флаг cостояния, указывающий на нормализованные координаты
** l - Радиус тонкой линзы, либо коэффициент в сферической камере, либо расстояние между изображениями в стерео камере
** f - расстояние до фокальной плоскости тонкой линзы, либо максимальное угловое поле в рыбьем глазе.
*/
struct	s_camera
{
	cl_float4			origin; // eye
	cl_float4			direction; // lookat - eye
	cl_float4			up; // (0, 1, 0)
	cl_float4			u;
	cl_float4			v; // actually we need only th3 vectors. the up vector could be hardcodeded and w = -direction
	cl_float4			w;
	t_viewplane			viewplane;
	cl_float			d; //the view-plane distance
	cl_float			zoom; //zoom factor
	cl_float			exposure_time; //using somewhere later
	t_camera_type		type;
	cl_int				sampler_id; //thin_camera
	cl_int				normalized;
	//thin-lens camera
	cl_float			l; //lens radius or lambda
	cl_float			f; //focal plane distance or psi_max in fisheye

//note: prob not needed
	cl_float			ratio;
	cl_float			inv_w;
	cl_float			inv_h;
	cl_float			angle;
	cl_int				fov;
};

void	compute_uvw(t_camera *camera);

#endif
