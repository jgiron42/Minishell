#include "minishell.h"

unsigned char	sh_unset(char **argv, t_env *env)
{
	int		ret;
	int		i;

	ret = 0;
	i = 0;
	argv++;
	while(argv && *argv)
	{
		while ((*argv)[i] && !ft_isdigit((*argv)[0]) && isvalid_name_letter((*argv)[i]))
			i++;
		if ((*argv)[i] != '\0')
		{
			ret = 1;
			printf("%d : unset : %s : bad variable name\n", ret, *argv);
		}
		else if (i > 0)
		{
			if (remove_var(env, (*argv)))
				ret = 1;
		}
		i = 0;
		argv++;
	}
	return (ret);
}
