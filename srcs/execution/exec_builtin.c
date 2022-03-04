//
// Created by joachim on 30/11/2021.
//

#include "minishell.h"

t_status	exec_regular_builtin(t_simple s, t_env *env)
{
	int	ret;

	ret = is_built_in(s.argv[0])(s.argv, env);
	return (ret);
}

t_status	exec_special_builtin(t_simple s, t_env *env)
{
	unsigned char	ret;

	ret = is_special_built_in(s.argv[0])(s.argv, env);
	if (ret == OK || env->is_interactive)
		return (ret);
	else
		return (FATAL);
}
