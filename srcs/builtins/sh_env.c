#include "minishell.h"

unsigned char	sh_env(char **argv, t_env *env)
{
	t_var_list	*first;

	(void)argv;
	first = env->vars;
	while (env->vars && env->vars->key)
	{
		if (env->vars->is_exported == true)
		{
			ft_putstr_fd(env->vars->key, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd(env->vars->value, 1);
			ft_putstr_fd("\n", 1);
		}
		env->vars = env->vars->next;
	}
	env->vars = first;
	return (0);
}
