//
// Created by joachim on 22/11/2021.
//

#include "minishell.h"


int main(int argc, char **argv, char **envp)
{
	t_var_list	*env;

	if (parse_env(envp, &env) == FATAL || init_env(&env) == FATAL)
	{
		free_env(env);
		return (1);
	}
	// TEST:
	char **zbeub = serialize_env(env);
	for (int i = 0; zbeub[i]; ++i)
		printf("%s\n", zbeub[i]);
	free_env(env);
	ft_free_split(zbeub);
}