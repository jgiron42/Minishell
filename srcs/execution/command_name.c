//
// Created by joachim on 30/11/2021.
//
#include <minishell.h>

t_builtin	*is_special_built_in(char *name)
{
	const char		*list[] = {"exit", "export", "unset", NULL};
	const t_builtin	*f[] = {&sh_exit, &sh_export, &sh_unset};
	int				i;

	i = -1;
	while (list[++i])
		if (!ft_strcmp(list[i], name))
			return (f[i]);
	return (NULL);
}

t_builtin	*is_built_in(char *name)
{
	const char		*list[] = {"env", "echo", "cd", "pwd", NULL};
	const t_builtin	*f[] = {&sh_env, &sh_echo, &sh_cd, &sh_pwd};
	int				i;

	i = -1;
	if (!name)
		return (NULL);
	while (list[++i])
		if (!ft_strcmp(list[i], name))
			return (f[i]);
	return (NULL);
}
