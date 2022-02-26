//
// Created by joachim on 22/11/2021.
//

#include "minishell.h"

t_status	parse_env(char **envp, t_var_list **env)
{
	char	*equal;

	*env = NULL;
	while (*envp)
	{
		equal = *envp;
		while (*equal && *equal != '=')
			equal++;
		*equal = 0;
		++equal;
		if (equal)
		{
			if (add_var(env, *envp, equal, true) == FATAL)
				return (FATAL);
		}
		envp++;
	}
	return (OK);
}
