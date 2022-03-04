//
// Created by joachim on 26/02/2022.
//

#include "minishell.h"

void	ft_exit(t_env *env)
{
	free_env(env);
	if (env->is_interactive)
		ft_putstr_fd("exit\n", 2);
	exit(g_err);
}
