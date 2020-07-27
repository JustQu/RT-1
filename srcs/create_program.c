/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_program.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 16:19:38 by marvin            #+#    #+#             */
/*   Updated: 2020/07/27 20:30:35 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <io.h>
#include <fcntl.h>

const char *files[] = {
    "./srcs/ocl/main.cl",
    NULL
};

cl_program create_program(cl_context context)
{
    int ret;
    int i;
    int fd;
    char **str;
    cl_program program;

    i = 0;
	str = malloc (sizeof(char *) * 1);
    str[0] = (char*)malloc(sizeof(char) * BUFF);
    ret = 0;
    while (files[i])
    {
        fd = open(files[i], O_RDONLY);
        ret = read(fd, str[0], BUFF);
        str[0][ret] = 0;
        i++;
    }
    program = clCreateProgramWithSource(context, 1, (const char **)str, NULL, &ret);
    assert(!ret);
    return (program);
}
