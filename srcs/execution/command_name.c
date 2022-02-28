//
// Created by joachim on 30/11/2021.
//
#include <minishell.h>

t_builtin	*is_special_built_in(char *name)
{
	const char *list[] = {
//			"break",
//			":",
//			"continue",
//			".",
//			"eval",
//			"exec",
//			"exit",
			"export",
//			"readonly",
//			"return",
//			"set",
//			"shift",
//			"times",
//			"trap",
//			"unset",
			NULL
	};
	 t_builtin *f[] =
			{
//			&shell_exit,
			&sh_export,
//			&shell_unset
			};
	int	i;

	i = -1;
	while (list[++i])
		if (!ft_strcmp(list[i], name))
			return (f[i]);
	return (NULL);
}

t_builtin	*is_built_in(char *name) {
	const char *list[] = {
		"env",
		"echo",
//		"alias",
//		"bg",
//		"cd",
//		"command",
//		"false",
//		"fc",
//		"fg",
//		"getopts",
//		"hash",
//		"jobs",
//		"kill",
//		"newgrp",
//		"pwd",
//		"read",
//		"true",
//		"umask",
//		"unalias",
//		"wait",
		NULL
	};
	 t_builtin *f[] =
			{
					&sh_env,
					&sh_echo,
//					&shell_cd,
//					&shell_false,
//					&shell_kill,
//					&shell_pwd,
//					&shell_read,
//					&shell_true
			};
	int	i;

	i = -1;
	while (list[++i])
		if (!ft_strcmp(list[i], name))
			return (f[i]);
	return (NULL);
}
