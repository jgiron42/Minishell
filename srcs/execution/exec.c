//
// Created by joachim on 22/11/2021.
//
#include "minishell.h"

char 		g_err;

typedef		t_status (*t_command_handler)(union u_command, t_env *env);

t_status	exec_simple(union u_command cmd, t_env *env)
{
	t_simple	s;

	s = cmd.simple;
	expand_simple(&s);
	/*
	 *  A="a     b"
	 *  B="c"
	 *  word_list:	{echo}, {$A$B}
	 *  expand:		{echo} {a     bc}
	 *  split:		"echo", "a", "bc"
	 */
	// expand all but redirections and assignments -> argv
	// perform redirections
	if (!s.argv[0] && perform_assignments(env, s, false) == FATAL)
		return (FATAL);
	if (!s.argv[0])
		return (OK);
	if (is_special_built_in(s.argv[0]))
		return (exec_special_builtin(s, env));
	if (is_built_in(s.argv[0]))
		return (exec_regular_builtin(s, env));
	else
		return (exec_program(s, env));
}

t_status	exec_pipeline(union u_command cmd, t_env *env)
{
	t_pipeline *p;
	int			next_pipe[2];
	int			prev_pipe_read;
	int 		ret;
	int			to_wait;
	int			status;

	to_wait = -1;
	p = cmd.pipeline;
	prev_pipe_read = -1;
	while (p)
	{
		next_pipe[0] = -1;
		if (p->next && pipe(next_pipe) < -1)
		{
			// TODO: print error?
			return(FATAL);
		}
		ret = fork();
		if (ret == -1)
		{
			// TODO: print error?
			return(FATAL);
		}
		else if (!ret)
		{
			if (p->next)
			{
				dup2(next_pipe[1], 1);
				close(next_pipe[0]);
			}
			if (prev_pipe_read != -1)
				dup2(prev_pipe_read, 0);
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
	waitpid(ret, &status, 0);
	while (--to_wait >= 0)
		wait(NULL);
	if (WIFEXITED(status))
		g_err = WEXITSTATUS(status);
	else
		g_err = WTERMSIG(status);
	return (OK);
}

t_status	exec_list(union u_command cmd, t_env *env)
{
	t_list *l;
	t_status ret;

	l = cmd.list;
	while (l)
	{
		ret = exec_pipeline((union u_command)l->pipeline, env);
		if ( ret != OK ||
			(l->sep == AND && g_err != 0) ||
			(l->sep == OR && g_err == 0))
			break;
		l = l->next;
	}
	return (ret);
}

t_status	exec_grouping(union u_command cmd, t_env *env)
{
	t_grouping	g;
	t_env		new_env;

	new_env = *env;
	g = cmd.grouping;
	if (g.is_in_subshell)
	{
		new_env.vars = dup_var_list(new_env.vars);
		if (!new_env.vars)
			return (FATAL);
	}
	return(exec_command(*g.command, &new_env));
}

t_status	exec_command(t_command cmd, t_env *env)
{
	t_command_handler a[] = {
			&exec_simple,
			&exec_pipeline,
			&exec_list,
			&exec_grouping
	};

	return(a[cmd.type](cmd.command, env));
}