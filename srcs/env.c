#include "../includes/minishell.h"

int	add_env(t_env **env, char *key, char *value)
{
	t_env *new_node;
	t_env *tmp;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (SYSCALL_FAILURE);
	new_node->key = key;
	new_node->value = value;
	new_node->next = NULL;
	if (!*env)
		*env = new_node;
	else
	{
		tmp = *env;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
	}
	return (OK);
}

char	*get_env(t_env *env, char *key)
{
	while(env)
	{
		if (!strcmp(key, env->key))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

int		set_env(t_env **env, char *key, char *value)
{
	t_env *tmp;

	tmp = *env;
	while(tmp)
	{
		if (!strcmp(key, tmp->key))
		{
			free(tmp->value);
			tmp->value = value;
			return (OK);
		}
		tmp = tmp->next;
	}
	return (add_env(env, key, value));
}

int 	remove_env(t_env **	env, char *key)
{
	t_env *tmp;
	t_env *old;

	tmp = *env;
	old = NULL;
	while (tmp)
	{
		if (!strcmp(key, tmp->key))
		{
			free(tmp->key);
			free(tmp->value);
			if (!old)
				*env = tmp->next;
			else
				old->next = tmp->next;
			return (OK);
		}
		old = tmp;
		tmp = tmp->next;
	}
	return (KO);
}
