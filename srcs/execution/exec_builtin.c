//
// Created by joachim on 30/11/2021.
//

#include "minishell.h"

t_status exec_regular_builtin(char **argv, t_simple s, t_env **env)
{
	t_env	*read_env;

	read_env = dupenv(*env);
	perform_assignments(&read_env, s, false);
}

t_status exec_special_builtin(char **argv, t_simple s, t_env **env)
{
	perform_assignments(env, s, false);
}