//
// Created by joachim on 30/11/2021.
//

#include "minishell.h"

t_status exec_regular_builtin(t_simple s, t_env *env)
{
	(void)s;
	(void)env;
//	t_env	*read_env;
//
//	read_env = dup_var_list(*env);
//	perform_assignments(&read_env, s, false);
	return (OK);
}

t_status exec_special_builtin(t_simple s, t_env *env)
{
	(void)s;
	(void)env;
//	perform_assignments(env, s, false);
	return (OK);
}
