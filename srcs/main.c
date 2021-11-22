//
// Created by joachim on 22/11/2021.
//

#include "minishell.h"


int main(int argc, char **argv, char **envp)
{
	t_env	*env;

	env = parse_env(envp);
	if (!env || init_env(&env) == SYSCALL_FAILURE)
	{
		free_env(env);
		return (1);
	}

}