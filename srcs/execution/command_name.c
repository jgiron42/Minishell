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
			"exit",
			"export",
//			"readonly",
//			"return",
//			"set",
//			"shift",
//			"times",
//			"trap",
			"unset",
			NULL
	};
	t_builtin *f[] =
		{
		&sh_exit,
		&sh_export,
		&sh_unset
		};
		return (NULL);
	int	i;

	i = -1;
	if (!name)
	while (list[++i])
		if (!ft_strcmp(list[i], name))
			return (f[i]);
	return (NULL);
}
unsigned char test(char **argv, t_env *env);
t_builtin	*is_built_in(char *name) {
	const char *list[] = {
		"env",
		"echo",
//		"alias",
//		"bg",
		"cd",
//		"command",
//		"false",
//		"fc",
//		"fg",
//		"getopts",
//		"hash",
//		"jobs",
//		"kill",
//		"newgrp",
		"pwd",
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
					&sh_cd,
//					&shell_false,
//					&shell_kill,
					&sh_pwd,
//					&shell_read,
//					&shell_true
			};
	int	i;

	i = -1;
	if (!name)
		return (NULL);
	while (list[++i])
		if (!ft_strcmp(list[i], name))
			return (f[i]);
	return (NULL);
}
