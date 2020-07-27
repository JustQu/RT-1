/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_program.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 16:19:38 by marvin            #+#    #+#             */
/*   Updated: 2020/07/27 16:19:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <io.h>
#include <fcntl.h>

const char *files[] = {
    "../srcs/ocl/main.cl",
    NULL};

cl_program create_program(cl_context context)
{
    int ret;
    int i;
    int fd;
    char *str;
    cl_program program;

    i = 0;
    str = (char*)malloc(sizeof(char) * BUFF);
    ret = 0;
    while (files[i])
    {
        fd = open(files[i], O_RDONLY);
        ret = read(fd, str, BUFF);
        str[ret] = 0;
        i++;
    }
    program = clCreateProgramWithSource(context, 1, (const char **)&str, NULL, &ret);
    assert(!ret);
    return (program);
}