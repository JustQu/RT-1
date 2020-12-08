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
