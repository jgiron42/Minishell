//
// Created by joachim on 22/11/2021.
//
#include "minishell.h"

char 		g_err;

t_status	exec_pipeline(t_pipeline *p, t_env **env)
{

}

t_status	exec_node(t_node *node, t_env **env, bool subshell)
{
	t_env	*new_env;

	if (subshell)
	{
		new_env = dupenv(*env);
		if (!new_env)
			return (FATAL);
		return(exec_node(node, &new_env, false));
	}
	while (node)
	{
		if (node->sublist)
			return (exec_node(node->sublist, env, node->is_in_subshell));
		else
			return (exec_pipeline(node->p, env));
		if ((node->sep == AND && g_err != 0) ||
			(node->sep == OR && g_err == 0))
			break;
		node = node->next;
	}
	return (OK);
}