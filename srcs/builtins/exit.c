#include "minishell.h"

unsigned char	sh_exit(char **argv, t_env *env)
{
	int	i;

	i = 0;
	argv++;
	if (!(*argv))
		ft_exit(env);
	while (ft_isdigit((*argv)[i]))
		i++;
	if ((*argv)[i] == '\0')
		g_err = ft_atoi(*argv);
	ft_exit(env);
	return(0);
}
