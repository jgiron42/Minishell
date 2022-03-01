//
// Created by jgiron on 11/26/21.
//
#include "minishell.h"

// echo -n
// my_getopt(&argv, "n", dst)

void	my_getopt(char ***argv, char *option, char *dest)
{
	int	i;

	ft_bzero(dest, 256);
	while (**argv && ***argv == '-')
	{
		if (!(**argv)[1])
			return;
		i = 0;
		while ((**argv)[++i])
			if (!ft_strchr(option, (**argv)[i]))
				return;
		i = 0;
		while ((**argv)[++i])
			dest[(int)*ft_strchr(option, (**argv)[i])] = 1;
		(*argv)++;
	}
}
