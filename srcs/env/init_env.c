//
// Created by joachim on 22/11/2021.
//

#include "minishell.h"

static t_status init_pwd(t_var_list **env)
{
	char	*current;
	char	*real_current;
	char	*true_pwd;
	t_status	ret;

	true_pwd = my_get_working_directory("shell-init");
	if (!true_pwd && errno == ENOMEM)
		return (FATAL);
	current = get_env_val(*env, "PWD");
	real_current = ft_realpath(current, NULL); // unauthorized function
//	printf("===========> %s\n", current);
//	printf("===========> %s\n", real_current);
//	printf("===========> %s\n", true_pwd);
	if (!true_pwd || (!real_current && (errno == EIO || errno == ENOMEM)))
		ret = FATAL;
	else if (current && ft_strlen(current) < PATH_MAX && !path_has_dot(current) && !ft_strcmp(real_current, true_pwd))
		ret = OK;//ret = set_env(env, "PWD", current, true);
	else
		ret = set_env(env, "PWD", true_pwd, true);
	free(true_pwd);
	free(real_current);
	return (ret);
}

static t_status init_shlvl(t_var_list **env)
{
	char	*current;

	current = get_env_val(*env, "SHLVL");
	if (!current)
		return (set_env(env, "SHLVL", "0", true));
	current = ft_itoa(ft_atoi(current) + 1);
	if (!current)
		return (FATAL);
	if (set_env(env, "SHLVL", current, true) == FATAL)
	{
		free(current);
		return (FATAL);
	}
	free(current);
	return (OK);
}

t_status init_env(t_var_list **env)
{
	//IFS
	if (set_env(env, "PS1", "$ ", false) == FATAL ||
		set_env(env, "PS2", "> ", false) == FATAL ||
		init_pwd(env) == FATAL ||
		init_shlvl(env) == FATAL)
		return (FATAL);
	return(OK);
}