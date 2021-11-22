//
// Created by joachim on 22/11/2021.
//

#include "minishell.h

bool	path_has_dot(char *path)
{
	int dots;

	dots = 0;
	while(*path)
	{
		if (*path == '/')
		{
			if (/*dots == 0 ||*/dots == 1 || dots == 2)
				return (1);
			dots = 0;
		}
		else if (*path == '.' && dots != -1)
			++dots;
		else
			dots = -1;
		++path;
	}
	return (0);
}