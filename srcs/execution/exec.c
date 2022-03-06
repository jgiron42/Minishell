/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiron <jgiron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 11:04:05 by jgiron            #+#    #+#             */
/*   Updated: 2022/03/04 11:04:07 by jgiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned char 		g_int;

typedef		t_status (*t_command_handler)(union u_command, t_env *env);

t_status	exec_simple(union u_command cmd, t_env *env)
{
	t_simple	s;
	int			ret;
	char		*name;

	s = cmd.simple;
	expand_simple(&s, env);
	ret = perform_redirection(env, s.redir_list);
	if (ret == KO && !env->is_interactive && (s.argv && is_special_built_in(s.argv[0])))
		ret = FATAL;
	if (ret == FATAL)
		return (FATAL);
	if (!s.argv || !s.argv[0])
		ret = OK;
	else if (ft_strchr(s.argv[0], '/'))
		ret = exec_program(s.argv[0], s, env);
	else if (is_special_built_in(s.argv[0]))
		ret = exec_special_builtin(s, env);
	else if (is_built_in(s.argv[0]))
		ret = exec_regular_builtin(s, env);
	else
	{
		ret = path_find(s.argv[0], env,&name);
		if (ret != FATAL)
			ret = exec_program(name, s, env);
		free(name);
	}
	ft_free_split(s.argv);
	if (reset_redirection(env, s.redir_list) == FATAL)
		return (FATAL);
	return (ret);
}

t_status set_pipe(const t_pipeline *p, const int *next_pipe, int prev_pipe_read, t_env *env) {
	int ret;

	ret = OK;
	if (p->next)
	{
		if (redir(next_pipe[1], 1, NULL, env) == FATAL || close(next_pipe[0]) == -1)
			ret = FATAL;
	}
	if (prev_pipe_read != -1)
	{
		if (redir(prev_pipe_read, 0, NULL, env) == FATAL)
			ret = FATAL;
	}
	if (ret != OK)
		return (my_perror(env, (char *[2]){"Can't set pipe", NULL}, true, FATAL), FATAL);
	return (OK);
}

t_status	exec_pipeline(union u_command cmd, t_env *env)
{
	t_pipeline *p;
	int			next_pipe[2];
	int			prev_pipe_read;
	int 		ret;
	int			to_wait;

	to_wait = -1;
	p = cmd.pipeline;
	prev_pipe_read = -1;
	while (p)
	{
		next_pipe[0] = -1;
		if (p->next && pipe(next_pipe) < -1)
			return(FATAL);
		ret = fork();
		if (ret == -1)
			return(FATAL);
		else if (!ret)
		{
			reset_signals(env);
			env->is_interactive = false;
			if (set_pipe(p, next_pipe, prev_pipe_read, env) == OK)
				exec_command(p->command, env);
			exit(env->err);
		}
		if (prev_pipe_read != -1)
			close(prev_pipe_read);
		if (next_pipe[0] != -1)
			close(next_pipe[1]);
		prev_pipe_read = next_pipe[0];
		to_wait++;
		p = p->next;
	}
	if (to_wait >= 0)
		get_err(env, ret);
	while (--to_wait >= 0)
		if (wait(NULL) == -1 && errno == EINTR)
			return (FATAL);
	return (OK);
}

t_status	exec_list(union u_command cmd, t_env *env)
{
	t_list *l;
	t_status ret;

	l = cmd.list;
	while (l)
	{
		ret = exec_command(l->command, env);
		if ( ret != OK ||
			(l->sep == AND_IF && env->err != 0) ||
			(l->sep == OR_IF && env->err == 0))
			break;
		l = l->next;
	}
	return (ret);
}

t_status	exec_grouping(union u_command cmd, t_env *env)
{
	t_grouping	*g;
	int			ret;
	pid_t		pid;

	g = cmd.grouping;
	ret = OK;
	if (expand_redir(&g->redir_list, env) == FATAL)
		return (FATAL);
	if (perform_redirection(env, g->redir_list) == FATAL)
		return (FATAL);
	if (g->is_in_subshell)
	{
		pid = fork();
		if (pid == -1)
			return (FATAL);
		if (!pid)
		{
			reset_signals(env);
			env->is_interactive = false;
			exec_command(g->command, env);
			ft_exit(env);
		}
		get_err(env, pid);
	}
	else
		ret = exec_command(g->command, env);
	if (reset_redirection(env, g->redir_list) == FATAL)
		return (FATAL);
	return (ret);
}

t_status	exec_command(t_command cmd, t_env *env)
{
	t_command_handler a[] = {
			&exec_simple,
			&exec_pipeline,
			&exec_list,
			&exec_grouping
	};

	return (a[cmd.type](cmd.command, env));
}
