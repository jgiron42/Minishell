#include "minishell.h"

void	free_env(t_env *env)
{
	t_var_list	*tmp;

	while (env->vars)
	{
		free(env->vars->key);
		free(env->vars->value);
		tmp = env->vars->next;
		free(env->vars);
		env->vars = tmp;
	}
	free(env->opened_files.data);
	clear_history();
}

t_status	export_var(t_env *env, char *key)
{
	t_var_list	*tmp;

	tmp = env->vars;
	while (tmp)
	{
		if (!ft_strcmp(key, tmp->key))
		{
			tmp->is_exported = true;
			return (OK);
		}
		tmp = tmp->next;
	}
	return (KO);
}

t_var_list	*ft_lstlast(t_var_list *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}
