
#include "rt.h"
#define RED "\033[38;2;200;20;20m"
#define EOC "\033[0m"

void		rt_error(char *message)
{
	ft_putstr(RED);
	ft_putendl(message);
	ft_putstr(EOC);
	exit(-1);
}