#include "minishell.h"

unsigned char	sh_echo(char **argv, t_env *env)
{
	char	dest[256];

	(void)env;
	argv++;
	my_getopt(&argv, "n", dest);
	while (*argv)
	{
		ft_putstr_fd((*argv), 1);
		argv++;
		if (*argv)
			write(1, " ", 1);
	}
	if (!dest['n'])
		write(1, "\n", 1);
	return (0);
}
