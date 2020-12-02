/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 21:41:52 by aapricot          #+#    #+#             */
/*   Updated: 2020/12/02 21:14:24 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "logs.h"
#include "offset.h"
#include "resource_manager.h"

t_selector		g_selector_obj[] = {
	{"origin", offsetof(t_parsed_object, origin), get_vector},
	{"direction", offsetof(t_parsed_object, direction), get_vector},
	{"rotation", offsetof(t_parsed_object, rotation), get_vector},
	{"scaling", offsetof(t_parsed_object, scaling), get_vector},
	{"vector1", offsetof(t_parsed_object, vector1), get_vector},
	{"vector2", offsetof(t_parsed_object, vector2), get_vector},
	{"type", offsetof(t_parsed_object, type), get_obj_type},
	{"radius", offsetof(t_parsed_object, r), get_float},
	{"radius2", offsetof(t_parsed_object, r2), get_float},
	{"maxm", offsetof(t_parsed_object, maxm), get_float},
	{"minm", offsetof(t_parsed_object, minm), get_float},
	{"material", offsetof(t_parsed_object, material), pars_material},
	{"texture", offsetof(t_parsed_object, texture), pars_texture}
};

int				g_obj_selector_size = sizeof(g_selector_obj) /
sizeof(t_selector);

void			validate_parsed_obj(t_res_mngr *resource_manager,
				t_parsed_info asset, t_parsed_object *object, int log)
{
	int			flag;

	flag = 0;
	if (object->type == -2)
	{
		flag++;
		write_logs(OBJ_TYPE_DOES_NOT_EXIST, log, "ERROR:");
	}
	if ((object->material.type == -2) && (object->texture.type == -2))
	{
		flag++;
		write_logs(MATERIAL_TYPE_DOES_NOT_EXIST, log, "ERROR:");
		write_logs(TEXTURE_TYPE_DOES_NOT_EXIST, log, "ERROR:");
	}
	if (isnan(object->origin.x))
	{
		object->origin = (cl_float4){0.0f, 0.0f, 0.0f};
		write_logs(BAD_ORIGIN, log, "WARNING:");
	}
	if (isnan(object->direction.x))
	{
		object->direction = (cl_float4){0.0f, 0.0f, 0.0f};
		write_logs(BAD_DIRECTION, log, "WARNING:");
	}
	if (flag == 0)
	{
		write_logs(PARS_SUCCESS, log, NULL);
		asset.type = 0;
		asset.data.object.type = object->type;
		asset.data.object.direction = object->direction;
		asset.data.object.material = object->material;
		asset.data.object.maxm = object->maxm;
		asset.data.object.minm = object->minm;
		asset.data.object.origin = object->origin;
		asset.data.object.r2 = object->r2;
		asset.data.object.r = object->r;
		asset.data.object.rotation = object->rotation;
		asset.data.object.scaling = object->scaling;
		asset.data.object.texture = object->texture;
		asset.data.object.vector1 = object->vector1;
		asset.data.object.vector2 = object->vector2;
		asset.data.object.boolean = 1;
		add_parsed_asset(resource_manager, asset);
	}
	else
	{
		write_logs(PARS_UNSUCCESS, log, NULL);
	}
}

void			fill_object(char *a, char *b, t_parsed_object *obj)
{
	int			i;

	i = 0;
	while (i < g_obj_selector_size)
	{
		if (!ft_strcmp(g_selector_obj[i].name, a))
		{
			g_selector_obj[i].func(b, g_selector_obj[i].offset, obj);
			break ;
		}
		i++;
	}
}

void			pars_object(t_res_mngr *resource_manager,
					t_parsed_info *asset, char *str, int log)
{
	char			*a;
	char			*b;
	t_parsed_object	obj;

	obj = get_default_obj();
	while (*str != '{' && *str != '\0')
		str++;
	str++;
	while (*str != '\0')
	{
		a = get_key(&str);
		b = get_value(&str);
		while (*str == ';' || *str == '}')
			str++;
		fill_object(a, b, &obj);
		free(a);
		free(b);
	}
	validate_parsed_obj(resource_manager, *asset, &obj, log);
}
