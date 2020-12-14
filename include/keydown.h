/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keydown.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 12:23:43 by jvoor             #+#    #+#             */
/*   Updated: 2020/12/14 12:23:53 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_LEGACY_KEYDOWN_H
# define RT_LEGACY_KEYDOWN_H

#include "interface.h"
#include "rt.h"
#include "gui.h"

int		catch_keydown_01(t_rt *rt, t_interface *interface, SDL_Event event);

#endif
