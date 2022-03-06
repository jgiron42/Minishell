/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiron <jgiron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 11:03:57 by jgiron            #+#    #+#             */
/*   Updated: 2022/03/04 11:03:59 by jgiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_status	permission_denied(char *name, t_env *env)
{
	ft_putstr_fd(NAME": ", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd(": Permission denied\n", 2);
	env->err = 126;
	return (OK);
}

t_status	is_a_directory(char *name, t_env *env)
{
	ft_putstr_fd(NAME": ", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd(": Is a directory\n", 2);
	env->err = 126;
	return (OK);
}

t_status	command_not_found(char *name, t_env *env)
{
	ft_putstr_fd(NAME": ", 2);
	if (name)
		ft_putstr_fd(name, 2);
	ft_putstr_fd(": Not found\n", 2);
	env->err = 127;
	return (OK);
}

void	clean_fds(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->opened_files.size)
	{
		if (env->opened_files.data[i] == FD_TMP)
		{
			close(i);
			env->opened_files.data[i] = FD_CLOSE;
		}
		i++;
	}
}

t_status	exec_program(char *name, t_simple s, t_env *env)
{
	char		**envp;
	pid_t		pid;

	if (!name || (access(name, X_OK) && (errno == ENOENT || errno == ENOTDIR)))
		return (command_not_found(s.argv[0], env));
	if (is_dir(name))
		return (is_a_directory(s.argv[0], env));
	if (access(name, X_OK))
		return (permission_denied(s.argv[0], env));
	pid = fork();
	if (pid == -1)
		return (FATAL);
	else if (!pid)
	{
		reset_signals(env);
		clean_fds(env);
		envp = serialize_env(env->vars);
		if (!envp)
			return (FATAL);
		execve(name, s.argv, envp);
		free_env(env);
		perror(NAME);
		exit (1);
	}
	get_err(env, pid);
	return (OK);
}
