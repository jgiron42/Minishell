//
// Created by joachim on 22/11/2021.
//

#include "minishell.h"

static t_status init_pwd(t_env **env)
{
	char	*current;
	char	*real_current;
	char	*true_pwd;
	t_status	ret;

	true_pwd = my_get_working_directory("init");
	current = get_env(*env, "PWD");
	real_current = realpath(current, NULL); // unauthorized function
	if (!true_pwd || (!real_current && (errno & (EIO | ENOMEM))))
		ret = SYSCALL_FAILURE;
	else if (current && ft_strlen(current) < PATH_MAX && !path_has_dot(current) && !ft_strcmp(real_current, true_pwd))
		ret = set_env(env, "PWD", current);
	else
		ret = set_env(env, "PWD", true_pwd);
	free(true_pwd);
	free(real_current);
	return (ret);
}

static t_status init_shlvl(t_env **env)
{
	char	*current;

	current = get_env(*env, "SHLVL");
	if (!current)
		return (set_env("SHLVL", "0"));
	current = ft_itoa(ft_atoi(current) + 1);
	if (!current)
		return (SYSCALL_FAILURE);
	if (set_env("SHLVL", current) == SYSCALL_FAILURE)
	{
		free(current);
		return (SYSCALL_FAILURE);
	}
	free(current);
	return (OK);
}

t_status init_env(t_env **env)
{
	//IFS
	if (set_env(env, "PS1", "$ ", false) == SYSCALL_FAILURE ||
		set_env(env, "PS2", "> ", false) == SYSCALL_FAILURE ||
		init_pwd(**env) == SYSCALL_FAILURE ||
		init_shlvl(env) == SYSCALL_FAILURE)
		return (SYSCALL_FAILURE);
	return(OK);
}!