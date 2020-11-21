/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 21:41:52 by aapricot          #+#    #+#             */
/*   Updated: 2020/11/21 20:19:03 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "logs.h"
// #include "camera.h"
// #include "rt_options.h"
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

int				g_obj_selector_size = sizeof(g_selector_obj) / sizeof(t_selector);

void			add_parsed_object(t_res_mngr *resource_manager, t_parsed_info *asset, t_parsed_object *object, int log)
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
		asset->type = 0;
		asset->data.object.type = object->type;
		asset->data.object.direction = object->direction;
		asset->data.object.material = object->material;
		asset->data.object.maxm = object->maxm;
		asset->data.object.minm = object->minm;
		asset->data.object.origin = object->origin;
		asset->data.object.r2 = object->r2;
		asset->data.object.r = object->r;
		asset->data.object.rotation = object->rotation;
		asset->data.object.scaling = object->scaling;
		asset->data.object.texture = object->texture;
		asset->data.object.vector1 = object->vector1;
		asset->data.object.vector2 = object->vector2;
		asset->data.object.boolean = 1;
		// printf("type = %d\n", object->type);
		// printf("origin.x = %f\n", object->origin.x);
		// printf("origin.y = %f\n", object->origin.y);
		// printf("origin.z = %f\n", object->origin.z);
		// printf("direction.x = %f\n", object->direction.x);
		// printf("direction.y = %f\n", object->direction.y);
		// printf("direction.z = %f\n", object->direction.z);
		// printf("rotation.x = %f\n", object->rotation.x);
		// printf("rotation.y = %f\n", object->rotation.y);
		// printf("rotation.z = %f\n", object->rotation.z);
		// printf("scaling.x = %f\n", object->scaling.x);
		// printf("scaling.y = %f\n", object->scaling.y);
		// printf("scaling.z = %f\n", object->scaling.z);
		// // printf("vector1 = %s\n", object->vector1);
		// printf("radius = %f\n", object->radius);
		// printf("radius2 = %f\n", object->radius2);
		// printf("material\ntype = %d\n", object->material.type);
		// printf("kt = %f\n", object->material.kt);
		// printf("texture\ntype = %d\n", object->texture.type);
		// printf("color.x = %f\n", object->material.reflective_color.r);
		// printf("color.y = %f\n", object->material.reflective_color.g);
		// printf("color.z = %f\n", object->material.reflective_color.b);
		add_parsed_asset(resource_manager, *asset);
	}
	else
	{
		write_logs(PARS_UNSUCCESS, log, NULL);
	}
}

char			*get_key(char **str)
{
	char			*a;
	int				i;

	a = (char *)malloc(sizeof(char) * 256);
	i = 0;
	while (**str != '=' && **str != '\0' && i < 255)
	{
		a[i] = **str;
		i++;
		*str += 1;
	}
	a[i] = '\0';
	if (**str != '\0')
		*str += 1;
	return (a);
}

char			*get_value(char **str)
{
	char		*b;
	int			i;
	int			count;

	count = 0;
	b = (char *)malloc(sizeof(char) * 256);
	i = 0;
	if (**str == '{')
	{
		count = 1;
		*str += 1;
		while (**str != '\0' && i < 255)
		{
			if (**str == '{')
				count++;
			else if (**str == '}')
				count--;
			if (count == 0)
				break ;
			b[i] = **str;
			i++;
			*str += 1;
		}
	}
	else
	{
		while (**str != ';' && **str != '}' && **str != '\0' && i < 255)
		{
			b[i] = **str;
			i++;
			*str += 1;
		}
	}
	if (**str != '\0')
		*str += 1;
	b[i] = '\0';
	return (b);
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
		// printf("key = %s\ncheck = %s\n\n", a, g_selector_obj[i].name);
		i++;
	}
}

void			pars_object(t_res_mngr *resource_manager, t_parsed_info *asset, char *str, int log)
{
	char			*a;
	char			*b;
	t_parsed_object	obj;
	// int				i;

	// i = 0;
	obj = get_default_obj();
	while (*str != '{' && *str != '\0')
		str++;
	str++;
	while (*str != '\0')
	{
		a = get_key(&str);
		b = get_value(&str);
		printf("%s\n%s\n====\n", a, b);
		while (*str == ';' || *str == '}')
			str++;
		fill_object(a, b, &obj);
		// while (i < g_obj_selector_size)
		// {
		// 	if (!ft_strcmp(g_selector_obj[i].name, a))
		// 	{
		// 		g_selector_obj[i].func(b, g_selector_obj[i].offset, &obj);
		// 		break ;
		// 	}
		// 	// printf("key = %s\ncheck = %s\n\n", a, g_selector_obj[i].name);
		// 	i++;
		// }
		// i = 0;
		free(a);
		free(b);
	}
	add_parsed_object(resource_manager, &asset, &obj, log);
}
