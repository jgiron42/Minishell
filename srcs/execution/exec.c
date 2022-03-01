//
// Created by joachim on 22/11/2021.
//
#include "minishell.h"

unsigned char 		g_err;

typedef		t_status (*t_command_handler)(union u_command, t_env *env);

t_status	command_not_found(char *name)
{
	ft_putstr_fd(name, 2);
	ft_putstr_fd(": command not found\n", 2);
	g_err = 127;
	return (OK);
}

t_status	exec_simple(union u_command cmd, t_env *env)
{
	t_simple	s;
	int			ret;
	char		*name;

	s = cmd.simple;
	expand_simple(&s, env);
	ret = perform_redirection(env, s.redir_list);
	if (ret == KO && !env->is_interactive && is_special_built_in(s.argv[0]))
		ret = FATAL;
	if (ret != OK)
		return (ret);
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
		if (ret == OK)
			ret = exec_program(name, s, env);
		else if (ret == KO)
			ret = command_not_found(s.argv[0]);
		free(name);
	}
	ft_free_split(s.argv);
	if (reset_redirection(env, s.redir_list) == FATAL)
		return (FATAL);
	return (ret);
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
			if ((p->next && (dup2(next_pipe[1], 1) == -1
				|| close(next_pipe[0]) == -1)) ||
			 	(prev_pipe_read != -1 && dup2(prev_pipe_read, 0)))
			{}	//TODO
			exec_command(p->command, env);
			exit(g_err);
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
		get_g_err(env, ret);
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
			(l->sep == AND_IF && g_err != 0) ||
			(l->sep == OR_IF && g_err == 0))
			break;
		l = l->next;
	}
	return (ret);
}

t_status	exec_grouping(union u_command cmd, t_env *env)
{
	t_grouping	*g;
	t_env		new_env;
	int			ret;
	pid_t		pid;

	new_env = *env;
	g = cmd.grouping;
	if (perform_redirection(env, g->redir_list) == FATAL)
		return (FATAL);
	if (g->is_in_subshell)
	{
		new_env.vars = dup_var_list(new_env.vars);
		if (!new_env.vars)
			return (FATAL);
		pid = fork();
		if (pid == -1)
			return (FATAL);
		if (!pid)
		{
			reset_signals(env);
			env->is_interactive = false;
			exec_command(g->command, &new_env);
			ft_exit(env);
		}
		get_g_err(env, pid);
	}
	else
		ret = exec_command(g->command, &new_env);
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
