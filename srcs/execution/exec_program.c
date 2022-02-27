//
// Created by joachim on 23/02/2022.
//
#include "minishell.h"

t_status	permission_denied(char *name)
{
	ft_putstr_fd(name, 2);
	ft_putstr_fd(": Permission denied\n", 2);
	g_err = 126;
	return (OK);
}

t_status	is_a_directory(char *name)
{
	ft_putstr_fd(name, 2);
	ft_putstr_fd(": Is a directory\n", 2);
	g_err = 126;
	return (OK);
}

void	clean_fds(t_env *env)
{
	int i = 0;

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

t_status exec_program(char *name, t_simple s, t_env *env)
{
	char **envp;
	pid_t pid;
	struct	stat buf;

	if (stat(name, &buf) == -1 || S_ISDIR(buf.st_mode))
		return (is_a_directory(name));
	if (access(name, X_OK))
		return (permission_denied(name));
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
	get_g_err(pid);
	return (OK);
}
