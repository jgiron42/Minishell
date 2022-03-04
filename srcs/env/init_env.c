/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiron <jgiron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 11:03:12 by jgiron            #+#    #+#             */
/*   Updated: 2022/03/04 11:03:13 by jgiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_status	init_pwd(t_env *env)
{
	char		*true_pwd;
	t_status	ret;

	true_pwd = my_get_working_directory("shell-init");
	if (!true_pwd && errno == ENOMEM)
		return (FATAL);
	if (!true_pwd)
		ret = KO;
	ret = set_var(env, "PWD", true_pwd, true);
	free(true_pwd);
	return (ret);
}

static t_status	init_shlvl(t_env *env)
{
	char	*current;

	current = get_var_val(env, "SHLVL");
	if (!current)
		return (set_var(env, "SHLVL", "0", true));
	current = ft_itoa(ft_atoi(current) + 1);
	if (!current)
		return (FATAL);
	if (set_var(env, "SHLVL", current, true) == FATAL)
	{
		free(current);
		return (FATAL);
	}
	free(current);
	return (OK);
}

t_status	init_env(t_env *env)
{
	env->is_interactive = (isatty(0) && isatty(2));
	if (env->is_interactive)
	{
		set_signal(SIGINT, sigint_handler, env);
		set_signal(SIGQUIT, SIG_IGN, env);
		set_signal(SIGTERM, SIG_IGN, env);
	}
	rl_outstream = stderr;
	if (!char_vec_resize(&env->opened_files, 3, FD_OPEN)
		|| set_var(env, "PS1", "$ ", false) == FATAL
		|| set_var(env, "PS2", "> ", false) == FATAL
		|| set_var(env, "IFS", " \t\n", false) == FATAL
		|| init_pwd(env) == FATAL
		|| init_shlvl(env) == FATAL)
		return (FATAL);
	return (OK);
}
