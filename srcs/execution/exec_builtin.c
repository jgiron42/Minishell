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
	unsigned char ret;

//	perform_assignments(env, s, false);
	ret = is_special_built_in(s.argv[0])(s.argv, env);
	if (ret == OK || env->is_interactive)
		return (ret);
	else
		return (FATAL);
}
