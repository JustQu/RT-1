/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 13:10:59 by maximka           #+#    #+#             */
/*   Updated: 2020/08/17 11:09:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

enum    e_types
{
    cone,
    cylinder,
    paraboloid,
    plane,
    sphere,
    torus,
    triangle,
    box,
    disk,
    rectangle
};

// struct                s_light
// {
//     cl_float4        origin;
//     cl_float4        direction;
//     t_color            color;
//     cl_float        ls; //radiance scaling factor [0, inf)
//     t_light_type    type;

//     cl_int            object_id; //for area lights
// };

// struct                    s_obj
// {
//     t_type                type;
//     t_material            material;
//     t_bbox                bounding_box;
//     cl_float4            origin;
//     cl_float4            direction;
//     cl_float4            dir2;
//     cl_float4            normal;
//     cl_float            r;
//     cl_float            r2;
//     cl_float            angle;
//     cl_float            maxm;
//     cl_float            minm;
//     cl_int                shadows;
//     cl_int                sampler_id;
// };

