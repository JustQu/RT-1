/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 00:07:37 by dmelessa          #+#    #+#             */
/*   Updated: 2020/10/03 23:22:03 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIAL_H
# define MATERIAL_H

# ifndef __OPENCL_C_VERSION__
#  include "rt_types.h"
#  include "color.h"
# endif

typedef enum e_material_type		t_material_type;
typedef struct s_material			t_material; //64 bytes

enum e_material_type
{
	matte, //kd, ka
	phong,
	emissive,
	reflective,
	metal,		//mirror
	dielectric	//transparance
};

/**
** color					//16
** reflective color 		//16
** type						//4
** kd						//4 -- diffuse
** ka						//4 -- ambient
** ks						//4 -- specular
** kr						//4 -- reflective
** kt						//4 -- tranpsarente
** exp						//4
** uchar is_reflective		//1
** uchar is_transparent		//1
**
** uchar gap[8]				//8
*/

struct					s_material //kd + ks < 1.0
{
	t_color				reflective_color;					//16 bytes
	t_material_type		type;								//4		20
	cl_float			kd; //diffuse reflection[0, 1]		//4		24
	cl_float			ka; //ambient reflection			//4		28
	cl_float			ks; //specular reflection [0, 1]	//4		32
	cl_float			kr;	//reflective coefficient		//4		36
	cl_float			kt; //transparent coefficient		//4		40
	cl_float			exp;								//4		44

	int					texture_id;							//4		48

	cl_uchar 			is_reflective;						//1		49
	cl_uchar			is_transparent;						//1		50
	cl_uchar			gap[14];							//2		64
};

#endif
