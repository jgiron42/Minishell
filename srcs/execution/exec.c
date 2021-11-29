//
// Created by joachim on 22/11/2021.
//
#include "minishell.h"

char 		g_err;

typedef		t_status (*t_command_handler)(union u_command, t_env **);

t_status	exec_simple(union u_command cmd, t_env **env)
{
	t_simple s;

	s = cmd.simple;

}

t_status	exec_pipeline(union u_command cmd, t_env **env)
{
	t_pipeline *p;
	int			next_pipe[2];
	int			prev_pipe[2];
	int 		ret;
	int			to_wait;

	to_wait = 0;
	p = cmd.pipeline;
	prev_pipe[0] = -1;
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
				dup2(next_pipe[0]);
		}
		to_wait++;
		exec_command(p->command, env);
		p = p->next;
	}

}

t_status	exec_list(union u_command cmd, t_env **env)
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

t_status	exec_grouping(union u_command cmd, t_env **env)
{
	t_grouping	g;
	t_env		*new_env;

	g = cmd.grouping;
	if (g.is_in_subshell)
	{
		new_env = dupenv(*env);
		if (!new_env)
			return (FATAL);
	}
	return(exec_command(*g.command, &new_env));
}

t_status	exec_command(t_command cmd, t_env **env)
{
	t_command_handler a[] = {
			&exec_simple,
			&exec_pipeline,
			&exec_list,
			&exec_grouping
	};

	return(a[cmd.type](cmd.command, env));
}