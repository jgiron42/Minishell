//
// Created by joachim on 30/11/2021.
//

#include "minishell.h"

t_status exec_regular_builtin(t_simple s, t_env *env)
{
	g_err = is_built_in(s.argv[0])(s.argv, env);
	return (OK);
}

t_status exec_special_builtin(t_simple s, t_env *env)
{
	g_err = is_special_built_in(s.argv[0])(s.argv, env);
	if (g_err == 0)
		return (OK);
	if (env->is_interactive)
		return (KO);
	else
		return (FATAL);
}
