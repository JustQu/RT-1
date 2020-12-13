/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_call.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 17:02:01 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/12 17:02:02 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// Created by Hugor Chau on 12/8/20.
//

#include "rt.h"

void		safe_call(int res, char *message)
{
	if (res == 0)
		return ;
	rt_error(message);
}

void		safe_call_ptr(void *res, char *message)
{
	if (res != NULL)
		return ;
	rt_error(message);
}
