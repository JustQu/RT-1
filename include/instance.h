/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instance.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 20:05:10 by dmelessa          #+#    #+#             */
/*   Updated: 2020/08/09 20:20:19 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INSTANCE_H
# define INSTANCE_H

#include "material.h"
#include "objects.h"

#ifdef _WIN64
__declspec(align(4))
#endif
typedef struct			s_instance
{
	t_material			material;	// todo: сделать менеджер материалов. Зачем? чтобы не загружать полностью материал каждый раз
	t_type				type;
	int					object_id; //triangle_id if type == triangle
	int					matrix_id;
}						t_instance;

#endif
