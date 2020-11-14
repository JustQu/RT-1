/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 19:29:26 by dmelessa          #+#    #+#             */
/*   Updated: 2020/11/14 02:27:21 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NO_INSTANCE 0xffffffff

#include <math.h>
#include <stdlib.h>

#include "bvh.h"
#include "scene.h"
#include "utils.h"

cl_float4	point_matrix_mul(cl_float4 point, t_matrix matrix);

void	sort_nodes(t_bvh_node *nodes, int size,
					int (*cmp)(t_bvh_node, t_bvh_node))
{
	int			l;
	int			r;
	t_bvh_node	node;
	t_bvh_node	tmp;

	l = 0;
	if ((r = size - 1) == 0)
		return ;
	node = nodes[(size + 1) / 2];
	while (l < r)
	{
		while (cmp(nodes[l], node))
			l++;
		while (cmp(node, nodes[r]))
			r--;
		if (l < r)
		{
			tmp = nodes[l];
			nodes[l] = nodes[r];
			nodes[r] = tmp;
			l++;
			r--;
		}
	}
	sort_nodes(nodes, (size + 1 ) / 2, cmp);
	sort_nodes(nodes + (size + 1) / 2, size / 2, cmp);
}

t_bbox	compute_bvh_node_aabb(t_bvh_node *nodes, int size)
{
	t_bbox	node_aabb;
	t_bbox	object_aabb;
	int		i;

	node_aabb.max = (cl_float4){ .x = -INFINITY, .y = -INFINITY,
								.z = -INFINITY, .w = -INFINITY };
	node_aabb.min = (cl_float4){ .x = INFINITY, .y = INFINITY,
								 .z = INFINITY, .w = INFINITY };
	i = -1;
	while (++i < size)
	{
		object_aabb = nodes[i].aabb;
		node_aabb.max.x = float_max(object_aabb.max.x, node_aabb.max.x);
		node_aabb.max.y = float_max(object_aabb.max.y, node_aabb.max.y);
		node_aabb.max.z = float_max(object_aabb.max.z, node_aabb.max.z);
		node_aabb.min.x = float_min(object_aabb.min.x, node_aabb.min.x);
		node_aabb.min.y = float_min(object_aabb.min.y, node_aabb.min.y);
		node_aabb.min.z = float_min(object_aabb.min.z, node_aabb.min.z);
	}
	return (node_aabb);
}

int	cmp_x(t_bvh_node a, t_bvh_node b)
{
	return (a.center.x < b.center.x);
}

int cmp_y(t_bvh_node a, t_bvh_node b)
{
	return (a.center.y < b.center.y);
}

int	cmp_z(t_bvh_node a, t_bvh_node b)
{
	return (a.center.z < b.center.z);
}

/**
** @brief split node and objects inside
** The simplest approach. Select the longest axis and sort objects along this direction.
** @param node
** @param nodes
** @param size
** @return ** int
*/
int		split_bvh_node(t_bvh_node node, t_bvh_node *nodes, int size)
{
	int		split_index;
	float	length;
	int		longest_axis;

	split_index = (size + 1) / 2;
	longest_axis = 0;//x
	length = node.aabb.max.x - node.aabb.min.x;

	if (node.aabb.max.y - node.aabb.min.y > length)
	{
		length = node.aabb.max.y - node.aabb.min.y;
		longest_axis = 1; //y
	}
	if (node.aabb.max.z - node.aabb.min.z > length)
	{
		length = node.aabb.max.z - node.aabb.min.z;
		longest_axis = 2;//z
	}

	if (longest_axis == 0)
		sort_nodes(nodes, size, cmp_x);
	else if (longest_axis == 1)
		sort_nodes(nodes, size, cmp_y);
	else
		sort_nodes(nodes, size, cmp_z);
	return split_index;
}

#define MAX_STACK_DEPTH 64

static int nodes_id_stack[64];
static int stack_size;

/*
** Recursive top-down building of bvh struct
*/
int		build_internal_node(t_bvh bvh, int *current, t_bvh temp_nodes, int size)
{
	t_bvh_node	node;
	int			id;
	int			nid;
	int			split;

	id = (*current)++;
	node = (t_bvh_node){ .next = -1, .instance_id = -1 };
	if (size == 1)
	{
		bvh[id] = temp_nodes[0];
		return (id);
	}
	node.aabb = compute_bvh_node_aabb(temp_nodes, size);
	bvh[id] = node;
	split = split_bvh_node(node, temp_nodes, size);
	nid = build_internal_node(bvh, current, temp_nodes, split);
	bvh[nid].next = build_internal_node(bvh, current,
										temp_nodes + split, size - split);
	nid = id + 1;
	while (TRUE)
	{
		if ((nid = bvh[nid+1].next) == -1)
			break;
		bvh[nid].next = bvh[id + 1].next;
		if (bvh[nid].instance_id != -1)
			break;
	}
	return (id);
}

t_bvh	build_bvh(t_scene *scene)
{
	t_bvh				bvh;
	t_bvh				temp_nodes;
	t_instance_manager	instance_mngr;
	int					id;

	instance_mngr = scene->instance_mngr;
	/* malloc 2 times more nodes of bvh tree*/
	bvh = malloc(instance_mngr.ninstances * 2 * sizeof(t_bvh_node));
	temp_nodes = malloc(instance_mngr.ninstances * sizeof(t_bvh_node));
	for (int i = 0; i < instance_mngr.ninstances; i++)
	{
		temp_nodes[i].instance_id = i;
		temp_nodes[i].aabb = instance_mngr.extra[i].aabb;
		temp_nodes[i].center.x = 0.5f * (temp_nodes[i].aabb.min.x
										+ temp_nodes[i].aabb.max.x);
		temp_nodes[i].center.y = 0.5f * (temp_nodes[i].aabb.min.y
										+ temp_nodes[i].aabb.max.y);
		temp_nodes[i].center.z = 0.5f * (temp_nodes[i].aabb.min.z
										+ temp_nodes[i].aabb.max.z);
		temp_nodes[i].next = -1;
		t_instance instance = instance_mngr.instances[i];
	}
	id = 0;
	build_internal_node(bvh, &id, temp_nodes, instance_mngr.ninstances);
	free(temp_nodes);
	scene->bvh = bvh;
	return (bvh);
}
