#include "minishell.h"

unsigned char	sh_export(char **argv, t_env *env)
{
	int	i;

	i = 0;
	argv++;
	while (argv && *argv)
	{
		while ((*argv)[i] && !ft_isdigit((*argv)[0]) && isvalid_name_letter((*argv)[i]))
			i++;
		if (i > 0 && (*argv)[i] == '=')
		{
			(*argv)[i] = '\0';
			if(set_var(env, *argv,*argv + i + 1, 1))
				return (-1);
			(*argv)[i] = '=';
		}
		i = 0;
		argv++;
	}
	return (0);
}
