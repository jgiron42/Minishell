//
// Created by jgiron on 11/26/21.
//
#include "minishell.h"
char	shell_kill(char **argv, t_env *env)
{
	char	options[256];
	 char *array[] = {"HUP", "INT", "QUIT", "ILL", "TRAP", "ABRT", "BUS",
						  "FPE", "KILL", "USR1", "SEGV", "USR2", "PIPE", "ALRM",
						  "TERM", "STKFLT", "CHLD", "CONT", "STOP", "TSTP",
						  "TTIN", "TTOU", "URG", "XCPU", "XFSZ", "VTALRM", "PROF",
						  "WINCH", "IO", "PWR", "SYS", "RTMIN", "RTMIN+1", "RTMIN+2",
						  "RTMIN+3", "RTMIN+4", "RTMIN+5", "RTMIN+6", "RTMIN+7",
						  "RTMIN+8", "RTMIN+9", "RTMIN+10", "RTMIN+11", "RTMIN+12",
						  "RTMIN+13", "RTMIN+14", "RTMIN+15", "RTMAX-14", "RTMAX-13",
						  "RTMAX-12", "RTMAX-11", "RTMAX-10", "RTMAX-9", "RTMAX-8",
						  "RTMAX-7", "RTMAX-6", "RTMAX-5", "RTMAX-4", "RTMAX-3",
						  "RTMAX-2", "RTMAX-1", "RTMAX", NULL};
	int i;

	(void)argv;
	(void)env;
	my_getopt(&argv, "l", options);
	if (!options['l'])
		my_getopt(&argv, "s", options);
	else if (*argv)
		ft_putstr_fd(array[ft_atoi(*argv)], 1);
	else
	{
		i = -1;
		while (array[++i])
		{
			ft_putstr_fd(array[i], 1);
			write(1, " ", 1);
		}
	}
	if (options['s']) {
		i = -1;
		if (!*argv) {
			ft_putstr_fd(NAME ": kill: -s: option requires an argument\n", 2);
			return (1);
		}
		if (!argv[1]) {
			ft_putstr_fd(NAME ": kill: missing argument\n", 2);
			return (1);
		}
//		TODO: ft_toupper(argv[1]);
		while (array[++i] && ft_strcmp(array[i], *argv));
		if (!array[i])
		{
			ft_putstr_fd(NAME ": kill: invalid signal name\n", 2);
			return (1);
		}
		if (kill(ft_atoi(argv[1]), i) == -1)
		{
			perror(NAME ": kill");
			return (1);
		}
	}
	return (0);
}